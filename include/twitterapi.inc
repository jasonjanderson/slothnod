<?php
class TwitterAPI {
  private static $_oauth = null;

  private function __construct() { }

  public static function init($consumer_key, $consumer_secret) {
    self::$_oauth = new EpiTwitter($consumer_key, $consumer_secret);
  }

  private static function set_user(&$user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to TwitterAPI::set_user is not of type User');
    }
    self::$_oauth->setToken($user->get_oauth_token(), $user->get_oauth_secret());
  }

  public static function get_authorize_url() {
    return self::$_oauth->getAuthorizeUrl(null, array('oauth_callback' => OAUTH_CALLBACK));
  }

  public static function set_token($token=null, $secret=null) {
    return self::$_oauth->setToken($token, $secret);
  }

  public static function get_access_token($params=null) {
    return self::$_oauth->getAccessToken($params);
  }

  public static function get_verify_credentials() {
    return self::$_oauth->get_accountVerify_credentials();
  }

  public static function create_favorite(&$user, $tweet_id) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to TwitterAPI::create_favorite() is not of type User');
    }
    if (!is_numeric($tweet_id)) {
      throw new Exception('Argument "tweet_id" passed to TwitterAPI::create_favorite() is not numeric');
    }
    TwitterAPI::set_user($user);
    return self::$_oauth->post('/favorites/create/' . $tweet_id . '.json');
  }

  public static function destroy_favorite(&$user, $tweet_id) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to TwitterAPI::destroy_favorite() is not of type User');
    }
    if (!is_numeric($tweet_id)) {
      throw new Exception('Argument "tweet_id" passed to TwitterAPI::destroy_favorite() is not numeric');
    }
    TwitterAPI::set_user($user);
    return self::$_oauth->post('/favorites/destroy/' . $tweet_id . '.json');
  }

  public static function create_follow(&$user, $user_id) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to TwitterAPI::destroy_favorite() is not of type User');
    }
    if (!is_numeric($user_id)) {
      throw new Exception('Argument "tweet_id" passed to TwitterAPI::destroy_favorite() is not numeric');
    }
    TwitterAPI::set_user($user);
    return self::$_oauth->post('/friendships/create.json?user_id=' . $user_id);
  }


  public static function retweet(&$user, $tweet_id) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to TwitterAPI::retweet() is not of type User');
    }
    if (!is_numeric($tweet_id)) {
      throw new Exception('Argument "tweet_id" passed to TwitterAPI::retweet() is not numeric');
    }
    TwitterAPI::set_user($user);
    return self::$_oauth->post('/statuses/retweet/' . $tweet_id . '.json');
  }



  

}

?>
