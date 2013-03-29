-- MySQL dump 10.11
--
-- Host: localhost    Database: slothnod
-- ------------------------------------------------------
-- Server version	5.0.51a-24+lenny4

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `favorite`
--

DROP TABLE IF EXISTS `favorite`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `favorite` (
  `status_id` bigint(20) NOT NULL,
  `user_id` bigint(20) NOT NULL,
  `favorite_date` datetime default NULL,
  PRIMARY KEY  (`status_id`,`user_id`),
  KEY `index_favorite_status_id` (`status_id`),
  KEY `index_favorite_user_id` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `leaderboard`
--

DROP TABLE IF EXISTS `leaderboard`;
/*!50001 DROP VIEW IF EXISTS `leaderboard`*/;
/*!50001 CREATE TABLE `leaderboard` (
  `status_id` bigint(19) unsigned,
  `text` varchar(255),
  `post_date` datetime,
  `leaderboard_date` bigint(10),
  `anonymous` bigint(11),
  `user_id` bigint(20),
  `username` varchar(255),
  `img_url` varchar(512),
  `followers` int(11),
  `following` int(11)
) */;

--
-- Temporary table structure for view `most_nodded`
--

DROP TABLE IF EXISTS `most_nodded`;
/*!50001 DROP VIEW IF EXISTS `most_nodded`*/;
/*!50001 CREATE TABLE `most_nodded` (
  `status_id` bigint(19) unsigned,
  `user_id` bigint(19) unsigned,
  `text` varchar(255),
  `post_date` datetime,
  `on_leaderboard` tinyint(1),
  `leaderboard_date` datetime,
  `img_url` varchar(512),
  `following` int(11),
  `followers` int(11),
  `username` varchar(255),
  `nodded` bigint(21),
  `anonymous` bigint(11)
) */;

--
-- Temporary table structure for view `next_leaderboard`
--

DROP TABLE IF EXISTS `next_leaderboard`;
/*!50001 DROP VIEW IF EXISTS `next_leaderboard`*/;
/*!50001 CREATE TABLE `next_leaderboard` (
  `status_id` bigint(20),
  `favorite_count` bigint(21),
  `followers` int(11),
  `following` int(11),
  `sloth_form` decimal(16,5),
  `on_leaderboard` tinyint(1)
) */;

--
-- Temporary table structure for view `next_nodboard`
--

DROP TABLE IF EXISTS `next_nodboard`;
/*!50001 DROP VIEW IF EXISTS `next_nodboard`*/;
/*!50001 CREATE TABLE `next_nodboard` (
  `status_id` bigint(20),
  `user_id` bigint(20),
  `text` varchar(255),
  `favorite_count` bigint(21),
  `followers` int(11),
  `following` int(11),
  `sloth_form` decimal(14,3),
  `on_leaderboard` tinyint(1)
) */;

--
-- Table structure for table `nodboard`
--

DROP TABLE IF EXISTS `nodboard`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `nodboard` (
  `status_id` bigint(20) unsigned NOT NULL,
  `user_id` bigint(20) unsigned NOT NULL,
  `nodboard_date` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`status_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `session`
--

DROP TABLE IF EXISTS `session`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `session` (
  `id` varchar(32) NOT NULL default '',
  `data` blob NOT NULL,
  `last_accessed` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `session_data`
--

DROP TABLE IF EXISTS `session_data`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `session_data` (
  `session_id` varchar(32) NOT NULL default '',
  `http_user_agent` varchar(32) NOT NULL default '',
  `session_data` blob NOT NULL,
  `session_expire` int(11) NOT NULL default '0',
  PRIMARY KEY  (`session_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `sessions`
--

DROP TABLE IF EXISTS `sessions`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `sessions` (
  `id` char(32) NOT NULL,
  `data` longtext NOT NULL,
  `last_accessed` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `status`
--

DROP TABLE IF EXISTS `status`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `status` (
  `id` bigint(19) unsigned NOT NULL,
  `user_id` bigint(19) unsigned NOT NULL,
  `text` varchar(255) default NULL,
  `post_date` datetime default NULL,
  `on_leaderboard` tinyint(1) default NULL,
  `leaderboard_date` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `user` (
  `id` bigint(20) NOT NULL,
  `username` varchar(255) default NULL,
  `following` int(11) default NULL,
  `followers` int(11) default NULL,
  `join_date` timestamp NOT NULL default '0000-00-00 00:00:00',
  `oauth_token` varchar(255) default NULL,
  `oauth_secret` varchar(255) default NULL,
  `img_url` varchar(512) default NULL,
  `active` tinyint(1) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `user_exclude`
--

DROP TABLE IF EXISTS `user_exclude`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `user_exclude` (
  `id` bigint(20) NOT NULL,
  `username` varchar(255) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `user_include`
--

DROP TABLE IF EXISTS `user_include`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `user_include` (
  `id` bigint(20) NOT NULL,
  `username` varchar(255) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `yesterday_board`
--

DROP TABLE IF EXISTS `yesterday_board`;
/*!50001 DROP VIEW IF EXISTS `yesterday_board`*/;
/*!50001 CREATE TABLE `yesterday_board` (
  `status_id` bigint(19) unsigned,
  `text` varchar(255),
  `post_date` datetime,
  `leaderboard_date` bigint(10),
  `anonymous` bigint(11),
  `user_id` bigint(20),
  `username` varchar(255),
  `img_url` varchar(512),
  `followers` int(11),
  `following` int(11)
) */;

--
-- Final view structure for view `leaderboard`
--

/*!50001 DROP TABLE `leaderboard`*/;
/*!50001 DROP VIEW IF EXISTS `leaderboard`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`slothnod`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `leaderboard` AS select `status`.`id` AS `status_id`,`status`.`text` AS `text`,`status`.`post_date` AS `post_date`,unix_timestamp(`status`.`leaderboard_date`) AS `leaderboard_date`,(unix_timestamp(utc_date()) - unix_timestamp(`status`.`leaderboard_date`)) AS `anonymous`,`user`.`id` AS `user_id`,`user`.`username` AS `username`,`user`.`img_url` AS `img_url`,`user`.`followers` AS `followers`,`user`.`following` AS `following` from (`status` left join `user` on((`status`.`user_id` = `user`.`id`))) where (`status`.`on_leaderboard` = 1) */;

--
-- Final view structure for view `most_nodded`
--

/*!50001 DROP TABLE `most_nodded`*/;
/*!50001 DROP VIEW IF EXISTS `most_nodded`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`slothnod`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `most_nodded` AS select `status`.`id` AS `status_id`,`status`.`user_id` AS `user_id`,`status`.`text` AS `text`,`status`.`post_date` AS `post_date`,`status`.`on_leaderboard` AS `on_leaderboard`,`status`.`leaderboard_date` AS `leaderboard_date`,`user`.`img_url` AS `img_url`,`user`.`following` AS `following`,`user`.`followers` AS `followers`,`user`.`username` AS `username`,count(`favorite`.`status_id`) AS `nodded`,(unix_timestamp(utc_date()) - unix_timestamp(`status`.`leaderboard_date`)) AS `anonymous` from ((`status` join `user` on((`status`.`user_id` = `user`.`id`))) join `favorite` on((`status`.`id` = `favorite`.`status_id`))) group by `status`.`id` having (`status`.`on_leaderboard` = 1) order by count(`favorite`.`status_id`) desc limit 100 */;

--
-- Final view structure for view `next_leaderboard`
--

/*!50001 DROP TABLE `next_leaderboard`*/;
/*!50001 DROP VIEW IF EXISTS `next_leaderboard`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`slothnod`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `next_leaderboard` AS select `favorite`.`status_id` AS `status_id`,count(`favorite`.`status_id`) AS `favorite_count`,`user`.`followers` AS `followers`,`user`.`following` AS `following`,(`user`.`followers` * 0.00666) AS `sloth_form`,`status`.`on_leaderboard` AS `on_leaderboard` from ((`favorite` join `status` on((`favorite`.`status_id` = `status`.`id`))) join `user` on((`status`.`user_id` = `user`.`id`))) group by `status`.`id` having ((`favorite_count` >= 3) and (`favorite_count` >= `sloth_form`) and (`user`.`followers` > 0) and (`status`.`on_leaderboard` = 0)) */;

--
-- Final view structure for view `next_nodboard`
--

/*!50001 DROP TABLE `next_nodboard`*/;
/*!50001 DROP VIEW IF EXISTS `next_nodboard`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`slothnod`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `next_nodboard` AS select `favorite`.`status_id` AS `status_id`,`user`.`id` AS `user_id`,`status`.`text` AS `text`,count(`favorite`.`status_id`) AS `favorite_count`,`user`.`followers` AS `followers`,`user`.`following` AS `following`,(`user`.`followers` * 0.001) AS `sloth_form`,`status`.`on_leaderboard` AS `on_leaderboard` from ((`favorite` join `status` on((`favorite`.`status_id` = `status`.`id`))) join `user` on((`status`.`user_id` = `user`.`id`))) group by `status`.`id` having ((`favorite_count` >= 5) and (`favorite_count` >= `sloth_form`) and (`user`.`followers` > 0) and (not(`favorite`.`status_id` in (select `nodboard`.`status_id` AS `status_id` from `nodboard`)))) */;

--
-- Final view structure for view `yesterday_board`
--

/*!50001 DROP TABLE `yesterday_board`*/;
/*!50001 DROP VIEW IF EXISTS `yesterday_board`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`slothnod`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `yesterday_board` AS select `status`.`id` AS `status_id`,`status`.`text` AS `text`,`status`.`post_date` AS `post_date`,unix_timestamp(`status`.`leaderboard_date`) AS `leaderboard_date`,(unix_timestamp(utc_date()) - unix_timestamp(`status`.`leaderboard_date`)) AS `anonymous`,`user`.`id` AS `user_id`,`user`.`username` AS `username`,`user`.`img_url` AS `img_url`,`user`.`followers` AS `followers`,`user`.`following` AS `following` from (`status` left join `user` on((`status`.`user_id` = `user`.`id`))) where ((`status`.`on_leaderboard` = 1) and ((unix_timestamp(utc_date()) - unix_timestamp(`status`.`leaderboard_date`)) < 86400) and ((unix_timestamp(utc_date()) - unix_timestamp(`status`.`leaderboard_date`)) > 0)) */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-05-23  1:04:34
