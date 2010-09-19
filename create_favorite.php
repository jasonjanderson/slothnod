<?php
require_once('./include/oauth/twitteroauth.php');
$id = NULL;

if(!isset($_GET['id'])) {
  echo "No favorite ID given";
  exit;
}

$id = $_GET['id'];
settype($id, 'integer');

/* Create a TwitterOauth object with consumer/user tokens. */
$connection = new TwitterOAuth(CONSUMER_KEY, CONSUMER_SECRET, $user->get_oauth_token(), $user->get_oauth_secret());

$response = $connection->post("favorites/create/$id");

?>
