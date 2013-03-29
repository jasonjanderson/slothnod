<?php
// Included by /nodders.php
global $nodder;

$page = URL::current();
if ($page == '') {
  $page = 1;
}
RecentNodderBoard::init($nodder->get_id());
$total_rows = RecentNodderBoard::db_get_total_rows();

$pagination = new Pagination($page, $total_rows, 50, '/nodders/' . $nodder->get_username());
$nodboard = RecentNodderBoard::db_get($pagination->get_limit_clause());
include('./html/nodders_recent.html');

?>
