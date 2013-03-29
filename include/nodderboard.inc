<?php

class NodderBoard extends TweetBoard {
  private static $_user_id = '';

  public function __construct() { }

  public static function init($user_id) {
    self::$_user_id = $user_id;
  }

  protected static function get_user_id() { return self::$_user_id; }

}

?>
