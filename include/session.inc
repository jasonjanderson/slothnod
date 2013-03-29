<?php

class Session
{
  public function __construct($gc_maxlifetime=1400, $gc_probability=1, $gc_divisor=100) {
    if ($gc_maxlifetime != "" && is_integer($gc_maxlifetime)) {
      @ini_set('session.gc_maxlifetime', $gc_maxlifetime);
    }

    if ($gc_probability != "" && is_integer($gc_probability)) {
      @ini_set('session.gc_probability', $gc_probability);
    }

    if ($gc_divisor != "" && is_integer($gc_divisor)) {
      @ini_set('session.gc_divisor', $gc_divisor);
    }

    $this->gc_maxlifetime = ini_get("session.gc_maxlifetime");

    session_set_save_handler(
      array(&$this, 'open'),
      array(&$this, 'close'),
      array(&$this, 'read'),
      array(&$this, 'write'),
      array(&$this, 'destroy'),
      array(&$this, 'gc')
    );
    register_shutdown_function('session_write_close');

    session_start();
  }

  public function __destruct() {
    session_write_close();
  }

  public function stop() {
    session_unset();
    session_destroy();
  }

  public static function regenerate_id() {
    $old_id= session_id();
    session_regenerate_id();
    $new_id = session_id();

    $sql = '
      UPDATE
        session 
      SET
        id = ?,
        last_accessed = UTC_TIMESTAMP()
      WHERE
        id = ?
    ';
    $db = MySQL::get_instance();
    $stmt = $db->prepare($sql);
    $stmt->bind_param('ss', $new_id, $old_id);
    $stmt->execute();
  }

  public function open($save_path, $session_name) {
    return true;
  }

  public function close() {
    return true;
  }


  public function read($session_id) {
    $sql = "
      SELECT data FROM session WHERE
        id = '%id%'
        AND last_accessed > (UTC_TIMESTAMP() - %gc_maxlifetime%)
      LIMIT 1
    ";
    try {
      $db = MySQL::get_instance();
      $result = $db->query(
        $sql,
        array(
          'id'=>$session_id,
          'gc_maxlifetime'=>$this->gc_maxlifetime
        )
      );
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not read data from session \'%s\'. MySQLException: %s', $session_id, $e));
    }
    if ($row = $result->fetch_assoc()) {
      return $row['data'];
    }
    return '';
  }

  public function write($session_id, $session_data) {
    $sql = '
      INSERT INTO
        session (
          id,
          data,
          last_accessed
        ) VALUES (?, ?, UTC_TIMESTAMP())
        ON DUPLICATE KEY UPDATE
        data = ?,
        last_accessed = UTC_TIMESTAMP()
    ';
    try {
      $db = MySQL::get_instance();
      $stmt = $db->prepare($sql);
      $stmt->bind_param(
        'sss',
        $session_id,
        $session_data,
        $session_data
      );
      $db->execute($stmt);
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not write \'%s\' => \'%s\' to session. MySQLException: %s', $session_id, $session_data, $e));
    }
  }

  public function destroy($session_id) {
    $sql = '
      DELETE FROM
        session
      WHERE
        id = ?
    ';
    try {
      $db = MySQL::get_instance();
      $stmt = $db->prepare($sql);
      $stmt->bind_param(
        's',
        $session_id
      );
      $db->execute($stmt);
    } catch (MySQLException $e) {
      throw new Exception(sprintf('Could not remove session \'%s\'. MySQLException: %s', $session_id, $e));
    }
  }

  public function gc($maxlifetime) {
    $timestamp = (time() - $maxlifetime);
    $sql ='
      DELETE FROM
        session
      WHERE
        last_accessed < ?
    ';
    try {
      $db = MySQL::get_instance();
      $stmt = $db->prepare($sql);
      $stmt->bind_param(
        'i',
        $timestamp
      );
      $db->execute($stmt);
    } catch (MySQLException $e) {
      throw new Exception('Could not garbage collect session data.', 0, $e);
    }
  }

  /*private static function get_user_agent_hash() { 
    return md5($_SERVER["HTTP_USER_AGENT"] . $this->salt);
  }
   */
}
?>
