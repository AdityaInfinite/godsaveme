const { request, response } = require('express');
const express = require('express');
'use strict';
const fs = require('fs');

const app = express();
const port = process.env.PORT || 3000;
app.listen(port, () => console.log(`listening at ${port}`));
app.use(express.static('public/'));
app.use(express.json());
app.post('/postpath', (request, response, next) => {
	console.log(request.body.val);
	var fileName = request.body.val
	response.sendFile(fileName,function (err) {
		if (err) {
			next(err)
		} else {
			console.log('Sent:', fileName)
		}
	})
})
