<?php

class Tweet {
  protected $status_id;
  protected $text;
  protected $post_date;
  protected $leaderboard_date;
  protected $user_id;
  protected $username;
  protected $img_url;
  protected $favorite;

  public function __construct($row) {
    $this->status_id = $row['status_id'];
    if (!settype($this->status_id, 'integer')) {
      die('No tweet ID given');
    }
    $this->text = $row['text'];
    $this->post_date = $row['post_date'];
    $this->leaderboard_date = $row['leaderboard_date'];
    $this->user_id = $row['user_id'];
    $this->username = $row['username'];
    $this->img_url = $row['img_url'];
    $this->favorite = $this->_get_favorite_array();
  }

  public function get_status_id() { return $this->status_id; }

  public function get_text() { return $this->text; }

  public function get_post_date() { return $this->post_date; }

  public function get_leaderboard_date() { return $this->leaderboard_date; }

  public function get_user_id() { return $this->user_id; }

  public function get_username() { return $this->username; }

  public function get_img_url() { return $this->img_url; }

  public function render() {
    include('./html/Tweet.html');
  }

  public function get_avatar_json() {
    return json_encode($this->favorite);
  }

  public function get_avatar_array() {
    return $this->favorite;
  }

  protected function _get_favorite_array() {
    global $db;

    $sql = "SELECT user.username, user.img_url FROM favorite LEFT JOIN user ON user.id = favorite.user_id WHERE favorite.status_id = '$this->status_id' ORDER BY RAND()";

    $result = $db->query($sql);
    $a = array();

    while ($row = mysql_fetch_assoc($result)) {
      $a[$row['username']] = $row['img_url'];
    }
    return $a;
  }

  public function favorited($user) {
    return array_key_exists($user->get_username(), $this->favorite);
  }


}

?>
