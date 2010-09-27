<?php
require_once('./include/Pagination.inc');
require_once('./include/nodboard.inc');

global $nodboard, $js;

if (isset($_GET['p'])) {
	$page = (int)$_GET['p'];
} else {
	$page = 1;
}
$sql = "SELECT SQL_CALC_FOUND_ROWS yesterday_board.status_id,
		yesterday_board.text,
		yesterday_board.post_date,
                yesterday_board.leaderboard_date,
                yesterday_board.anonymous,
		yesterday_board.user_id,
		yesterday_board.username,
		yesterday_board.img_url FROM yesterday_board ORDER BY yesterday_board.leaderboard_date DESC";

$pagination = new Pagination($connection=$db->get_connection(), $sql=$sql, $rows_per_page=50, $num_adjacent=3, $page_url_name='p', $url_base='yesterday');
$result = $pagination->get_result();
$nodboard = new NodBoard($result);
include('./html/yesterday.html');
$js->set_js_var('tweets', $nodboard->get_status_id_json());

?>
