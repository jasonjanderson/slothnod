<?php
require_once('./include/user.inc');

class Auth {
  private static $_user = null;

  public function __construct() { }

  public static function is_logged_in() {
    self::$_user = self::get_current_user();
    return (!is_null(self::$_user));
  }

  public static function get_current_user() {
    if (self::$_user) {
      return self::$_user;
    }
    if (isset($_SESSION['user_id'])) {
      self::$_user = User::db_get($_SESSION['user_id']);
    }
    return self::$_user;
  }

  public static function login($user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument \'user\' is not of type \'User\'');
    }
    $_SESSION['user_id'] = $user->get_id();
    self::$_user = $user;
  }

  public static function logout() {
    unset($_SESSION['user_id']);
    self::$_user = null;
    session_unset();
    session_destroy();
  }
}
?>
