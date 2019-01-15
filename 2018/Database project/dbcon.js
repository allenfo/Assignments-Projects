var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs361_allenfo',
  password        : '1124',
  database        : 'cs361_allenfo'
});

module.exports.pool = pool;
