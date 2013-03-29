<?php
require_once('./config.php');

function __autoload($classname) {
  require_once(DOCUMENT_ROOT . '/include/' . strtolower($classname) . '.inc');
}

class Bootstrap {

  public static $_instance = null;

  public function __construct() { }

  public function __destruct() { }

  public function init_minimal() {
    global $js;
    global $session;

    $this->init_maintenance_mode();
    $this->init_error_reporting(STATE);
    date_default_timezone_set('UTC');
    MySQL::connect($host=DB_HOST, $user=DB_USER, $password=DB_PASSWORD, $database=DB_NAME);
    Cache::connect($host='localhost');
    URL::init();
    $session = new Session($gc_maxlifetime=SESSION_TIMEOUT);
    $js = new JavaScript();
    $this->init_header();
  }

  public function init_error_reporting($state) {
    switch ($state) {
      case 'production':
        error_reporting(0);
        @ini_set('display_errors', 0);
        break;

      case 'development':
        error_reporting(E_ALL);
        @ini_set('display_errors', 1);
        break;
    }
  }

  public function init_maintenance_mode() {
    if (IN_MAINTENANCE_MODE) {
      if (!isset($_GET['bypass'])) {
        include('./html/maintenance.html');
        exit;
      }
    }
  }
  public function init_header() {
    if (preg_match('/rv:1\.(([1-8]|9pre|9a|9b[0-4])\.[0-9.]+).*Gecko/', $_SERVER['HTTP_USER_AGENT'])) {
        header('Content-type: application/xhtml+xml');
    }
  }

  public static function init_twitter_api() {
    TwitterAPI::init(CONSUMER_KEY, CONSUMER_SECRET);
  }

  public static function get_instance() {
    if (!(self::$_instance)) {
      self::$_instance = new self;
    }
    return self::$_instance;
  }

}

?>
