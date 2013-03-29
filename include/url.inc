<?php
class URL {
  private static $_url_array = null;
  private static $_pointer = -1;

  private function __construct() { }

  public function __destruct() { }

  public static function init() {
    self::$_url_array = self::get_url_array();
  }

  public static function redirect($url) {
    header('Location: ' . $url);
  }

  public static function get_url_array() {
    if (!self::$_url_array) {
      self::$_url_array = self::_get_url_array($_SERVER['REQUEST_URI']);
    }
    return self::$_url_array;
  }

  public static function pop() {
    self::$_pointer++;
    if (isset(self::$_url_array[self::$_pointer])) {
      return self::$_url_array[self::$_pointer];
    }
    return '';
  }

  public static function reset() {
    self::$_pointer = -1;
  }

  public static function push() {
    self::$_pointer--;
    if (isset(self::$_url_array[self::$_pointer])) {
      return self::$_url_array[self::$_pointer];
    }
    return '';
  }

  public static function current() {
    if (self::$_pointer == -1) {
      return self::$_url_array[0];
    }
    if (isset(self::$_url_array[self::$_pointer])) {
      return self::$_url_array[self::$_pointer];
    }
    return '';
  }

  private static function _get_url_array($array) {
    $uri_array = explode('?', $array);
    $url_array = explode('/', $uri_array[0]);
    array_shift($url_array);
    if ($url_array[(sizeof($url_array) - 1)] == '') {
      array_pop($url_array);
    }
    return $url_array;
  }
   
}

?>
