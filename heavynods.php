<?php

$page = URL::pop();
if ($page != '') {
  URL::redirect('/heavynods');
}

$nodboard = HeavyNodsBoard::db_get('');
include('./html/heavynodsboard.html');

?>
