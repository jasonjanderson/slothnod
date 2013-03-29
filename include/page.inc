<?php

class Page {

  private static $_title = '';
  private static $_content = '';

  private function __construct() { }

  public function __destruct() { }

  public static function render($page, $template=null, $title='') {
    self::set_title($title);
    ob_start();
    include($page);
    $content = ob_get_contents();
    ob_end_clean();
    self::add_content($content);
    if ($template) {
      include($template);
    } else {
      echo $content;
    }
  }

  public static function set_title($title) {
    self::$_title = $title;
  }

  public static function add_content($content) {
    self::$_content .= $content;
  }

  public static function get_title() { return self::$_title; }

  public static function get_content() { return self::$_content; }

}

?>
