<?php
//require_once('./include/Pagination.inc');
require_once('./include/nodboard.inc');

global $nodboard, $js;

$sql = "SELECT SQL_CALC_FOUND_ROWS most_nodded.status_id,
		most_nodded.text,
		most_nodded.post_date,
                most_nodded.leaderboard_date,
                most_nodded.nodded,
                most_nodded.anonymous,
		most_nodded.user_id,
		most_nodded.username,
		most_nodded.img_url FROM most_nodded ORDER BY most_nodded.nodded DESC, most_nodded.post_date DESC";

$result = $db->query($sql);
$nodboard = new NodBoard($result);
include('./html/mostnodded.html');
$js->set_js_var('tweets', $nodboard->get_status_id_json());

?>
