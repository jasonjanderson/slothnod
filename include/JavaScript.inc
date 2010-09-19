<?php

class JavaScript {
  private $file;
  private $data_sorted;
  private $data_unsorted;
  private $data_variable;

  public function __construct() {
    $this->file = array();
    $this->data_sorted = array();
    $this->data_unsorted = '';
    $this->data_variable = array();
  }

  public function __destruct() {
    unset($this->file);
    unset($this->data_sorted);
    unset($this->data_unsorted);
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
  
  public function prepare_js($data) {
    return '<script type="text/javascript">' . $data . '</script>';
  }
  public function prepare_js_var($key, $value) {
    return 'var ' . $key . ' = ' . $this->data_variable[$key] . ';';
  }

  public function get_js($key=NULL) {
    if (isset($key)) {
      return $this->prepare_js($this->data_sorted[$key]);
    } else {
      return $this->prepare_js($this->data_unsorted);
    }
  }

  public function set_js_var($key, $value) {
    $this->data_variable[$key] = $value;
  }
  
  public function get_js_var($key) {
    return $this->prepare_js_var($key, $this->data_variable[$key]);
  }

  public function get_all_js_var() {
    $a = '';
    foreach ($this->data_variable as $k => $v) {
      $a .= $this->prepare_js_var($k, $v);
    }
    return $this->prepare_js($a);
  }
}

?>
