<?php
Cache::print_status();

class Tweet {
  private $_id;
  private $_postDate;
  private $_text;
  public function __construct($id, $postDate, $text) {
    $this->_id = $id;
    $this->_postDate = $postDate;
    $this->_text = $text;
  }
  public function getId() { return $this->_id; }
  public function getPostDate() { return $this->_postDate; }
  public function getText() { return $this->_text; }
}

$tweet = new Tweet(334089370476544, '2010-11-04 23:50:27', 'The best thing about telepathy is...I know, right?');
echo serialize($tweet);
var_dump(unserialize(Cache::get('Tweet:33408937047654sdf4')));

echo "Tweet:" . $tweet->getId();






?>
