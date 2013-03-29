<?php

class Cache {
  // 60
  const UNIX_MINUTE = 60;
  // 60 * 60
  const UNIX_HOUR = 3600;
  // 60 * 60 * 24
  const UNIX_DAY = 86400;
  // 60 * 60 * 24 * 7
  const UNIX_WEEK = 604800;

  private static $_memcache = null;

  private function __construct() { }

  public static function connect($server, $port=11211) {
    self::$_memcache = new Memcache();
    if (!(self::$_memcache->addServer($server, $port))) {
      throw new Exception(sprintf('Could not connect to Memcache server: %s:%s', $server, $port));
    }
  }

  public static function exists($key) {
    return ((self::$_memcache->get($key)) && (self::$_memcache->getResultCode() == Memcache::RES_SUCCESS));
  }

  public static function get($key) {
    return self::$_memcache->get($key);
  }

  public static function set($key, $value, $expiration=0) {
    if (!(self::$_memcache->set($key, $value, 0, $expiration))) {
      throw new Exception(
        sprintf('ERROR: Failed to store key pair \'%s\' = \'%s\' in cache.', 
          $key,
          $value
        )
      );
    }
  }

  public static function delete($key) {
    self::$_memcache->delete($key);
  }

  public static function flush() { self::$_memcache->flush(); }
  public static function print_status(){ 
    $status = self::$_memcache->getStats();
    echo "<table border='1'>"; 
    echo "<tr><td>Memcache Server version:</td><td> ".$status ["version"]."</td></tr>"; 
    echo "<tr><td>Process id of this server process </td><td>".$status ["pid"]."</td></tr>"; 
    echo "<tr><td>Number of seconds this server has been running </td><td>".$status ["uptime"]."</td></tr>"; 
    echo "<tr><td>Accumulated user time for this process </td><td>".$status ["rusage_user"]." seconds</td></tr>"; 
    echo "<tr><td>Accumulated system time for this process </td><td>".$status ["rusage_system"]." seconds</td></tr>"; 
    echo "<tr><td>Total number of items stored by this server ever since it started </td><td>".$status ["total_items"]."</td></tr>"; 
    echo "<tr><td>Number of open connections </td><td>".$status ["curr_connections"]."</td></tr>"; 
    echo "<tr><td>Total number of connections opened since the server started running </td><td>".$status ["total_connections"]."</td></tr>"; 
    echo "<tr><td>Number of connection structures allocated by the server </td><td>".$status ["connection_structures"]."</td></tr>"; 
    echo "<tr><td>Cumulative number of retrieval requests </td><td>".$status ["cmd_get"]."</td></tr>"; 
    echo "<tr><td> Cumulative number of storage requests </td><td>".$status ["cmd_set"]."</td></tr>"; 
    $percCacheHit=((real)$status ["get_hits"]/ (real)$status ["cmd_get"] *100); 
    $percCacheHit=round($percCacheHit,3); 
    $percCacheMiss=100-$percCacheHit; 
    echo "<tr><td>Number of keys that have been requested and found present </td><td>".$status ["get_hits"]." ($percCacheHit%)</td></tr>"; 
    echo "<tr><td>Number of items that have been requested and not found </td><td>".$status ["get_misses"]."($percCacheMiss%)</td></tr>"; 
    $MBRead= (real)$status["bytes_read"]/(1024*1024); 
    echo "<tr><td>Total number of bytes read by this server from network </td><td>".$MBRead." Mega Bytes</td></tr>"; 
    $MBWrite=(real) $status["bytes_written"]/(1024*1024) ; 
    echo "<tr><td>Total number of bytes sent by this server to network </td><td>".$MBWrite." Mega Bytes</td></tr>"; 
    $MBSize=(real) $status["limit_maxbytes"]/(1024*1024) ; 
    echo "<tr><td>Number of bytes this server is allowed to use for storage.</td><td>".$MBSize." Mega Bytes</td></tr>"; 
    echo "<tr><td>Number of valid items removed from cache to free memory for new items.</td><td>".$status ["evictions"]."</td></tr>"; 
    echo "</table>"; 
  } 

}

?>
