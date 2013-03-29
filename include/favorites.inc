<?php

class Favorites {
  private $user_ids;
  private $users = null;

  public function __construct($user_ids) {
    if (!is_array($user_ids)) {
      throw new Exception('Argument "user_ids" passed to Favorites::construct() is not an array.');
    }
    $this->user_ids = $user_ids;
  }

  public function __sleep() {
    return array('user_ids');
  }

  public function get_user_id_array() {
    return $this->user_ids;
  }

  public function get_user_array() {
    if (!$this->users) {
      $this->users = $this->_fetch_users($this->user_ids);
    }
    return $this->users;
  }

  public function &get_img_url_array() {
    $users = $this->get_user_array();
    $img_urls = array();
    foreach($users as $user) {
      if ($user) {
        $img_urls[$user->get_username()] = $user->get_img_url();
      }
    }
    return $img_urls;
  }

  public function user_favorited(&$user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to Favorites::user_favorited() is not of type User');
    }
    return in_array($user->get_id(), $this->user_ids);
  }

  private function &_fetch_users(&$arr) {
    $users = array();
    foreach($arr as $user_id) {
      array_push($users, User::db_get($user_id));
    }
    return $users;
  }


  public static function db_get($tweet_id) {
    if (!(is_numeric($tweet_id))) {
      throw new Exception('Argument "tweet_id" passed to Favorites::db_get() is not numeric.');
    }
    if ($user_ids = Cache::get('Favorites:' . $tweet_id)) {
      return new Favorites(unserialize($user_ids));
    }
    $sql = '
      SELECT
        user_id
      FROM
        favorite
      WHERE
        status_id = \'%id%\'
      ORDER BY
        rand()
    ';
    try {
      $db = MySQL::get_instance();
      $result = $db->query($sql, array('id'=>$tweet_id));
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not fetch favorites (Tweet:%s) from database. MySQL Exception: %s', $tweet_id, $e));
    }
    $user_ids = array();
    while ($row = $result->fetch_assoc()) {
      array_push($user_ids, $row['user_id']);
    }
    
    $result = $db->query($sql, array('id'=>$tweet_id));
    Cache::set('Favorites:' . $tweet_id, serialize($user_ids), Cache::UNIX_DAY);

    return new Favorites($user_ids);
  }


}

?>
