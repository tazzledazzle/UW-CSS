CREATE DATABASE HappyHourDatabase;
USE HappyHourDatabase;


-- Table creation

CREATE TABLE HappyHourDatabase (
	happyHourID INT NOT NULL,
	PRIMARY KEY(happyHourID)
);

CREATE TABLE Restaurant (
	restaurantID INT NOT NULL, 
	happyHourID INT NOT NULL, 
	Menu VARCHAR(255),
	PRIMARY KEY(restaurantID)
);

CREATE TABLE Advertisement(
	advertisementID INT NOT NULL,
	restaurantID INT NOT NULL,
	Document VARCHAR(255),
	PRIMARY KEY(advertisementID)
);

CREATE TABLE Entertainment (
	entertainID INT NOT NULL,
	restaurantID INT NOT NULL,
	activityID INT NOT NULL,
	PRIMARY KEY(entertainID)
);

CREATE TABLE Activity(
	activityID INT NOT NULL,
	ActivityName VARCHAR(255) NOT NULL,
	ActivityDescription VARCHAR(255),
	ActivityPrice DOUBLE,
	PRIMARY KEY(activityID, ActivityName)
);

CREATE TABLE Schedule(
	scheduleID INT NOT NULL,
	locationID INT NOT NULL,
	activityID INT NOT NULL,
	day DATE,
	openTime DATE,
	closeTime DATE,
	PRIMARY KEY(scheduleID)
);

CREATE TABLE RestaurantLocation(
	restLocationID INT NOT NULL,
	restaurantID INT NOT NULL,
	locationID INT NOT NULL,
	PRIMARY KEY(restLocationID)
);

CREATE TABLE Location(
	locationID INT NOT NULL,
	Address VARCHAR(255),
	PRIMARY KEY(locationID)
);

CREATE TABLE Address(
	addressID INT NOT NULL,
	locationID INT NOT NULL,
	Street1 VARCHAR(255),
	Street2 VARCHAR(255),
	City VARCHAR(255),
	State VARCHAR(255),
	PostalCode INT(5),
	Phone INT(10),
	Fax INT(10),
	PRIMARY KEY(addressID, locationID)
);

CREATE TABLE Review(
	reviewID INT NOT NULL,
	restaurantID INT NOT NULL,
	userID INT NOT NULL,
	Comment VARCHAR(255),
	Rating INT,
	EstPriceRange VARCHAR(255),
	PRIMARY KEY(reviewID, restaurantID)
);

CREATE TABLE User(
	userID INT NOT NULL,
	UserName VARCHAR(255),
	PRIMARY KEY(userID)
);

CREATE TABLE Menu(
	menuID INT NOT NULL,
	PRIMARY KEY(menuID)
);

CREATE TABLE FoodItem(
	foodItemID INT NOT NULL,
	menuItemID INT NOT NULL,
	FoodItemName VARCHAR(255),
	FoodItemDesc VARCHAR(255),
	FoodItemPrice VARCHAR(255),
	PRIMARY KEY(foodItemID, menuItemID)
);

CREATE TABLE DrinkItem(
	drinkItemID INT NOT NULL,
	menuItemID INT NOT NULL,
	DrinkItemName VARCHAR(255),
	DrinkItemDesc VARCHAR(255),
	DrinkItemPrice VARCHAR(255),
	PRIMARY KEY(drinkItemID, menuItemID)
);

CREATE TABLE HappyHourItem(
	happyHourID INT NOT NULL,
	menuID INT NOT NULL,
	drinkItemID INT NOT NULL,
	foodItemID INT NOT NULL,
	Schedule VARCHAR(255),
	PRIMARY KEY(happyHourID, menuID)
);

CREATE TABLE MenuItem(
	menuItemID INT NOT NULL,
	menuID INT NOT NULL,
	MenuItemName VARCHAR(255),
	MenuItemDescription VARCHAR(255),
	MenuItemPrice VARCHAR(255),
	PRIMARY KEY(menuItemID, menuID)
);





-- foreign keys





ALTER TABLE Restaurant
ADD CONSTRAINT FOREIGN KEY (happyHourID) references HappyHourDatabase (happyHourID);


ALTER TABLE Advertisement
ADD CONSTRAINT FOREIGN KEY (restaurantID) references Restaurant (restaurantID);


ALTER TABLE Entertainment
ADD CONSTRAINT FOREIGN KEY (restaurantID) references Restaurant (restaurantID);

ALTER TABLE Entertainment
ADD CONSTRAINT FOREIGN KEY (activityID) references Activity (activityID);


ALTER TABLE Schedule
ADD CONSTRAINT FOREIGN KEY (locationID) references Location (locationID);

ALTER TABLE Schedule
ADD CONSTRAINT FOREIGN KEY (activityID) references Activity (activityID);


ALTER TABLE RestaurantLocation
ADD CONSTRAINT FOREIGN KEY (restaurantID) references Restaurant (restaurantID);

ALTER TABLE RestaurantLocation
ADD CONSTRAINT FOREIGN KEY (locationID) references Location (locationID);


ALTER TABLE Address
ADD CONSTRAINT FOREIGN KEY (locationID) references Location (locationID);


ALTER TABLE Review
ADD CONSTRAINT FOREIGN KEY (restaurantID) references Restaurant (restaurantID);

ALTER TABLE Review
ADD CONSTRAINT FOREIGN KEY (userID) references User (userID);


ALTER TABLE FoodItem
ADD CONSTRAINT FOREIGN KEY (menuItemID) references MenuItem (menuItemID);


ALTER TABLE DrinkItem
ADD CONSTRAINT FOREIGN KEY (menuItemID) references MenuItem (menuItemID);


ALTER TABLE HappyHourItem
ADD CONSTRAINT FOREIGN KEY (drinkItemID) REFERENCES DrinkItem (drinkItemID);

ALTER TABLE HappyHourItem
ADD CONSTRAINT FOREIGN KEY (foodItemID) REFERENCES FoodItem (foodItemID);

ALTER TABLE HappyHourItem
ADD CONSTRAINT FOREIGN KEY (menuID) references Menu (menuID);


ALTER TABLE MenuItem
ADD CONSTRAINT FOREIGN KEY (menuID) references Menu (menuID);

-- end