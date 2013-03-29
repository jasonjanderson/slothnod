<?php

define('STATE', 'development');
define('VERSION', 'beta');
define('CONSUMER_KEY', 'iY5GwavKZc4yx3SA2Oz2IA');
define('CONSUMER_SECRET', 'y617QtnBQaviFF3iBjYGPJIbH22dS79ki9upGT8OE');
define('AVATAR_PER_TWEET', 15);
define('IN_MAINTENANCE_MODE', false);
define('TWEETS_PER_PAGE', 50);
define('DOCUMENT_ROOT', getcwd());

define('SLOTHNOD_FORMULA_MULTIPLIER', 0.001);
define('SLOTHNOD_FORMULA_MIN_NODS', 5);

/* Timeout session in 1 week */
define('SESSION_TIMEOUT', 604800);
define('SESSION_SALT', '9ePGGcIiXlgrHgmE81QBZ4WY8UW1ApfP7yJUh2OPYv5q2Wlbn063ZFwDTWXPf4e');

if (STATE == 'production') {
  define('OAUTH_CALLBACK', 'http://slothnod.com/callback');
  define('DB_HOST', 'localhost');
  define('DB_USER', 'slothnod');
  define('DB_NAME', 'slothnod');
  define('DB_PASSWORD', 'k3fgQ0pJibdQFZi4Dtv5rE9ObrMG8KoKfJMlv2XrRVMOTQDESe5wYebEIx7HCO7');

  define('CACHE_SERVER', 'localhost');
  define('CACHE_PORT', '11211');
} else {
  define('OAUTH_CALLBACK', 'http://twitter.nectro.com/callback');
  define('DB_HOST', 'localhost');
  define('DB_USER', 'slothnod');
  define('DB_NAME', 'slothnod');
  define('DB_PASSWORD', 'slothnod');

  define('CACHE_SERVER', 'localhost');
  define('CACHE_PORT', '11211');
}

?>
