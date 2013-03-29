<?php
require_once('./include/bootstrap.inc');

$bootstrap = Bootstrap::get_instance();
$bootstrap->init_minimal();

$route = URL::pop();
switch ($route) {
  case '':
    $title="Nod Board - SlothNod";
    Page::render('./nodboard.php', './html/page.html', $title);
    break;

  case 'about':
    $title="About - SlothNod";
    $page = './html/about.html';
    Page::render('./html/about.html', './html/page.html', $title);
    break;

  case 'yesterday':
    $title="Yesterday - SlothNod";
    Page::render('./yesterday.php', './html/page.html', $title);
    break;

  case 'heavynods':
    $title="Heavy Nods - SlothNod";
    Page::render('./heavynods.php', './html/page.html', $title);
    break;

  case 'redirect':
    $page = './redirect.php';
    break;

  case 'signin':
    $title="Sign in - SlothNod";
    Page::render('./signin.php', './html/page.html', $title);
    break;

  case 'callback':
    Page::render('./callback.php');
    break;
    
  case 'signout':
    Page::render('./signout.php');
    break;

  case 'create_favorite':
    Page::render('./create_favorite.php');
    break;

  case 'destroy_favorite':
    Page::render('./destroy_favorite.php');
    break;

  case 'retweet':
    Page::render('./retweet.php');
    break;


  case 'nodders':
    include('./nodders.php');
    break;

  case 'create_follow':
    Page::render('./create_follow.php');
    break;

  case 'cachestats':
    include('./cachestats.php');
    break;

  default:
    if (!is_numeric($route)) {
      URL::redirect('/');
    }
    URL::reset();
    $title="Nod Board - SlothNod";
    Page::render('./nodboard.php', './html/page.html', $title);
}

?>
