<?php
require_once('./include/Pagination.inc');
require_once('./include/nodboard.inc');

global $nodboard, $js;

if (isset($_GET['p'])) {
	$page = (int)$_GET['p'];
} else {
	$page = 1;
}
$sql = "SELECT SQL_CALC_FOUND_ROWS leaderboard.status_id,
		leaderboard.text,
		leaderboard.post_date,
                leaderboard.leaderboard_date,
                leaderboard.anonymous,
		leaderboard.user_id,
		leaderboard.username,
		leaderboard.img_url FROM leaderboard ORDER BY leaderboard.leaderboard_date DESC";

$pagination = new Pagination($connection=$db->get_connection(), $sql=$sql, $rows_per_page=50, $num_adjacent=3);
$result = $pagination->get_result();
$nodboard = new NodBoard($result);
include('./html/nodboard.html');
$js->set_js_var('tweets', $nodboard->get_status_id_json());

?>
