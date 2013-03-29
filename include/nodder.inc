<?php

class Nodder {
  private $id;
  private $username;
  private $following;
  private $followers;
  private $join_date;
  private $img_url;
  private $active;

  public function __construct() { }

  public function set_id($v) { $this->id = $v; }
  public function get_id() { return $this->id; }

  public function set_username($v) { $this->username = $v; }
  public function get_username() { return $this->username; }

  public function set_following($v) { $this->following = $v; }
  public function get_following() { return $this->following; }

  public function set_followers($v) { $this->followers = $v; }
  public function get_followers() { return $this->followers; }

  public function set_join_date($v) { $this->join_date = $v; }
  public function get_join_date() { return $this->join_date; }

  public function set_img_url($v) { $this->img_url = $v; }
  public function get_img_url() { return $this->img_url; }

  public function set_active($v) { $this->active = $v; }
  public function is_active() { return $this->active; }


  public static function db_get($username) {
    global $db;
    $sql = 
      "SELECT
        user.id,
        user.username,
        user.following,
        user.followers,
        user.join_date,
        user.img_url,
        user.active
      FROM
        user
      WHERE
        LOWER(user.username) = LOWER('%username%');";

    $result = $db->query($sql,
      array('username' => $username)
    );
    if (mysql::num_rows($result) != 1) {
      return NULL;
    }
    return mysql_fetch_object($result, 'Nodder');
  }

}

?>
