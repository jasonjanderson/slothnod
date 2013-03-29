<?php

$page = URL::pop();
if ($page == '') {
  $page = 1;
}
$total_rows = NodBoard::db_get_total_rows();
$pagination = new Pagination($page, $total_rows, 50);
$nodboard = NodBoard::db_get($pagination->get_limit_clause());
include('./html/nodboard.html');

?>
