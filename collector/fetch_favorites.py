#!/usr/bin/env python

__author__ = "Jason Anderson"
__version__ = "$Revision: 1.0 $"
__date__ = "$Date: In progress$"
__file__ = "fetch_favorites.py"

import simplejson as json
import urllib
import httplib
import conf
import MySQLdb as mysql
import logger
import oauth2 as oauth
import time
import re
import memcache

class User:
  """ Provides partial DAO functionality to the 'user' table in the database """
  def __init__(self, id, username, img_url, followers, following, oauth_token, oauth_secret):
    self.id = id
    self.username = username
    self.img_url = img_url
    self.oauth_token = oauth_token
    self.oauth_secret = oauth_secret
    self.followers = followers
    self.following = following

  def get_id(self):
    return self.id

  def get_username(self):
    return self.username

  def get_img_url(self):
    return self.img_url

  def get_oauth_token(self):
    return self.oauth_token

  def get_oauth_secret(self):
    return self.oauth_secret

  def update_user(self, json_data):
    global db
    cursor = db.cursor()
    if (self.following != json_data['friends_count']):
      cursor.execute("UPDATE user SET following = '%s' WHERE id = '%s'"
        % (json_data['friends_count'], self.id))
      cache.delete('User:%s' % self.id)
    if (self.followers != json_data['followers_count']):
      cursor.execute("UPDATE user SET followers = '%s' WHERE id = '%s'"
        % (json_data['followers_count'], self.id))
      cache.delete('User:%s' % self.id)
    if (self.img_url != json_data['profile_image_url']):
      cursor.execute("UPDATE user SET img_url = '%s' WHERE id = '%s'"
        % (mysql.escape_string(json_data['profile_image_url']), self.id))
      cache.delete('User:%s' % self.id)
    db.commit()
    cursor.close()

users = {}
cache = memcache.Client(['%s:%s' % (conf.MEMCACHE_SERVER, conf.MEMCACHE_PORT)], debug=0)
try:
  db = mysql.connect(host=conf.SQL_HOST,
    user=conf.SQL_USER,
    passwd=conf.SQL_PASSWORD,
    db=conf.SQL_DATABASE,
    use_unicode=True)
except mysql.Error, e:
  print "Error %d: %s" % (e.args[0], e.args[1])
  sys.exit(1)
 
consumer = oauth.Consumer(conf.OAUTH_CONSUMER_KEY, conf.OAUTH_CONSUMER_SECRET)

def fetch_favorites(user):
  global consumer
  global users

  print "Fetching favorites for %s" % user.get_username()
  token = oauth.Token(key=user.get_oauth_token(), secret=user.get_oauth_secret())
  client = oauth.Client(consumer=consumer, token=token)

  response, content = client.request(conf.TWITTER_VERIFY_CREDENTIALS_URL, "GET")
  if (response['status'] == '401'):
    deactivate_user(user)
    return None
  
  try: 
    user.update_user(json.loads(content))
  except ValueError:
    print "ERROR: Content returned is not JSON. Returned '%s'." % content

  response, content = client.request("%s?count=%s" % (conf.TWITTER_FAVORITES_URL, conf.FAVORITE_FETCH_COUNT), "GET")
    
  if (response['status'] == '200'):
    try:
      favorites = json.loads(content)
      [add_favorite(user, favorite) for favorite in favorites if valid_favorite(favorite)]
    except ValueError:
      print "ERROR: Content returned is not JSON. Returned '%s'." % content

def valid_favorite(favorite):
  """ Validates the favorite """
  global users
  return users.has_key(favorite['user']['id']) and valid_tweet_text(favorite['text'])

def valid_tweet_text(text):
  regex = ".*(http://|https://|@).*"
  r = re.compile(regex)
  return (r.search(text) == None and len(text.strip()) > 0)

def add_favorite(user, dict):
  global db
  a = time.strptime(dict['created_at'], "%a %b %d %H:%M:%S +0000 %Y")
  created_at_str = "%d-%d-%d %d:%d:%d" % (a[0], a[1], a[2], a[3], a[4], a[5])
  cursor = db.cursor()
  cursor.execute("""INSERT IGNORE INTO status 
    (id, user_id, text, post_date, on_leaderboard, leaderboard_date) VALUES ('%s', '%s', '%s', '%s', False, NULL);""" %
    (dict['id'],
    dict['user']['id'],
    mysql.escape_string(dict['text'].encode("utf-8")),
    created_at_str))
  cursor.execute("""INSERT IGNORE INTO favorite 
   (status_id, user_id, favorite_date)
    VALUES ('%s', '%s', UTC_TIMESTAMP());""" % (dict['id'], user.get_id()))
  db.commit()
  cursor.close()
  cache.delete('Favorites:%s' % dict['id'])

def deactivate_user(user):
  global db
  db.query("UPDATE user SET active=False WHERE id=%s" % user.get_id())
  db.commit()
    
def add_user_to_dict(row):
  global users
  user = User(
    id = row['id'],
    username = row['username'],
    oauth_token = row['oauth_token'],
    oauth_secret = row['oauth_secret'],
    img_url = row['img_url'],
    followers = row['followers'],
    following = row['following'])
  users[row['id']] = user

def main():
  global db
  global users
  cursor = db.cursor(mysql.cursors.DictCursor)
  cursor.execute("SELECT id, username, following, followers, oauth_token, oauth_secret, img_url FROM user WHERE active = True")
  result = cursor.fetchall()
  cursor.close()
  [add_user_to_dict(row) for row in result]
  [fetch_favorites(user) for (id, user) in users.iteritems()]
  db.commit()
  db.close()
    

if __name__ == '__main__':
  main()

