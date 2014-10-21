<?php
require_once 'login.php';
     $link =  mysql_connect($db_hostname, $db_username, $db_password)
       or die("<p>Error connecting to database: " .
                mysql_error() . "</p>");
       echo "<p>Connected to MySQL!</p>";
$res = mysql_query("SHOW DATABASES");

while ($row = mysql_fetch_assoc($res)) {
    echo $row['Database'] . "\n";
}




?>
