<?php
require_once('./include/bootstrap.inc');
$bootstrap = Bootstrap::get_instance();
$bootstrap->init_minimal();
Cache::flush();
Cache::print_status();




?>
