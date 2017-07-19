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
const config = require('./config.json');

if(process.env.NODE_ENV == "debug") {
    const util = require('util');
}

const app = express();

const commands = {
    "power": 0b0000,
    "coolMode": 0b0001,
    "energySaverMode": 0b0010,
    "fanOnlyMode": 0b0011,
    "sleepButton":0b0100,
    "autoFanMode": 0b0101,
    "timerButton": 0b0110,
    "fanDown": 0b0111,
    "fanUp": 0b1000,
    "tempDown": 0b1001,
    "tempUp": 0b1010
}


function sendToDevice(msg) {
    const iotClient = IotClient.fromConnectionString(config.iotConnString);

    iotClient.open(function(err) {
        if (err) {
            console.error("Could not connect to Azure: " + err.message);
        } else {
            console.log("Client connected to Azure");
            const message = new IotMessage(msg);
            console.log("Sending message: " + message.getData());
            iotClient.send(config.iotDeviceID, message, printResultFor('send'));
        }
    });
}

function printResultFor(op, result) {
    return function printResult(err, res) {
        if (err) {
            console.log(op + " encountered an error: " + err.toString());
        } else {
            console.log(op + " result: " + res.constructor.name);
            console.debug(util.inspect(res, false, null));
        }
    };
}


app.get('/', function(req, res, next) {
    res.send("Listening...");
});

app.get('/power', function(req, res, next){
    sendToDevice(commands.power);
    res.status(200).send();
});





app.listen(8080);
console.log("Listening on port 8080...");

module.exports.server = app;
module.exports.sendToDevice = sendToDevice;
module.exports.printResultFor = printResultFor;
module.exports.commands = commands;
