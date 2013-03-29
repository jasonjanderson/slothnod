<?php

class NodBoard extends TweetBoard {
  public static function get_sql() {
    return '
      SELECT
        status_id,
        (unix_timestamp(utc_date()) - unix_timestamp(nodboard_date)) AS anonymous
      FROM
        nodboard 
      ORDER BY
        nodboard_date DESC';
  }

  public static function get_sql_total_rows() {
    return '
      SELECT 
        COUNT(*) AS num_rows
      FROM
        nodboard
    ';
  }

  public static function db_get_tweet(&$row) {
    return TweetFactory::factory($row['status_id'], $row['anonymous']);
  }

}

?>
