<?php

$page = URL::pop();
if ($page == '') {
  $page = 1;
}
$total_rows = YesterdayBoard::db_get_total_rows();
$pagination = new Pagination($page, $total_rows, 50, '/yesterday');
$nodboard = YesterdayBoard::db_get($pagination->get_limit_clause());
include('./html/yesterdayboard.html');

?>
