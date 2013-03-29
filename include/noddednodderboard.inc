<?php

class NoddedNodderBoard extends NodderBoard {
  public static function get_sql() {
    return sprintf('
      SELECT 
        favorite.status_id
      FROM 
        favorite
      WHERE 
        favorite.user_id = \'%s\'
      ORDER BY
        favorite.status_id DESC
    ', self::get_user_id());
  }

  public static function get_sql_total_rows() {
    return sprintf('
      SELECT 
        COUNT(*) AS num_rows
      FROM 
        favorite
      WHERE 
        favorite.user_id = \'%s\'
    ', self::get_user_id());
  }

  public static function db_get_tweet(&$row) {
    return TweetFactory::factory($row['status_id']);
  }

}

?>
