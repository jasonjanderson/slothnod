<?php

class HeavyNodsBoard extends TweetBoard {
  protected static function get_sql() {
    return '
      SELECT 
        nodboard.status_id,
        COUNT(favorite.status_id) AS num_nods,
        (unix_timestamp(utc_date()) - unix_timestamp(nodboard.nodboard_date)) AS anonymous
      FROM 
        nodboard
      JOIN favorite
        ON nodboard.status_id = favorite.status_id
      JOIN user 
        ON nodboard.user_id = user.id
      GROUP BY 
        nodboard.status_id
      ORDER BY 
        num_nods DESC
      LIMIT 100
    ';
  }

  public static function get_sql_total_rows() {
    return '';
  }

  public static function db_get_tweet(&$row) {
    return TweetFactory::factory($row['status_id'], $row['anonymous']);
  }

}

?>
