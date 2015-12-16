var fs = require("fs");
var crypto = require('crypto');
var words = (fs.readFileSync("cracklib-small.txt") + "").split("\n");
for (i in words) {
		var word = words[i];
		var md5sum = crypto.createHash("md5").update(word + "5948").digest("hex");
		if (md5sum === "02ed2bf40532f187ec9334ef37f75591") {
			console.log(word);
		}
	}