<?php

class Notification {
  private static $_instance = null; 
  private $messages = array();
  private $messages_typed = array();

  public function __construct() {

  }
  
  public static function get_instance() {
    if (!(self::$_instance instanceof self)) {
      self::$_instance = new self();
    }
    return self::$_instance;
  }

  public function add_notification($message, $type=null) {
    if (isset($type)) {
      if (!(in_array($type, $this->messages_typed))) {
        $this->messages_typed[$type] = array();
      }
      array_push($this->messages_typed[$type], $message);
      return;
    }

    array_push($this->_messages, $message);
  }

  public function get_notifications($type=null) {
    if (isset($type)) {
      if (!(in_array($type, $this->messages_typed))) {
        throw new Exception(sprintf('Notification type: "%s" doesn\'t exist', $type));
      }
      return $this->messages_typed[$type];
    }
    return $this->messages;
  }
}

?>
