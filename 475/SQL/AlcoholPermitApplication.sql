CREATE DATABASE AcloholPermitApplication;

-- Table Creation
CREATE TABLE PermitRequest (
	RequestID INT NOT NULL AUTO_INCREMENT,
	PermitID INT,
	PermitTypeCode VARCHAR(25),
	RequestDate DATE,
	NotaryID INT,
	EventID INT
	PRIMARY KEY(RequestID)
);

CREATE TABLE Permit (
	PermitID INT NOT NULL AUTO_INCREMENT,
	PermitTypeCode VARCHAR(25),
	PermitNumber INT,
	IssueDate DATE
	PRIMARY KEY(PermitID)
);

CREATE TABLE Notary (
	NotaryID INT NOT NULL AUTO_INCREMENT,
	NotaryName VARCHAR(255),
	NotaryNo INT,
	ExpirationDate DATE,
	LocationID INT,
	PRIMARY KEY(NotaryID) 
);

-- PermitBeveragen TODO
-- Beveragen TODO
-- BeverageTypen TODO
-- Providern TODO
-- Eventn TODO
-- EventDayn TODO
-- Recipientn TODO
-- Entityn TODO
-- Appplicantn TODO
-- Contactn TODO
-- Locationn TODO
-- Staten TODO

-- Foriegn keys

ALTER TABLE PermitRequest
ADD CONSTRAINT FOREIGN KEY(PermitID) REFERENCES Permit(PermitID);
ADD CONSTRAINT FOREIGN KEY(PermitTypeCode) REFERENCES PermitType(PermitTypeCode);
ADD CONSTRAINT FOREIGN KEY(NotaryID) REFERENCES Notary(NotaryID);
ADD CONSTRAINT FOREIGN KEY(EventID) REFERENCES Event(EventID);

ALTER TABLE Permit 
ADD CONSTRAINT FOREIGN KEY(PermitTypeCode) REFERENCES PermitType(PermitTypeCode);
