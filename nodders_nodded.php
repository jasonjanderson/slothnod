<?php
// Included by /nodders.php
global $nodder;

$page = URL::pop();
if ($page == '') {
  $page = 1;
}
NoddedNodderBoard::init($nodder->get_id());
$total_rows = NoddedNodderBoard::db_get_total_rows();

$pagination = new Pagination($page, $total_rows, 50, '/nodders/' . $nodder->get_username() . '/nodded');
$nodboard = NoddedNodderBoard::db_get($pagination->get_limit_clause());
include('./html/nodders_nodded.html');

?>
