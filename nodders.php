<?php
global $nodder;
global $username;
$username = URL::pop();

$nodder = User::db_get_username($username=$username);
if (!$nodder) {
  Page::render('./html/noddernotfound.html', './html/page.html');
} else {
  $route = URL::pop();
  switch ($route) {
    case 'mostnods':
     $title = $username . ' - Most Nods - SlothNod';
      Page::render('./nodders_mostnods.php', './html/page.html', $title);
      break;
    case 'nodded':
      $title = $username . ' - Nodded - SlothNod';
      Page::render('./nodders_nodded.php', './html/page.html', $title);
      break;
    default:
      $title = $username . ' - Recent - SlothNod';
      Page::render('./nodders_recent.php', './html/page.html', $title);
      break;
  }
}

?>
