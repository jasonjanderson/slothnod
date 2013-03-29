<?php
require_once('./include/bootstrap.inc');
$bootstrap = Bootstrap::get_instance();
$bootstrap->init_minimal();
if (!isset($_GET['install'])) {
  echo "Can't Install";
  exit();
}
$db = MySQL::get_instance();
/*
$sql = "CREATE INDEX index_favorite_status_id ON favorite (status_id);";
$db->query($sql);

$sql = "CREATE INDEX index_favorite_user_id ON favorite (user_id);";
$db->query($sql);
 */

//$sql = "ALTER TABLE user CHANGE join_date join_date TIMESTAMP;";
/*
$db->query($sql);

$sql= "
  CREATE TABLE IF NOT EXISTS session ( 
    id varchar(32) NOT NULL default '', 
    http_user_agent varchar(32) NOT NULL default '', 
    data blob NOT NULL, 
    last_accessed timestamp NOT NULL, 
    PRIMARY KEY  (id) 
  ) ENGINE=MyISAM DEFAULT CHARSET=latin1;
";
$db->query($sql);

$sql = '
CREATE TABLE IF NOT EXISTS nodboard (
  status_id bigint unsigned NOT NULL,
  user_id bigint unsigned NOT NULL,
  nodboard_date timestamp,
PRIMARY KEY  (status_id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
';
$db->query($sql);
 */
//$sql = 'CREATE INDEX nodboard_user_id ON nodboard (user_id);';
//$db->query($sql);

//select favorite.status_id,   user.id AS user_id,   status.text AS text,   status.post_date, COUNT(favorite.status_id) AS favorite_count,   user.followers,   user.following,   (user.followers * 0.004) AS sloth_form,   status.on_leaderboard   FROM favorite   JOIN status   ON favorite.status_id = status.id   JOIN user   ON status.user_id = user.id   GROUP BY status.id   HAVING favorite_count >= 5   AND favorite_count >= sloth_form   AND user.followers > 0 AND (UNIX_TIMESTAMP(utc_date()) - UNIX_TIMESTAMP(status.post_date)) < 172800 AND (UNIX_TIMESTAMP(utc_date()) - UNIX_TIMESTAMP(status.post_date)) > 86400;
/*
$db->query($sql);
$sql = "CREATE OR REPLACE VIEW next_nodboard AS 
  SELECT favorite.status_id, 
  user.id AS user_id,
  status.text AS text,
  COUNT(favorite.status_id) AS favorite_count, 
  user.followers, 
  user.following, 
  (user.followers * 0.001) AS sloth_form, 
  status.on_leaderboard 
  FROM favorite 
  JOIN status 
  ON favorite.status_id = status.id 
  JOIN user 
  ON status.user_id = user.id 
  GROUP BY status.id 
  HAVING favorite_count >= 5 
  AND favorite_count >= sloth_form 
  AND user.followers > 0 
  AND favorite.status_id NOT IN (SELECT status_id FROM nodboard)";
$db->query($sql);
 */
?>
