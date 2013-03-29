<?php

abstract class TweetBoard extends Board {
//  protected $tweet_ids = array();
  protected static $sql = '';
  protected static $sql_total_rows = '';

  public function __construct() { }

/*
  public function __sleep() {
    return array('tweet_ids');
    //return array_keys(get_object_vars($this));
  }

  public function __wakeup() { }
*/
/*
  public function get_avatar_json() {
    $a = array();
    foreach ($this->nodboard as $tweet) {
      $a[$tweet->get_status_id()] = $tweet->get_avatar_array();
    }
    return json_encode($a);
  }

  public function get_status_id_json() {
    return json_encode($this->status_id);
  }
*/
  protected static function get_cache_name() { return get_called_class(); }

  protected static function db_get_tweet(&$row) {
    $class = get_called_class();
    return $class::db_get_tweet($row);
  }

  public static function db_get($limit_clause='') {
    $class = get_called_class();
    try {
      $db = MySQL::get_instance();
      $result = $db->query($class::get_sql() . ' ' . $limit_clause);
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not fetch TweetBoard. MySQL Exception: %s', $e));
    }

    $class = get_called_class();
    $tweetboard = new $class();
    while ($row = $result->fetch_assoc()) {
      $element = self::db_get_tweet($row);
      $tweetboard->add_element($element);
    }

    return $tweetboard;
  }

  public static function db_get_total_rows() {
    $class = get_called_class();
/*    if ($num_rows = Cache::get('NodBoard:num_rows')) {
      return unserialize($num_rows);
    }
 */
    try {
      $db = MySQL::get_instance();
      $result = $db->query($class::get_sql_total_rows());
      $row = $result->fetch_assoc();
      (int)$num_rows = $row['num_rows'];
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not fetch the row count for the TweetBoard. MySQL Exception: %s', $e));
    }
//    Cache::set('NodBoard:num_rows', serialize($num_rows));
    return $num_rows;
  }
}

?>
