<?php

class YesterdayBoard extends TweetBoard {
  public static function get_sql() {
    return sprintf('
      SELECT 
        nodboard.status_id,
        nodboard.nodboard_date,
        (COUNT(favorite.status_id) / (user.followers * %s)) AS nod_ratio
      FROM 
        nodboard
      JOIN user
        ON nodboard.user_id = user.id
      JOIN favorite
        ON nodboard.status_id = favorite.status_id
      GROUP BY
        favorite.status_id
      HAVING 
        (unix_timestamp(utc_date()) - unix_timestamp(nodboard.nodboard_date)) < 86400
        AND (unix_timestamp(utc_date()) - unix_timestamp(nodboard.nodboard_date)) > 0
      ORDER BY
        nod_ratio DESC
    ', SLOTHNOD_FORMULA_MULTIPLIER);
  }

  public static function get_sql_total_rows() {
    return '
      SELECT 
        count(*) AS num_rows
      FROM 
        nodboard
      WHERE 
        (unix_timestamp(utc_date()) - unix_timestamp(nodboard.nodboard_date)) < 86400
        AND (unix_timestamp(utc_date()) - unix_timestamp(nodboard.nodboard_date)) > 0
    ';
  }

  public static function db_get_tweet(&$row) {
    return TweetFactory::factory($row['status_id']);
  }

}

?>
