<?php
class Date {

  /*
  * Turns a MySQL datetime (YYYY-MM-DD HH:MM:SS) into a unix timestamp
  * @param str
  */
  public static function datetime_to_timestamp($str) {

    list($date, $time) = explode(' ', $str);
    list($year, $month, $day) = explode('-', $date);
    list($hour, $minute, $second) = explode(':', $time);
    $timestamp = mktime($hour, $minute, $second, $month, $day, $year);
    return $timestamp;
  }

  public static function datetime_to_fuzzy($str) {
    return self::fuzzy_time_ago(mktime() - self::datetime_to_timestamp($str));
  }

  public static function fuzzy_time_ago($seconds) {
    $minutes = $seconds / 60;
    if (round($minutes) <= 1) {
      if (round($minutes) == 1) {
        return 'a minute ago';
      }
      return 'less than a minute ago';
    }
    $hours = $minutes / 60;
    if (round($hours) <= 1) {
      if (round($hours) == 1) {
        return 'about a hour ago';
      }
      return 'about ' . round($minutes) . ' minutes ago';
    }
    $days = $hours / 24;
    if (round($days) <= 1) {
      if (round($days) == 1) {
        return 'a day ago';
      }
      return 'about ' . round($hours) . ' hours ago';
    }
    $years = $days / 365;
    if (round($years) <= 1) {
      if (round($years) == 1) {
        return 'about a year ago';
      }
      return 'about ' . round($days) . ' days ago';
    }
    return 'about ' .round($years) . ' years ago';
  }

}
?>

