<?php
require_once('./include/Tweet.inc');

class AnonymousTweet extends Tweet {

  public function __construct($row) {
    parent::__construct($row);
  }

  public function render() {
    include('./html/AnonyomousTweet.html');
  }

}

?>
