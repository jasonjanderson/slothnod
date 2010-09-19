<?php

define('STATE', 'development');
define('VERSION', 'beta');
define('CONSUMER_KEY', 'iY5GwavKZc4yx3SA2Oz2IA');
define('CONSUMER_SECRET', 'y617QtnBQaviFF3iBjYGPJIbH22dS79ki9upGT8OE');
define('AVATAR_PER_TWEET', 15);

if (STATE == 'production') {
  define('OAUTH_CALLBACK', 'http://slothnod.com/callback');
  define('DB_HOST', 'localhost');
  define('DB_USERNAME', 'slothnod');
  define('DB_NAME', 'slothnod');
  define('DB_PASSWORD', 'k3fgQ0pJibdQFZi4Dtv5rE9ObrMG8KoKfJMlv2XrRVMOTQDESe5wYebEIx7HCO7');
} else {
  define('OAUTH_CALLBACK', 'http://localhost:8080/callback');
  define('DB_HOST', 'localhost');
  define('DB_USERNAME', 'slothnod');
  define('DB_NAME', 'slothnod');
  define('DB_PASSWORD', 'slothnod');
}

?>
