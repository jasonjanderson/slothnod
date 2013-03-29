#!/bin/sh

sudo cat >> /etc/apt/sources.list << EOF

## LAMP Stable Updates ##
deb http://php53.dotdeb.org stable all
deb-src http://php53.dotdeb.org stable all
EOF
sudo wget http://www.dotdeb.org/dotdeb.gpg
sudo cat dotdeb.gpg | sudo apt-key add -

sudo apt-get install memcached php5-memcache python-memcache
sudo /etc/init.d/apache2 restart
sudo apt-get update
sudo apt-get dist-upgrade

exit 0
