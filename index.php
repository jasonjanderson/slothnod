<?php
require_once('./include/bootstrap.inc');

global $route;
global $head_title;

$route = 'index';

if (isset($_GET['route'])) {
  $route = $_GET['route'];
}

ob_start();
include('./html/header.html');
$header = ob_get_contents();
ob_end_clean();

ob_start();
switch ($route) {

  case 'index':
    $head_title="Nod Board - SlothNod";
    include('./nodboard.php');
    break;

  case 'about':
    $head_title="About - SlothNod";
    include('./html/about.html');
    break;

  case 'nodboard':
    $head_title="Nod Board - SlothNod";
    include('./nodboard.php');
    break;
    
  case 'yesterday':
    $head_title="Nod Board - SlothNod";
    include('./yesterday.php');
    break;

  case 'mostnodded':
    $head_title="Most Nodded - SlothNod";
    include('./mostnodded.php');
    break;


  case 'redirect':
    include('./redirect.php');
    break;

  case 'signin':
    $head_title="Sign in - SlothNod";
    include('./html/signin.html');
    break;


  case 'callback':
    include('./callback.php');
    break;
    
  case 'signout':
    include('./signout.php');
    break;

  case 'create_favorite':
    include('./create_favorite.php');
    break;

  default:
    include('./leaderboard.php');
}
$body_contents = ob_get_contents();
ob_end_clean();

include('./html/page.html');

?>
