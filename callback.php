<?php
require_once('./include/oauth/twitteroauth.php');

if (isset($_REQUEST['denied'])) {
  $session->stop();
  header('Location: ./');
}
/* If the oauth_token is old redirect to the connect page. */

if (isset($_REQUEST['oauth_token']) && $_SESSION['oauth_token'] !== $_REQUEST['oauth_token']) {
/*  $_SESSION['oauth_status'] = 'oldtoken';
*/
  $session->stop();
  header('Location: ./');
}


/* Create TwitteroAuth object with app key/secret and token key/secret from default phase */
$connection = new TwitterOAuth(CONSUMER_KEY, CONSUMER_SECRET, $_SESSION['oauth_token'], $_SESSION['oauth_token_secret']);


/* Remove no longer needed request tokens */
unset($_SESSION['oauth_token']);
unset($_SESSION['oauth_token_secret']);

/* Request access tokens from twitter */
$access_token = $connection->getAccessToken($_REQUEST['oauth_verifier']);

/* Create a TwitterOauth object with consumer/user tokens. */
$connection = new TwitterOAuth(CONSUMER_KEY, CONSUMER_SECRET, $access_token['oauth_token'], $access_token['oauth_token_secret']);

/* If method is set change API call made. Test is called by default. */
$userinfo = $connection->get('account/verify_credentials');
$user = new User(
  $id = $userinfo->{'id'},
  $username = $userinfo->{'screen_name'},
  $followers = $userinfo->{'followers_count'},
  $following = $userinfo->{'friends_count'},
  $img_url = $userinfo->{'profile_image_url'},
  $oauth_token = $access_token['oauth_token'],
  $oauth_secret = $access_token['oauth_token_secret']
);

if (!User::valid_user($user)) {
  include('./html/deny_user.html');
} else {
  User::db_add($user);
  $session->regenerate_id();
  $_SESSION['user'] = $user;
  header('Location: ./');
}
