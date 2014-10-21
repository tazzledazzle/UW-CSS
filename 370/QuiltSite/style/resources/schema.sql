create table Forums (
    forumID int not null, --pk
);
create table ForumPosts (
    forumMemberID int not null, --pk
    forumID int not null, --fk
    userID int, --fk
    
);
create table FourmMembers (
    forumMemberID int not null, --pk
    userID int not null, --fk
    forumID int not null,   --fk
);
create table Email (
    userID int not null, --pk
    inboxID int not null,
);
create table Inbox (
    inboxID int not null, --pk
);
--Inbox
create table emailMessage ();
--sentMessage
create table sentMessage ();
--pendingMessage
create table pendingMessage (); --maybe
--User
create table User (
    userID int not null,
    name varchar(255), 
    email  varchar(255),
    
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
    photoID int not null,
    photoName varchar(255),
    photoPath varchar(255),
);

create table Store (
    storeID int not null,
);
create table Buyer (
    userID int not null,
);
create table Seller (
    userID int not null,
);
create table purchasableItem (
    itemID int not null,
);
create table Groups (
    groupID int not null,
);
create table GroupMembers (
    groupMembersID int not null,
);
create table Events (
    eventID int not null,
);
create table Profile (
    profileID int not null,
);
create table Projects (
    projectID int not null,
    
)
create table projectHistory ();
create table Chest(stash); ();
create table texture ();
create table pattern ();
create table tools ();
create table userNamedItem ();
