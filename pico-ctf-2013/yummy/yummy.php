<html>
<head>
<title>SpacePort Authentication Server</title>
</head>

<div style="position: relative; width: 728px; margin: auto;">
<h1>Docking Bay Ship Status</h1>

<?php
if ($_COOKIE["authorization"] === "administrator") {
  echo <<<END
<h2>Login Success. </h2>
<br/>
<hr>
<br/>
<table border="1">
<tr>
<th>Docking Bay</th>
<th>Ship Designation</th>
<th>Status</th>
</tr>
<tr>
<td>DX9-2</td>
<td>Proud Planetary Prowler</td>
<td>Under Repair</td>
</tr>
<tr>
<td>DX5-2</td>
<td>Century Eagle</td>
<td>Fuelling</td>
</tr>
<tr>
<td>DX6-7</td>
<td>USS Franchise</td>
<td>Awaiting Launch</td>
</tr>
<tr>
<td>DX7-1</td>
<td>HMS Beagle</td>
<td>Under Repair</td>
</tr>
<tr>
<td>DX7-2</td>
<td>Pwnie Express</td>
<td>Awaiting Launch</td>
</tr>
<tr>
<td>DX9-5</td>
<td>Happy Fun Time Awesome Best Ship</td>
<td>Awaiting Launch</td>
</tr>
<tr>
<td>DX2-2</td>
<td>Roflcopter</td>
<td>Under Repair</td>
</tr>
<tr>
<td>DX4-5</td>
<td>YHXS-2 Ghost</td>
<td>Under Repair</td>
</tr>
<tr>
<td>DX4-9</td>
<td>Theseus</td>
<td>Awaiting Launch</td>
</tr>
<tr>
<td>DX8-2</td>
<td>Drone DK97</td>
<td>Fuelling</td>
</tr>
</table> 
END;
}
else {
echo <<<END
<h2>Login Failure</h2>
<hr>
<p style="color:red">You are not authorized to view this page.</p>
END;
echo "<!-- DEBUG: Expected Cookie: \"authorization=administrator\"
received Cookie: \"".$_SERVER['HTTP_COOKIE']."\" -->";
}
?>

</div>

</html>
