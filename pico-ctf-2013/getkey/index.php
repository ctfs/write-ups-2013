<!doctype html>
<html lang="en">
	<head>
		<style type="text/css">
			body {
				padding-top: 40px;
				text-align: center;
			}

			input {
				border-style: solid;
				border-color: black;
				padding: 5px;
			}
		</style>
	</head>
	<body>
		<?php
			$key = '9fa449c061d64f58de600dfacaa6bd5d';
			if (!(array_key_exists('admin', $_GET) && array_key_exists('competition', $_GET))) {
				echo('');
			} else if (($_GET['admin'] === 'true') && 
			  (($_GET['competition'] === 'picoctf' || 
			  $_GET['competition'] === 'toasterwars'))) {
			  	echo("<p>FLAG: $key</p>");
			} else {
				echo("Either you aren't admin or wrong competition");
			}
		?>
		<form action="?admin=false&competition=ccdc" method="GET">
			<input type="hidden" name="admin" value="false" /> 
			<input type="hidden" name="competition" value="ccdc" /> 
			<p><input type="submit" value="Get Key"></p>
		</form>
	</body>
</html>
