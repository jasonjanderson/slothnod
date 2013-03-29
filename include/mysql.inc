<?php

class MySQLException extends Exception {
  protected $mysqli_warnings = '';
  private $mysqli = null;
  private $mysqli_connect_errno = null;
  private $mysqli_connect_error = null;
  private $mysqli_errno = null;
  private $mysqli_error = null;
  private $query = null;

  public function __construct(&$mysqli, $message, $query=null, Exception $previous=null) {
    $this->mysqli = &$mysqli;
    parent::__construct($message, mysqli_errno($this->mysqli));
    $this->query = $query;
    $this->_fetch_warnings();
    $this->mysqli_connect_errno = mysqli_connect_errno();
    $this->mysqli_connect_error = mysqli_connect_error();
  }

  public function get_mysqli_warnings() { return $this->mysqli_warnings; }

  public function get_mysqli_connect_errno() { return $this->mysqli_connect_errno; }
  public function get_mysqli_connect_error() { return $this->mysqli_connect_error; }

  public function get_mysqli_errno() { return $this->mysqli_errno; }
  public function get_mysqli_error() { return $this->mysqli_error; }

  public function get_query() { return $this->query; }

  public function __toString() {
    return sprintf('Message: %s\n', $this->getMessage()) .
      sprintf('Code: %d\n', $this->getCode()) .
      sprintf('File: %s\n', $this->getFile()) .
      sprintf('Line: %s\n', $this->getLine()) .
      sprintf('Query: %s\n', $this->get_query()) .
      sprintf('MySQLi connect error number: %s\n', $this->get_mysqli_connect_errno()) .
      sprintf('MySQLi connect error: %s\n', $this->get_mysqli_connect_error()) .
      sprintf('MySQLi error number: %s\n', $this->get_mysqli_errno()) .
      sprintf('MySQLi error: %s\n', $this->get_mysqli_error()) .
      sprintf('Warnings: %s\n', $this->get_mysqli_warnings()) .
      sprintf('Trace: %s\n', $this->getTraceAsString());
  }

  private function _fetch_warnings() {
    if (mysqli_warning_count($this->mysqli)) {
      $e = mysqli_get_warnings($this->mysqli);
      do {
        $this->mysqli_warnings += sprintf('Warning: %d: %s\n', $e->errno, $e->message);
      } while ($e->next());
    }
  }
}


class MySQL {
  private static $_instance = null;
  private $mysqli = null;

  public static function connect($host, $user, $password, $database) {
    self::$_instance = new MySQL($host=$host, $user=$user, $password=$password, $database=$database);
  }

  final private function __construct($host='localhost', $user, $password, $database) {
    $this->mysqli = new mysqli($host=$host, $username=$user, $passwd=$password, $dbname=$database);
    if (mysqli_connect_errno()) {
      throw new MySQLException($this->_mysqli, 'Could not connect to database.');
    }
  }

  public function __destruct() {
    $this->mysqli->close();
  }

  final private function __clone() {}

  public static function get_instance() {
    if (!(self::$_instance instanceof self)) {
      throw new Exception('Database instance does not exist.');
    }
    return self::$_instance;
  }

  public function prepare($sql) {
    $stmt = null;
    if (!($stmt = $this->mysqli->prepare($sql))) {
      throw new MySQLException($this->mysqli, 'Could not prepare database query.', $sql);
    }
    return $stmt;
  }

  public function execute(&$stmt) {
    if (!($stmt instanceof mysqli_stmt)) {
      throw new MySQLException($this->mysqli, 'MySQL prepared statement (mysqli_stmt) was not passed to function.');
    }
    if (!$stmt->execute()) {
      throw new MySQLException($this->mysqli, 'Could not execute prepared statement');
    }
    $result = $stmt->result_metadata();
    return $result;
  }

  public function query($sql, $params=null) {
    if (isset($params) && is_array($params)) {
      $tmp = array();
      foreach ($params as $k => $v) {
        $tmp['%' . $k . '%'] = $this->mysqli->real_escape_string($v);
      }
      $sql = str_replace(array_keys($tmp), array_values($tmp), $sql);
    } 
    $result = $this->mysqli->query($sql);
    if (!$result) {
      throw new MySQLException($this->mysqli, 'Could not execute query.', $sql);
    }
    return $result;
  }
}
?>
