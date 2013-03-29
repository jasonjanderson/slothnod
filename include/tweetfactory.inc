<?php
class TweetFactory {
  public static function factory($tweet_id, $anonymous=0) {
    if ($anonymous < 0) {
      return AnonymousTweet::db_get($tweet_id);
    }
    return Tweet::db_get($tweet_id);

  }
}

?>
