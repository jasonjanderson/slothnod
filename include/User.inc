<?php

class User {
  private $id;
  private $username;
  private $followers;
  private $following;
  private $img_url;
  private $oauth_token;
  private $oauth_secret;

  public function __construct($id, $username, $followers, $following, $img_url, $oauth_token, $oauth_secret) {
    $this->id = $id;
    $this->username = $username;
    $this->followers = $followers;
    $this->following = $following;
    $this->img_url = $img_url;
    $this->oauth_token = $oauth_token;
    $this->oauth_secret = $oauth_secret;
  }
  
  public function __destruct() {

  }

  public function get_id() { return $this->id; }
  public function get_username() { return $this->username; }
  public function get_followers() { return $this->followers; }
  public function get_following() { return $this->following; }
  public function get_img_url() { return $this->img_url; }
  public function get_oauth_token() { return $this->oauth_token; }
  public function get_oauth_secret() { return $this->oauth_secret; }

  public static function valid_user($user) {
    # Change when out of beta
    return ((!User::is_excluded($user)) && User::is_included($user));
  }

  public static function db_add($user) {
    global $db;
    $sql = "INSERT INTO user
      (id, username, img_url, following, followers, join_date, oauth_token, oauth_secret, active) VALUES
      ('%id%', '%username%', '%img_url%', '%following%', '%followers%', UTC_TIMESTAMP(), '%oauth_token%', '%oauth_secret%', True)
      ON DUPLICATE KEY UPDATE username = '%username%', img_url = '%img_url%', following = '%following%',
      followers = '%followers%', oauth_token = '%oauth_token%', oauth_secret = '%oauth_secret%', active = True;";
    $db->query($sql,
      array(
        'id'=>$user->get_id(),
        'username'=>$user->get_username(),
        'img_url'=>$user->get_img_url(),
        'following'=>$user->get_following(),
        'followers'=>$user->get_followers(),
        'oauth_token'=>$user->get_oauth_token(),
        'oauth_secret'=>$user->get_oauth_secret()
        )
    );
  }

  public static function is_excluded($user) {
    global $db;
    $sql = "SELECT 1 FROM user_exclude WHERE id = '%id%';";
    $result = $db->query($sql, array('id' => $user->get_id()));
    if (mysql::num_rows($result) >= 1) {
      return true;
    }
    return false;
  }


  public static function is_included($user) {
    global $db;
    $sql = "SELECT 1 FROM user_include WHERE id = '%id%';";
    $result = $db->query($sql, array('id' => $user->get_id()));
    if (mysql::num_rows($result) >= 1) {
      return true;
    }
    return false;
  }

  public static function is_logged_in() {
    return isset($_SESSION['user']);

  }



}
?>
