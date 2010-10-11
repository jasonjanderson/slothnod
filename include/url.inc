<?php
class URL {
  private $url_array;

  public function __construct() {
    $uri_array = explode('?', $_SERVER['REQUEST_URI']);
    $this->url_array = explode('/', $uri_array[0]);
    array_shift($this->url_array);
    if ($this->url_array[(sizeof($this->url_array) - 1)] == '') {
      array_pop($this->url_array);
    }
  }

  public function __destruct() {
    unset($this->url_array);
  }

  public function get_url_array() {
    return $this->url_array;
  }
  
}

?>
