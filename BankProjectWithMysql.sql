CREATE TABLE `membertbl` (
  `useraccnum` int unsigned NOT NULL,
  `username` varchar(10) NOT NULL,
  `userssn` varchar(14) NOT NULL,
  `userphone` varchar(11) NOT NULL,
  `userpass` char(4) NOT NULL,
  `userage` int NOT NULL,
  PRIMARY KEY (`useraccnum`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `membermoneytbl` (
  `num` int NOT NULL AUTO_INCREMENT,
  `useraccnum` int unsigned NOT NULL,
  `inputmoney` int NOT NULL,
  `outputmoney` int NOT NULL,
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`num`),
  KEY `useraccnum` (`useraccnum`),
  CONSTRAINT `membermoneytbl_ibfk_1` FOREIGN KEY (`useraccnum`) REFERENCES `membertbl` (`useraccnum`)
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
