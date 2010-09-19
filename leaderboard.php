<?php
require_once('./include/Pagination.inc');
require_once('./include/LeaderBoard.inc');

global $leaderboard, $js;

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

$pagination = new Pagination($connection=$db->get_connection(), $sql=$sql, $rows_per_page=10, $num_adjacent=3);
$result = $pagination->get_result();
$leaderboard = new LeaderBoard($result);
include('./html/leaderboard.html');
$js->set_js_var('tweets', $leaderboard->get_status_id_json());

?>
