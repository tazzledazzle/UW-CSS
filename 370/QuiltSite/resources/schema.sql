create table Forums (
    forumID int not null, --pk
);
create table ForumPosts (
    forumMemberID int not null, --pk
    forumID int not null, --fk
    userID int, --fk
    
);
create table FourmMembers (
    forumMemberID int not null auto_increment, --pk
    userID int not null, --fk
    forumID int not null,   --fk
);
create table Email (
    emailID int not null auto_increment,
    userID int not null, --pk
    inboxID int not null,
);
create table Inbox (
    inboxID int not null auto_increment, --pk
);
--Inbox
create table emailMessage ();
--sentMessage
create table sentMessage ();
--pendingMessage
create table pendingMessage (); --maybe
--User
create table User (
    userID int not null auto_increment,
    name varchar(255), 
    email  varchar(255),
    password varchar(40),
    
    phone varchar(255),
    city varchar(255),
    postalState varchar(255),
    postalCode int,
    
    -- Photo userPhoto
    
    -- CreditCard creditCardNumber
    primary key(userID)
);
alter table user
    add foreign key(userPhotoID) references Photo(photoID);
--Photo
create table Photo (
    photoID int not null auto_increment,
    photoName varchar(255),
    photoPath varchar(255),
);

create table Store (
    storeID int not null auto_increment,
);
create table Buyer (
    userID int not null auto_increment,
);
create table Seller (
    userID int not null auto_increment,
);
create table purchasableItem (
    itemID int not null auto_increment,
);
create table Groups (
    groupID int not null auto_increment,
);
create table GroupMembers (
    groupMembersID int not null auto_increment,
);
create table Events (
    eventID int not null auto_increment,
);
create table Profile (
    profileID int not null auto_increment,
    userID int not null,
    
);
create table Projects (
    projectID int not null auto_increment,
    
)
create table projectHistory ();
create table Chest(stash); ();
create table texture ();
create table pattern ();
create table tools ();
create table userNamedItem ();
