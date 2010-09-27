<?php
require_once('./include/Tweet.inc');
require_once('./include/AnonymousTweet.inc');

class NodBoard {
  private $result;
  protected $nodboard = array();
  protected $status_id = array();

  public function __construct($result) {
    $this->result = $result;
    if ($this->result == NULL || mysql::num_rows($result) == 0) {
      print "No Blurts Found (yet)";
      return;
    }
     while ($row = mysql_fetch_assoc($this->result)) {
      if ($this->is_anonymous($row)) {
        $tweet = new AnonymousTweet($row);
        array_push($this->nodboard, $tweet);
      } else {
        $tweet = new Tweet($row);
        array_push($this->nodboard, $tweet);
      }
      array_push($this->status_id, $tweet->get_status_id());
    }
  }

  private function is_anonymous($row) {
   return ($row['anonymous'] < 0);
  }

  public function render() {
    foreach ($this->nodboard as $tweet) {
      $tweet->render();
    }
  }

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
}

?>
