process.env.NODE_ENV = "test";

const chai = require('chai');
const chaiHttp = require('chai-http');
const IotClient = require('azure-iothub').Client;
const IotMessage = require('azure-iot-common').Message;
const config = require('../config.json');
let server = require('../app').server;
let sendMessage = require('../app').sendMessage;
let printResultFor = require('../app').printResultFor;
const should = require('chai').should();

chai.use(chaiHttp);

describe('GET /', function() {
    it('should retrieve a good status (200)', function(done) {
        chai.request(server)
            .get('/')
            .end(function(err, res) {
                res.should.have.status(200);
                done();
            });
    });
});

describe('Sending Messages/printResultFor', function() {
    it('should send a message');
    it('am not sure how to test the send and receive of data yet');
});
