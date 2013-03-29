<?php

class MostNodsNodderBoard extends NodderBoard {
  public static function get_sql() {
    return sprintf('
      SELECT 
        favorite.status_id,
        status.user_id,
        COUNT(favorite.status_id) AS num_nods
      FROM 
        favorite
      JOIN status ON
        favorite.status_id = status.id
      GROUP BY favorite.status_id
      HAVING
        status.user_id = \'%s\'
      ORDER BY
        num_nods DESC
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
