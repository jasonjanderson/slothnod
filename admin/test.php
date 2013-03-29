<?php
require_once('./include/bootstrap.inc');
$bootstrap = Bootstrap::get_instance();
$bootstrap->init_minimal();
$a = array('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z');

var_dump(User::db_get(169824199));
Cache::flush();
Cache::print_status();


?>
