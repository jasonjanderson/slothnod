<?php

class JavaScript {
  //private $file;
  //private $data_sorted;
  //private $data_unsorted;
  private static $variables = array();

/*  public function __construct() {
//    $this->file = array();
    $this->data_sorted = array();
    $this->data_unsorted = '';
    $this->data_variable = array();
  }
  public function __destruct() {
//    unset($this->file);
//    unset($this->data_sorted);
 //   unset($this->data_unsorted);
  }

  public function start_js_capture() {
    ob_start();
  }

  public function end_js_capture($key=NULL) {
    if (isset($key)) {
      $data_sorted[$key] = ob_get_contents();
    } else {
      $data_unsorted .= ob_get_contents();
    }
    ob_end_clean();
  }
  
 */
  public static function prepare_js($data) {
    return '<script type="text/javascript">' . $data . '</script>';
  }
  public static function prepare_variable($key, $value) {
    return 'var ' . $key . ' = ' . $value . ';';
  }
/*
  public function get_js($key=NULL) {
    if (isset($key)) {
      return $this->prepare_js($this->data_sorted[$key]);
    } else {
      return $this->prepare_js($this->data_unsorted);
    }
  }
 */
  public static function set_variable($key, $value) {
    self::$variables[$key] = $value;
  }

  public function get_all_variables() {
    $a = '';
    foreach (self::$variables as $k => $v) {
      $a .= self::prepare_variable($k, $v);
    }
    return self::prepare_js($a);
  }
}

?>
