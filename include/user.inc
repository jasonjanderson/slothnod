<?php
require_once('./include/bootstrap.inc');

class User {
  private $id;
  private $username;
  private $followers;
  private $following;
  private $img_url;
  private $oauth_token;
  private $oauth_secret;

  public function __construct() { }

  public function __destruct() {}

  public function get_id() { return $this->id; }
  public function get_username() { return $this->username; }
  public function get_followers() { return $this->followers; }
  public function get_following() { return $this->following; }
  public function get_img_url() { return $this->img_url; }
  public function get_oauth_token() { return $this->oauth_token; }
  public function get_oauth_secret() { return $this->oauth_secret; }
  public function get_active() { return $this->active; }

  public function get_sloth_number() {
    return max(
      SLOTHNOD_FORMULA_MIN_NODS,
      ceil($this->followers * SLOTHNOD_FORMULA_MULTIPLIER)
    );
  }
  public function set_id($id) {
    if (!is_numeric($id)) {
      throw new Exception('Argument "id" passed to User::set_id is not numeric.');
    }
    $this->id = $id;
  }
  
  public function set_username($username) {
    if (!is_string($username)) {
      throw new Exception('Argument "username" passed to User::set_username is not a string.');
    }
    $this->username = $username;
  }

  public function set_followers($followers) {
    if (!is_numeric($followers)) {
      throw new Exception('Argument "followers" passed to User::set_followers is not numeric.');
    }
    $this->followers = $followers;
  }

  public function set_following($following) {
    if (!is_numeric($following)) {
      throw new Exception('Argument "following" passed to User::set_following is not numeric.');
    }
    $this->following = $following;
  }

  public function set_img_url($img_url) {
    if (!is_string($img_url)) {
      throw new Exception('Argument "img_url" passed to User::set_img_url is not a string.');
    }
    $this->img_url = $img_url;
  }

  public function set_oauth_token($oauth_token) {
    if (!is_string($oauth_token)) {
      throw new Exception('Argument "oauth_token" passed to User::set_oauth_token is not a string.');
    }
    $this->oauth_token = $oauth_token;
  }

  public function set_oauth_secret($oauth_secret) {
    if (!is_string($oauth_secret)) {
      throw new Exception('Argument "oauth_secret" passed to User::set_oauth_secret is not a string.');
    }
    $this->oauth_secret = $oauth_secret;
  }

  public function set_active($active) {
    $this->active = $active;
  }

  public static function construct(&$params) {
    if (!is_array($params)) {
      throw new Exception('Argument "params" passed to User::construct() is not an array.');
    }
    if (!isset($params['id'])) {
      throw new Exception('Array passed to User::construct() does not contain an "id" key.');
    }
    if (!isset($params['username'])) {
      throw new Exception('Array passed to User::construct() does not contain a "username" key.');
    }
    if (!isset($params['followers'])) {
      throw new Exception('Array passed to User::construct() does not contain a "followers" key.');
    }
    if (!isset($params['following'])) {
      throw new Exception('Array passed to User::construct() does not contain a "following" key.');
    }
    if (!isset($params['img_url'])) {
      throw new Exception('Array passed to User::construct() does not contain an "img_url" key.');
    }
    if (!isset($params['oauth_token'])) {
      throw new Exception('Array passed to User::construct() does not contain an "oauth_token" key.');
    }
    if (!isset($params['oauth_secret'])) {
      throw new Exception('Array passed to User::construct() does not contain an "oauth_secret" key.');
    }

    $user = new User();
    $user->set_id($params['id']);
    $user->set_username($params['username']);
    $user->set_followers($params['followers']);
    $user->set_following($params['following']);
    $user->set_img_url($params['img_url']);
    $user->set_oauth_token($params['oauth_token']);
    $user->set_oauth_secret($params['oauth_secret']);

    return $user;
  }
 
  public static function db_get($id) {
    if (!is_numeric($id)) {
      throw new Exception('Argument "id" passed to User::get() is not numeric.');
    }

    if ($user = Cache::get('User:' . $id)) {
      return unserialize($user);
    }

    $sql = '
      SELECT 
        id, username, img_url, following, followers, join_date, oauth_token, oauth_secret, active 
      FROM user
      WHERE
        id = \'%id%\'';
    $db = MySQL::get_instance();
    $result = $db->query($sql, array('id'=>$id));
    $user = $result->fetch_object('User');

    Cache::set('User:' . $id, serialize($user));
    return $user;
  }


  public static function db_get_username($username) {
    if (!is_string($username)) {
      throw new Exception('Argument "username" passed to User::db_get_username() is not a string.');
    }

    $sql = '
      SELECT 
        id
      FROM user
      WHERE
        LOWER(username) = LOWER(\'%username%\')';
    $db = MySQL::get_instance();
    $result = $db->query($sql, array('username'=>$username));
    if (!($row = $result->fetch_assoc())) {
      return null;
    }
    return User::db_get($row['id']);
  }


  public static function db_add($user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to User::db_add is not of type User.');
    }
    Cache::delete('User:' . $user->get_id());
    $sql = 'INSERT INTO user
      (id, username, img_url, following, followers, join_date, oauth_token, oauth_secret, active) VALUES
      (?, ?, ?, ?, ?, UTC_TIMESTAMP(), ?, ?, True)
      ON DUPLICATE KEY UPDATE username = ?, img_url = ?, following = ?,
      followers = ?, oauth_token = ?, oauth_secret = ?, active = True;';
    $db = MySQL::get_instance();
    $stmt = $db->prepare($sql);
    $stmt->bind_param(
      'issiissssiiss',
      $user->get_id(),
      $user->get_username(),
      $user->get_img_url(),
      $user->get_following(),
      $user->get_followers(),
      $user->get_oauth_token(),
      $user->get_oauth_secret(),
      $user->get_username(),
      $user->get_img_url(),
      $user->get_following(),
      $user->get_followers(),
      $user->get_oauth_token(),
      $user->get_oauth_secret()
    );
    $db->execute($stmt);
  }

  public static function db_remove($user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to User::db_remove is not of type User.');
    }
    Cache::delete('User:' . $user->get_id());
    $sql = 'DELETE FROM user WHERE id = ?';
    $db = MySQL::get_instance();
    $stmt = $db->prepare($sql);
    $stmt->bind_param(
      'i',
      $user->get_id()
    );
    $db->execute($stmt);
  }

  public static function db_update($user) {
    if (!($user instanceof User)) {
      throw new Exception('Argument "user" passed to User::db_add is not of type User.');
    }
    Cache::set('User:' . $user->get_id(), serialize($user), Cache::UNIX_DAY);
    $sql = '
      UPDATE user SET
        id = ?,
        username = ?, 
        img_url = ?, 
        following = ?, 
        followers = ?, 
        oauth_token = ?, 
        oauth_secret = ?, 
        active = ?
      WHERE
        id = ?
    ';
      
    $db = MySQL::get_instance();
    $stmt = $db->prepare($sql);
    $stmt->bind_param(
      'issiissii',
      $user->get_id(),
      $user->get_username(),
      $user->get_img_url(),
      $user->get_following(),
      $user->get_followers(),
      $user->get_oauth_token(),
      $user->get_oauth_secret(),
      $user->get_active(),
      $user->get_id()
    );
    $db->execute($stmt);
  }
}
?>
