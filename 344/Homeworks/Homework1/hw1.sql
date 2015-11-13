

# create table Edges
CREATE TABLE Edges(Source INTEGER, Destination INTEGER);

# insert (10, 5), (6, 25), (1,3), (4,4)
INSERT INTO Edges(Source, Destination) VALUES (10,5);\
INSERT INTO Edges(Source, Destination) VALUES (6,25);\
INSERT INTO Edges(Source, Destination) VALUES (1,3);\
INSERT INTO Edges(Source, Destination) VALUES (4,4);

# return all tuples
SELECT * FROM Edges;

# return column Source for tuples
SELECT Source FROM Edges;

# * Write a SQL statement that returns all tuples where Source > Destination
SELECT Source FROM Edges WHERE Source > Destination;

# tricky question
INSERT INTO Edges(Source, Destination) VALUES ('-1', '2000'); 
# this works because of Integer bounds go negative and the strings are 
# interpreted as integer values



# Create a table called MyRestaurants with the following attributes: 
-- * Name of the restaurant: a varchar field
-- * Type of food they make: a varchar field
-- * Distance (in minutes) from your house: an integer
-- * Date of your last visit: a varchar field, interpreted as date
-- * Whether you like it or not: an integer, interpreted as a Boolean
CREATE TABLE MyRestaurants(
	Name VARCHAR,
	FoodType VARCHAR,
	Distance INTEGER,
	LastVisit VARCHAR,
	Liked	INTEGER
);


# five restaurants inserted, one you liked, one you hated, and one that's null
INSERT INTO MyRestaurants(Name, FoodType, Distance, LastVisit, Liked) VALUES ('Dantes', 'American', 45, '10-10-14', 1);
INSERT INTO MyRestaurants(Name, FoodType, Distance, LastVisit, Liked) VALUES ('McDonalds', 'Fast Food', 10, '09-10-15', 0);
INSERT INTO MyRestaurants(Name, FoodType, Distance, LastVisit, Liked) VALUES ('El Sabor', 'Mexican', 5, '11-10-15', NULL);