<?php
require_once('./config.php');

class mysql {
  protected $connection = null;
  protected $error = null;

  public function __construct() {
    $this->connection = mysql_connect(DB_HOST, DB_USERNAME, DB_PASSWORD);
    if (!$this->connection) {
      $this->error = "Could not connect to MySQL server ('" . DB_HOST ."')\nMySQL Error:" . mysql_error();
    }
    if (!mysql_select_db(DB_NAME)) {
      $this->error = "Could not select database ('" . DB_NAME ."')\nMySQL Error:" . mysql_error();
    }
  }

  public function __destruct() {
    mysql_close($this->connection);
  }

  public function get_connection() {
    return $this->connection;
  }

  public function error() {
    return $this->error;
  }

  public function query($query, $params = null) {
    if (isset($params) && is_array($params)) {
      $tmp = array();
      foreach ($params as $k => $v) {
        $tmp['%' . $k . '%'] = mysql_real_escape_string($v);
      }
      $sql = str_replace(array_keys($tmp), array_values($tmp), $query);
      $result = mysql_query($sql, $this->connection);
    } else {
      $result = mysql_query($query, $this->connection);
    }
    if (!$result) {
      $this->error = "Could not execute query ('" . $query . "')\nMySQL Error:". mysql_error();
    }
    return $result;
  }

  public static function num_rows($result) {
    return mysql_num_rows($result);
  }
};
?>
