<?php
if (!($user = Auth::get_current_user())) {
  echo "signin";
  exit;
}
$id = URL::pop();
if (!is_numeric($id) || $id == '') {
  exit;
}
try {
  $tweet = TweetBase::db_get($id);
  $favorite = Favorite::construct($user, $tweet);
  Favorite::db_remove($favorite);

  BootStrap::init_twitter_api();
  TwitterAPI::destroy_favorite($user, $tweet->get_id());
} catch (Exception $e) {
  // muffeled
}

?>
