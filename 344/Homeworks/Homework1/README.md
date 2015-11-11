# CSE 344 Homework 1: SQLITE

### Objectives:
To be able to create and manipulate tables in sqlite3.
### Assignment tools:
SQLite 3
### Due date:
Thursday, October 8, 2015 by 11:00pm. Turn in your solution using the assignment drop box linked from the main course web page.
#### What to turn in:
A file containing all of your SQL and SQLite commands, and SQL comments for your responses that are not in SQL (i.e., submit a .sql file that can be executed directly against the database system). No need to include any inputs nor outputs.
#### Motivation: 
We will use SQLite for this assignment. SQLite is a software library that implements a SQL database engine. We will use SQLite in this assignment because it offers an extremely lightweight method to create and analyze structured datasets (by structured we mean datasets in the form of tables rather than, say, free text). Using SQLite is a minimal hassle approach to realizing the benefits of a relational database management system. Of course, SQLite does not do everything, but we will get to that point in later assignments. In the meantime, you can also check a page that describes when to use SQLite and when not to use it.

#### Extra Resources :

Some important SQLite commands:
to view help contents: ".help"
to view a list of all your tables: ".tables"
to exit: ".exit" 

This page provides a simple guide for commonly used command-line functions in SQLite. 

This page provides more information on formatting output in SQLite. 

This page provides an index of more detailed information for SQL commands in SQLite.
Assignment Details:

To run SQLite do the following:

* on Mac OS X or Linux, open a terminal and type sqlite3
* on Windows, there are two reasonable options:
	* Install the stand-alone windows program from the sqlite web site (precompiled windows command-line shell on the download page), or (mabye a bit more complicated):
	* Install cygwin to get a linux command shell, then open cygwin and type sqlite3 (you may have to install it by running setup --> database --> sqlite3; it is probably already installed in the CSE labs).
(see how easy it is to get started!)

[5 points] 
First, create a simple table using the following steps:
* Create a table Edges(Source,Destination) where both Source and Destination are integers.
* Insert the tuples (10,5), (6,25), (1,3), (4, 4)
* Write a SQL statement that returns all tuples
* Write a SQL statement that returns only column Source for all tuples
* Write a SQL statement that returns all tuples where Source > Destination
* Tricky question (check the documentation here: http://www.sqlite.org/datatype3.html): Now insert the tuple ('-1','2000'). Do you get an error? Why?

For the next question you will be asked to create tables with attributes of types integer, varchar, date, and Boolean. However, SQL Lite does not have date and Boolean: you will use varchar and int instead:

0 (false) and 1 (true) are the values used to interpret Booleans.
Date strings in SQLite are in the form: 'YYYY-MM-DD'.
Examples of valid date strings include: '1988-01-15', '0000-12-31', and '2011-03-28'.
Examples of invalid date strings include: '11-11-01', '1900-1-20', '2011-03-5', and '2011-03-50'.
Examples of date operations on date strings (try them):
* select date('2011-03-28'); 
* select date('now');
* select date('now', '-5 year');
* select date('now', '-5 year', '+24 hour'); 
* select case when date('now') < date('2011-12-09') then 'Taking classes' when date('now') < date('2011-12-16') then 'Exams' else 'Vacation' end; 

[3 points] Create a table called MyRestaurants with the following attributes: 
* Name of the restaurant: a varchar field
* Type of food they make: a varchar field
* Distance (in minutes) from your house: an integer
* Date of your last visit: a varchar field, interpreted as date
* Whether you like it or not: an integer, interpreted as a Boolean

[3 points] Insert at least five tuples using the SQL INSERT command five (or more) times. You should insert at least one restaurant you liked, at least one restaurant you did not like, and at least one restaurant where you leave the iLike field NULL.

[3 points] Write a SQL query that returns all restaurants in your table. Experiment with a few of SQLite's output formats:
* print the results in comma-separated form
* print the results in list form, delimited by " | "
* print the results in column form, and make each column have width 15
* for each of the formats above, try printing/not printing the column headers with the results


[3 points] Write a SQL query that returns only the name and distance of all restaurants within and including 20 minutes of your house. The query should list the restaurants in alphabetical order of names.

[3 points] Write a SQL query that returns all restaurants that you like, but have not visited since more than 3 months ago.