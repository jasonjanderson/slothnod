<?php

function get_menu_item($title, $link, $active) {
  global $route;

  if ($route == $active) {
    return "<li class=\"active\"><a href=\"" . $link . "\">" . $title . "</a></li>"; 
  }
  return "<li><a href=\"" . $link . "\">" . $title . "</a></li>";
}

?>
