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

  init_maintenance_mode();
  init_error_reporting(STATE);
  date_default_timezone_set('UTC');
  $db = new mysql();
  $js = new JavaScript();
  $session = new Session();

  if (isset($_SESSION['user'])) {
    $user = $_SESSION['user'];
  }
}

function init_error_reporting($state) {
  switch ($state) {
    case 'production':
      error_reporting(0);
      @ini_set('display_errors', 0);
      break;

    case 'development':
      error_reporting(E_ALL);
      @ini_set('display_errors', 1);
  }
}

function init_maintenance_mode() {
  if (IN_MAINTENANCE_MODE) {
    if (!isset($_GET['bypass'])) {
      include('./html/maintenance.html');
      exit;
    }
  }
}


init();

?>
