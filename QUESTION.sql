-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2014-06-11 07:03:28
-- 服务器版本: 5.5.37-0ubuntu0.14.04.1
-- PHP 版本: 5.5.9-1ubuntu4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `DB`
--

-- --------------------------------------------------------

--
-- 表的结构 `QUESTION`
--

CREATE TABLE IF NOT EXISTS `QUESTION` (
  `QUESTION_ID` varchar(32) NOT NULL,
  `QUESTION_TYPE_ID` varchar(16) NOT NULL,
  `QUESTION_TYPE_NAME` varchar(64) NOT NULL,
  `USER_ID` int(11) NOT NULL,
  `USER_NAME` varchar(64) NOT NULL,
  `QUESTION_TITLE` varchar(64) NOT NULL,
  `QUESTION_FILE_PATH` varchar(255) NOT NULL,
  `QUESTION_FILE_NAME` varchar(64) NOT NULL,
  `QUESTION_SUBMIT_DATE` date NOT NULL,
  PRIMARY KEY (`QUESTION_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `QUESTION`
--

INSERT INTO `QUESTION` (`QUESTION_ID`, `QUESTION_TYPE_ID`, `QUESTION_TYPE_NAME`, `USER_ID`, `USER_NAME`, `QUESTION_TITLE`, `QUESTION_FILE_PATH`, `QUESTION_FILE_NAME`, `QUESTION_SUBMIT_DATE`) VALUES
('00010001000100000000000000001001', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Poker Shuffle', '/temp/2013Changchun/', '2013Changchun Online1001.pdf', '2014-06-01'),
('00010001000100000000000000001002', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Good Firewall', '/temp/2013Changchun/', '2013Changchun Online1002.pdf', '2014-06-01'),
('00010001000100000000000000001003', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Sky', '/temp/2013Changchun/', '2013Changchun Online1003.pdf', '2014-06-01'),
('00010001000100000000000000001004', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Cut the Cake', '/temp/2013Changchun/', '2013Changchun Online1004.pdf', '2014-06-01'),
('00010001000100000000000000001005', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Theme Section', '/temp/2013Changchun/', '2013Changchun Online1005.pdf', '2014-06-01'),
('00010001000100000000000000001006', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Stone', '/temp/2013Changchun/', '2013Changchun Online1006.pdf', '2014-06-01'),
('00010001000100000000000000001007', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Tsp', '/temp/2013Changchun/', '2013Changchun Online1007.pdf', '2014-06-01'),
('00010001000100000000000000001008', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Network', '/temp/2013Changchun/', '2013Changchun Online1008.pdf', '2014-06-01'),
('00010001000100000000000000001009', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Bell', '/temp/2013Changchun/', '2013Changchun Online1009.pdf', '2014-06-01'),
('00010001000100000000000000001010', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Flyer', '/temp/2013Changchun/', '2013Changchun Online1010.pdf', '2014-06-01'),
('00010001000100000000000000001011', '0001000100010000', '2013长春赛区', 2, '2013长春赛区', 'Sword', '/temp/2013Changchun/', '2013Changchun Online1011.pdf', '2014-06-01'),
('00010001000200000000000000001001', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'A Game in the Hospital', '/temp/2013Chengdu/', '2013Chengdu Online1001.pdf', '2014-06-01'),
('00010001000200000000000000001002', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'An Easy Problem for Elfness ', '/temp/2013Chengdu/', '2013Chengdu Online1002.pdf', '2014-06-01'),
('00010001000200000000000000001003', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'We Love MOE Girls ', '/temp/2013Chengdu/', '2013Chengdu Online1003.pdf', '2014-06-01'),
('00010001000200000000000000001004', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'Minimum palindrome', '/temp/2013Chengdu/', '2013Chengdu Online1004.pdf', '2014-06-01'),
('00010001000200000000000000001005', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'Round Table', '/temp/2013Chengdu/', '2013Chengdu Online1005.pdf', '2014-06-01'),
('00010001000200000000000000001006', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'G(x)', '/temp/2013Chengdu/', '2013Chengdu Online1006.pdf', '2014-06-01'),
('00010001000200000000000000001007', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'F(x)', '/temp/2013Chengdu/', '2013Chengdu Online1007.pdf', '2014-06-01'),
('00010001000200000000000000001008', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'Little Wish~ lyrical step~', '/temp/2013Chengdu/', '2013Chengdu Online1008.pdf', '2014-06-01'),
('00010001000200000000000000001009', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'This Is The Job The Bear Finds', '/temp/2013Chengdu/', '2013Chengdu Online1009.pdf', '2014-06-01'),
('00010001000200000000000000001010', '0001000100020000', '2013成都赛区', 3, '2013成都赛区', 'A Bit Fun', '/temp/2013Chengdu/', '2013Chengdu Online1010.pdf', '2014-06-01'),
('00010001000300000000000000001001', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Caocao''s Bridges', '/temp/2013Hangzhou/', '2013Hangzhou Online1001.pdf', '2014-06-01'),
('00010001000300000000000000001002', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Zhuge Liang''s Mines', '/temp/2013Hangzhou/', '2013Hangzhou Online1002.pdf', '2014-06-01'),
('00010001000300000000000000001003', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'The Donkey of Gui ZHou', '/temp/2013Hangzhou/', '2013Hangzhou Online1003.pdf', '2014-06-01'),
('00010001000300000000000000001004', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Save Labman No.004', '/temp/2013Hangzhou/', '2013Hangzhou Online1004.pdf', '2014-06-01'),
('00010001000300000000000000001005', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Pinball Game 3D', '/temp/2013Hangzhou/', '2013Hangzhou Online1005.pdf', '2014-06-01'),
('00010001000300000000000000001006', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Sparrow', '/temp/2013Hangzhou/', '2013Hangzhou Online1006.pdf', '2014-06-01'),
('00010001000300000000000000001007', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Starloop System', '/temp/2013Hangzhou/', '2013Hangzhou Online1007.pdf', '2014-06-01'),
('00010001000300000000000000001008', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Two Rabbits', '/temp/2013Hangzhou/', '2013Hangzhou Online1008.pdf', '2014-06-01'),
('00010001000300000000000000001009', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Mophues', '/temp/2013Hangzhou/', '2013Hangzhou Online1009.pdf', '2014-06-01'),
('00010001000300000000000000001010', '0001000100030000', '2013杭州赛区', 4, '2013杭州赛区', 'Mex', '/temp/2013Hangzhou/', '2013Hangzhou Online1010.pdf', '2014-06-01'),
('00010001000400000000000000001001', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Area', '/temp/2013Nanjing/', '2013Nanjing Online1009.pdf', '2014-06-01'),
('00010001000400000000000000001002', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Parade Show', '/temp/2013Nanjing/', '2013Nanjing Online1002.pdf', '2014-06-01'),
('00010001000400000000000000001003', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Count The Pairs', '/temp/2013Nanjing/', '2013Nanjing Online1003.pdf', '2014-06-01'),
('00010001000400000000000000001004', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Divide Groups', '/temp/2013Nanjing/', '2013Nanjing Online1004.pdf', '2014-06-01'),
('00010001000400000000000000001005', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Polygon', '/temp/2013Nanjing/', '2013Nanjing Online1005.pdf', '2014-06-01'),
('00010001000400000000000000001006', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Fishhead''s Little Game', '/temp/2013Nanjing/', '2013Nanjing Online1006.pdf', '2014-06-01'),
('00010001000400000000000000001007', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Spacecraft Monitoring', '/temp/2013Nanjing/', '2013Nanjing Online1007.pdf', '2014-06-01'),
('00010001000400000000000000001008', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Heroes of Might and Magic', '/temp/2013Nanjing/', '2013Nanjing Online1008.pdf', '2014-06-01'),
('00010001000400000000000000001009', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Install Air Conditioning', '/temp/2013Nanjing/', '2013Nanjing Online1009.pdf', '2014-06-01'),
('00010001000400000000000000001010', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Tree', '/temp/2013Nanjing/', '2013Nanjing Online1010.pdf', '2014-06-01'),
('00010001000400000000000000001011', '0001000100040000', '2013南京赛区', 5, '2013南京赛区', 'Walk Through Squares', '/temp/2013Nanjing/', '2013Nanjing Online1011.pdf', '2014-06-01');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
