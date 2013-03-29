<?php

class AnonymousTweet extends TweetBase implements BoardElement {
  public static function construct($params) {
    $tweet = new AnonymousTweet();

    $tweet->set_id($params['id']);
    $tweet->set_user_id($params['user_id']);
    $tweet->set_text($params['text']);
    $tweet->set_post_date($params['post_date']);
    return $tweet;
  }


  public function render() {
    include('./html/anonyomoustweet.html');
  }

}

?>
