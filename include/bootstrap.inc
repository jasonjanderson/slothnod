<?php
require_once('./include/mysql.inc');
require_once('./include/JavaScript.inc');
require_once('./include/Session.inc/');
require_once('./include/User.inc');


function init() {
  global $db;
  global $js;
  global $session;
  global $user;

  $db = new mysql();
  $js = new JavaScript();
  $session = new Session();


  init_error_reporting($state);
  if (isset($_SESSION['user'])) {
    $user = $_SESSION['user'];
  }
}

function init_error_reporting($state) {
  switch ($state) {
    case 'production':
      error_reporting(0);
      @ini_set(‘display_errors’, 0);
      break;

    case 'development':
      error_reporting(E_ALL);
      @ini_set(‘display_errors’, 1);
  }
}


init();

?>
