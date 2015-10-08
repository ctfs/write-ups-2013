<html>
<body>
<p>Welcome to Loading Bay Control System.</p>
<p>Please input username to retrieve key.</p>
<form action="index.php" method="post">
Username: <input type="text" name="user" default="admin"><br>
<input type="submit" value="Submit"><br>

<?php
if (isset($_POST["user"]))
{
  if (FALSE === strpos(strtolower($_POST["user"]), "admin"))
  {

    $c = mysqli_connect("localhost", "ppp", "ppphatesmysql", "problem") or die('Could not connect to db. Contact competition organizer');
    $query = "SELECT username,hash FROM pwtable WHERE username='" . $_POST["user"] . "'";
    $result = mysqli_query($c, $query);
    if ($result && mysqli_num_rows($result) != 0) {
        while($row = mysqli_fetch_assoc($result)) {
    		echo("<p>Username: " . $row['username']);
    		echo(" Hash: " . $row['hash'] . "</p>");
	}
    }
    mysqli_close($c);
  }
  else
  {
    echo("<p><b>I'm not allowed to tell you the admin password.</b></p>");
  }
}

?>

</body>
</html>


