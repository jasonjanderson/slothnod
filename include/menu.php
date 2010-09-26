<?php

function get_menu_item($title, $link, $active, $new_window=false) {
  global $route;
  $element = '<li';

  if ($route == $active) {
    $element .=' class="active"';
  }
  $element .= '><a href="' . $link . '"';
  if ($new_window == true) {
    $element .= ' target="_blank"';
  }
  $element .= '>' . $title . '</a></li>';
  return $element;
}

?>
