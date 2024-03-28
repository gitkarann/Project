-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Feb 09, 2023 at 12:05 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `coursework`
--

-- --------------------------------------------------------

--
-- Table structure for table `assigned_modules`
--

CREATE TABLE `assigned_modules` (
  `Teacher_Name` varchar(225) NOT NULL,
  `Module_1` varchar(225) NOT NULL,
  `Module_2` varchar(225) NOT NULL,
  `Module_3` varchar(225) NOT NULL,
  `Module_4` varchar(225) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `assigned_modules`
--

INSERT INTO `assigned_modules` (`Teacher_Name`, `Module_1`, `Module_2`, `Module_3`, `Module_4`) VALUES
('Sajan Siwakoti', 'OODP', 'FOC', 'JDBC', 'Database'),
('Kapil Shrestha', 'PHP', 'FOC', 'Computational Mathematics', 'Database'),
('Binod Chaudhary', 'Business Analytics', 'HR Basics', 'Principles of Business', 'International Rrelations'),
('Biplav Party', 'Project Business', 'Capital Finance', 'Marketing', 'Principles of Business');


-- --------------------------------------------------------

--
-- Table structure for table `course`
--

CREATE TABLE `course` (
  `Course_id` int(225) NOT NULL,
  `Course_Name` varchar(225) NOT NULL,
  `No_Of_Modules` varchar(225) NOT NULL,
  `Active_Status` varchar(225) NOT NULL,
  `Length` int(225) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `course`
--

INSERT INTO `course` (`Course_id`, `Course_Name`, `No_Of_Modules`, `Active_Status`, `Length`) VALUES
(8, 'BSc Computer Science', '14', 'YES', 3),
(16, 'BSc International Business', '12', 'YES', 4),
(24, 'BBA', '16', 'NO', 4),
(140, 'CSIT', '10', 'NO', 3),
(201, 'MBA', '11', 'NO', 2);

-- --------------------------------------------------------

--
-- Table structure for table `marks`
--

CREATE TABLE `marks` (
  `student_id` int(225) NOT NULL,
  `Student_Name` varchar(225) NOT NULL,
  `Level` varchar(225) NOT NULL,
  `Module_1` int(225) NOT NULL,
  `Module_2` int(225) NOT NULL,
  `Module_3` int(225) NOT NULL,
  `Module_4` int(225) NOT NULL,
  `Module_5` int(225) NOT NULL,
  `Module_6` int(225) NOT NULL,
  `Module_7` int(225) NOT NULL,
  `Module_8` int(225) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `marks`
--

INSERT INTO `marks` (`student_id`, `Student_Name`, `Level`, `Module_1`, `Module_2`, `Module_3`, `Module_4`, `Module_5`, `Module_6`, `Module_7`, `Module_8`) VALUES
(31, 'Karan Sah', '5', 78, 79, 80, 82, 72, 75, 76, 77),
(32, 'Rem Bikram', '5', 99, 98, 96, 92, 85, 86, 94, 95 ),
(32, 'Chetan Bhandari', '6', 85, 45, 45, 58, 98, 96, 45, 87),
(42, 'Bhagat Narayan', '4', 78, 96, 85, 45, 87, 88, 86, 71);


-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE `student` (
  `Id` int(225) NOT NULL,
  `Student_Name` varchar(225) NOT NULL,
  `Semester` varchar(225) NOT NULL,
  `Level` varchar(225) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`Id`, `Student_Name`, `Semester`, `Level`) VALUES
(31, 'Karan Sah', '3', '5'),
(32, 'Rem Bikram', '6', '5'),
(32, 'Chetan Bhandari', '6', '6'),
(42, 'Bhagat Narayan', '2', '4');


-- --------------------------------------------------------

--
-- Table structure for table `tutor`
--

CREATE TABLE `tutor` (
  `ID` int(225) NOT NULL,
  `Name` varchar(225) NOT NULL,
  `Phone_Number` bigint(225) NOT NULL,
  `Address` varchar(225) NOT NULL,
  `Sex` varchar(225) NOT NULL,
  `Module_Assigned` varchar(225) NOT NULL,
  `Date_Of_Birth` date NOT NULL,
  `Full_Time` varchar(225) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tutor`
--

INSERT INTO `tutor` (`ID`, `Name`, `Phone_Number`, `Address`, `Sex`, `Module_Assigned`, `Date_Of_Birth`, `Full_Time`) VALUES
(20, 'Amrish Puri', 78954, 'Tokha', 'Female', 'ISA', '1998-01-23', 'NO'),
(21, 'Kajol Bhattarai', 524689, 'Lalitpur', 'Female', 'OODP', '199-0123', 'YES'),
(22, 'Himal Pandey', 98165156, 'Bhaktapur', 'Male', 'AI', '2001-12-01', 'YES');


-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `User_Id` int(225) NOT NULL,
  `FullName` text NOT NULL,
  `Sex` varchar(225) NOT NULL,
  `Username` varchar(225) NOT NULL,
  `Password` varchar(225) NOT NULL,
  `Course` varchar(225) NOT NULL,
  `User_Type` varchar(225) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`User_Id`, `FullName`, `Sex`, `Username`, `Password`, `Course`, `User_Type`) VALUES
(254, 'Mahesh Babu', 'Male', 'babuMahesh', '12857', 'BIBM', 'Teacher'),
(458, 'Imran Hasmi', 'Male', 'Hashmi', 'ijfdsiji', 'BIT', 'Student'),
(12, 'Admin', 'Male', 'Admin', 'Admin', ' ', 'Admin'),
(111, 'Karan Sah', 'Male', 'Sah', 'djfihdf', 'BIT', 'Student'),
(111, 'Karan Sah', 'Male', 'Sah', 'djfihdf', 'BIT', 'Student');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `course`
--
ALTER TABLE `course`
  ADD PRIMARY KEY (`Course_id`);

--
-- Indexes for table `marks`
--
ALTER TABLE `marks`
  ADD PRIMARY KEY (`student_id`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `tutor`
--
ALTER TABLE `tutor`
  ADD PRIMARY KEY (`Id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`User_Id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `course`
--
ALTER TABLE `course`
  MODIFY `Course_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `marks`
--
ALTER TABLE `marks`
  MODIFY `student_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `student`
--
ALTER TABLE `student`
  MODIFY `Id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `tutor`
--
ALTER TABLE `tutor`
  MODIFY `Id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `User_Id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
