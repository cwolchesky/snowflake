process.env.NODE_ENV = "test";

const chai = require('chai');
const chaiHttp = require('chai-http');
let server = require('../app');
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
