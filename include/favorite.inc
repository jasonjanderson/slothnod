<?php

class Favorite {
  private $tweet;
  private $user;

  private function __construct() { }

  public static function construct(&$user, &$tweet) {
    $favorite = new Favorite();
    $favorite->set_user($user);
    $favorite->set_tweet($tweet);
    return $favorite;
  }

  public function set_user(&$user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument \'user\' not of type \'User\'');
    }
    $this->user = $user;
  }

  public function set_tweet(&$tweet) {
    if (!($tweet instanceof TweetBase)) {
      throw new Exception('Argument \'tweet\' not of type \'TweetBase\'');
    }
    $this->tweet = $tweet;
  }

  public function get_user() {
    return $this->user;
  }

  public function get_tweet() {
    return $this->tweet;
  }


  public static function db_add($favorite) {
    if (!($favorite instanceof Favorite)) {
      throw new Exception('Argument "favorite" passed to Favorite::db_add() is not of type Favorite');
    }
    $sql = '
      INSERT INTO 
        favorite (
        status_id,
        user_id,
        favorite_date
      ) VALUES (
        ?, ?, UTC_TIMESTAMP()
      )
    ';

    try {
      $db = MySQL::get_instance();
      $stmt = $db->prepare($sql);
      $stmt->bind_param(
        'ii',
        $favorite->get_tweet()->get_id(),
        $favorite->get_user()->get_id()
      );
      $db->execute($stmt);
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not add favorite to database. MySQLException: %s', $e));
    }
    Cache::delete('Favorites:' . $favorite->get_tweet()->get_id());
  }

  public static function db_remove($favorite) {
    $sql = '
      DELETE FROM
        favorite
      WHERE
        status_id = ?
        AND user_id = ?
    ';

    try {
      $db = MySQL::get_instance();
      $stmt = $db->prepare($sql);
      $stmt->bind_param(
        'ii',
        $favorite->get_tweet()->get_id(),
        $favorite->get_user()->get_id()
      );
      $db->execute($stmt);
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not delete favorite from database. MySQLException: %s', $e));
    }
    Cache::delete('Favorites:' . $favorite->get_tweet()->get_id());
  }

}


?>
