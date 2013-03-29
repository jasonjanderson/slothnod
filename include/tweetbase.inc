<?php

class TweetBase {
  protected $id = 0;
  protected $text = '';
  protected $user_id = 0;
  protected $user = null;
  protected $post_date = '';
  protected $favorites = null;


  public function __construct() { }

  public static function construct($params) {
    if (!is_array($params)) {
      throw new Exception('TweetBase::construct() requires an array of key/value pairs as an argument.');
    }
    
    if (!isset($params['id'])) {
      throw new Exception('Array passed to TweetBase::construct() does not contain a "id" key.');
    }

    if (!isset($params['user_id'])) {
      throw new Exception('Array passed to TweetBase::construct() does not contain a "user" key.');
    }

    if (!isset($params['text'])) {
      throw new Exception('Array passed to TweetBase::construct() does not contain a "text" key.');
    }

    if (!isset($params['post_date'])) {
      throw new Exception('Array passed to TweetBase::construct() does not contain a "post_date" key.');
    }
    $classname = get_called_class();
    $tweetbase = new $classname();

    $tweetbase->set_id($params['id']);
    $tweetbase->set_user_id($params['user_id']);
    $tweetbase->set_text($params['text']);
    $tweetbase->set_post_date($params['post_date']);

    return $tweetbase;
  }

  public function __sleep() {
    return array('id', 'text', 'user_id', 'post_date');
  }

  public function set_id($id) {
    if (!is_numeric($id)) {
      throw new Exception('Argument "id" passed to TweetBase::set_id() is not numeric.');
    }
    $this->id = $id;
  }

  public function set_user_id($user_id) {
    if (!is_numeric($user_id)) {
      throw new Exception('Argument "user_id" passed to TweetBase::set_user_id() is not numeric.');
    }
    $this->user_id = $user_id;
  }

  public function set_user($user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to TweetBase::set_user() is not of type "User".');
    }
    $this->user = $user;
  }

  public function set_text($text) {
    if (!is_string($text)) {
      throw new Exception('Argument "text" passed to TweetBase::set_text() is not a string.');
    }
    $this->text = $text;
  }

  public function set_post_date($post_date) {
    if (!is_string($post_date)) {
      throw new Exception('Argument "post_date" passed to TweetBase::set_post_date() is not a string.');
    }
    $this->post_date = $post_date;
  }

  public function get_id() { return $this->id; }

  public function get_text() { return $this->text; }

  public function get_post_date() { return $this->post_date; }

//  public function get_post_date_unix() { return $this->post_date_unix; }

//  public function get_post_date_fuzzy() { return Date::fuzzy_time_ago(mktime() - $this->post_date_unix); }

//  public function get_post_date_iso8601() { return date('c', $this->post_date_unix); }

//  public function get_post_date_pretty() { return date("F j, Y, g:i A", $this->post_date_unix); }

//  public function get_leaderboard_date() { return $this->leaderboard_date; }

//  public function get_on_leaderboard() { return $this->on_leaderboard; }

  public function get_user_id() { return $this->user_id; }

  public function get_user() {
    if ($this->user) {
      return $this->user;
    }

    $user = User::db_get($this->user_id);
    $this->set_user($user);
    return $this->user;
  }

  public function get_favorites() {
    if ($this->favorites) {
      return $this->favorites;
    }
    $this->favorites = Favorites::db_get($this->id);
    return $this->favorites;
  }
    
  public static function db_get($id) {
    $class = get_called_class();
    if (!(is_numeric($id))) {
      throw new Exception('Argument "id" is not numeric.');
    }
    if ($tweetbase = Cache::get($class . ':' . $id)) {
      return unserialize($tweetbase);
    }
    $sql = '
      SELECT
        id,
        user_id,
        text,
        post_date
      FROM
        status
      WHERE
        id = \'%id%\'
      LIMIT 1
    ';
    try {
      $db = MySQL::get_instance();
      $result = $db->query($sql, array('id'=>$id));
      $tweetbase = $result->fetch_object(get_called_class());
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not fetch tweet (%s) from database. MySQL Exception: %s', $id, $e));
    }
    Cache::set($class . ':' . $id, serialize($tweetbase), Cache::UNIX_DAY);
    return $tweetbase;
  }

}

?>
