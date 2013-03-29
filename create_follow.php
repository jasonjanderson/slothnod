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
  BootStrap::init_twitter_api();
  TwitterAPI::create_follow($user, $id);
} catch (Exception $e) {
  // muffeled
}

?>
