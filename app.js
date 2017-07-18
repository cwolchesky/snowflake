/*
* snowflake - An IoT controller for an AC using an Arduino-based device
* Copyright (C) 2017 Chris Wolchesky
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Setting up our required components.  Using constants as the variables
// themselves will be immutable but their properties will still be mutable
const IotClient = require('azure-iothub').Client;
const IotMessage = require('azure-iot-common').Message;
const express = require('express');

const app = express();


app.get('/', function(req, res, next) {
    res.send("Listening...");
});




app.listen(8080);
console.log("Listening on port 8080...");

module.exports = app;
