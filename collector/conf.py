"""
Config file for global parameters for SlothNod. 
"""
STATE='PRODUCTION'

SQL_HOST="localhost"
SQL_DATABASE="slothnod"
MEMCACHE_SERVER='localhost'
MEMCACHE_PORT='11211'

if (STATE == 'PRODUCTION'):
  SQL_USER="slothnod"
  SQL_PASSWORD="k3fgQ0pJibdQFZi4Dtv5rE9ObrMG8KoKfJMlv2XrRVMOTQDESe5wYebEIx7HCO7"
else:
  SQL_USER="slothnod"
  SQL_PASSWORD="slothnod"

OAUTH_CONSUMER_KEY="iY5GwavKZc4yx3SA2Oz2IA"
OAUTH_CONSUMER_SECRET="y617QtnBQaviFF3iBjYGPJIbH22dS79ki9upGT8OE"

TWITTER_FAVORITES_URL="http://api.twitter.com/1/favorites.json"
TWITTER_VERIFY_CREDENTIALS_URL="http://api.twitter.com/1/account/verify_credentials.json"
TWITTER_FOLLOWERS_URL="http://api.twitter.com/1/statuses/followers.json"
TWITTER_SHOW_USER_URL="http://api.twitter.com/1/users/show.json"

FAVORITE_FETCH_COUNT="100"
