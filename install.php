<?php
require_once('./include/bootstrap.inc');
if (!isset($_GET['install'])) {
  exit();
}

$sql= "CREATE TABLE IF NOT EXISTS `session_data` (
`session_id` varchar(32) NOT NULL default '',
`http_user_agent` varchar(32) NOT NULL default '',
`session_data` blob NOT NULL,
`session_expire` int(11) NOT NULL default '0',
PRIMARY KEY  (`session_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;";

$sql .= "CREATE VIEW IF NOT EXISTS yesterday_board AS 
  SELECT status.id AS status_id,
  status.text,
  status.post_date,
  unix_timestamp(status.leaderboard_date) AS leaderboard_date,
  (unix_timestamp(utc_date()) - unix_timestamp(status.leaderboard_date)) AS anonymous,
  user.id AS user_id,
  user.username,
  user.img_url,
  user.followers,
  user.following 
  FROM status 
  LEFT JOIN user 
  ON status.user_id = user.id 
  WHERE  status.on_leaderboard = 1 
  AND (unix_timestamp(utc_date()) - unix_timestamp(status.leaderboard_date)) < 86400 
  AND (unix_timestamp(utc_date()) - unix_timestamp(status.leaderboard_date)) > 0;";

$sql .= "CREATE VIEW IF NOT EXISTS next_leaderboard AS 
  SELECT favorite.status_id, 
  COUNT(favorite.status_id) AS favorite_count, 
  user.followers, 
  user.following, 
  ((user.following + user.followers) * 0.005) AS sloth_form, 
  status.on_leaderboard 
  FROM favorite 
  JOIN status 
  ON favorite.status_id = status.id 
  JOIN user 
  ON status.user_id = user.id 
  GROUP BY status.id 
  HAVING favorite_count >= 3 
  AND favorite_count >= sloth_form 
  AND user.followers > 0 
  AND status.on_leaderboard = 0;";

$sql .= "CREATE OR REPLACE VIEW most_nodded AS 
  SELECT status.id AS status_id, 
  status.user_id, 
  status.text, 
  status.post_date, 
  status.on_leaderboard, 
  status.leaderboard_date, 
  user.img_url, 
  user.following, 
  user.followers, 
  user.username, 
  COUNT(favorite.status_id) AS nodded, 
  (unix_timestamp(utc_date()) - unix_timestamp(status.leaderboard_date)) AS anonymous 
  FROM status 
  JOIN user 
  ON status.user_id = user.id 
  JOIN favorite 
  ON status.id = favorite.status_id 
  GROUP BY status.id 
  HAVING on_leaderboard = true 
  ORDER BY nodded DESC 
  LIMIT 100;";

$db->query($sql);


?>
