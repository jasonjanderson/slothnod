<?php
if (isset($_GET['denied'])) {
  URL::redirect('/');
}
Bootstrap::init_twitter_api();

try {
TwitterAPI::set_token($_GET['oauth_token']);
$token = TwitterAPI::get_access_token();
TwitterAPI::set_token($token->oauth_token, $token->oauth_token_secret);
$userinfo = TwitterAPI::get_verify_credentials();
$userinfo->response;

$user_array = array(
  'id'=>$userinfo->id,
  'username'=>$userinfo->screen_name,
  'followers'=>$userinfo->followers_count,
  'following'=>$userinfo->friends_count,
  'img_url'=>$userinfo->profile_image_url,
  'oauth_token'=>$token->oauth_token,
  'oauth_secret'=>$token->oauth_token_secret
);
$user = User::construct($user_array);
User::db_add($user);
Session::regenerate_id();
Auth::login($user);
URL::redirect('/');
} catch (Exception $e) {
  Page::render('./html/signin_failure.html', './html/page.html', 'Login Failure - SlothNod');
}

?>

