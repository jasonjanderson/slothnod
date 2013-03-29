<?php

class RecentNodderBoard extends NodderBoard {
  public static function get_sql() {
    return sprintf('
      SELECT 
        status.id AS status_id
      FROM 
        status
      WHERE 
        status.user_id = \'%s\'
      ORDER BY
        status.post_date DESC
    ', self::get_user_id());
  }

  public static function get_sql_total_rows() {
    return sprintf('
      SELECT 
        count(*) AS num_rows
      FROM 
        status
      WHERE 
        status.user_id = \'%s\'
    ', self::get_user_id());
  }

  public static function db_get_tweet(&$row) {
    return TweetFactory::factory($row['status_id']);
  }

}

?>
