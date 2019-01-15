module.exports = function(){
    var express = require('express');
    var router = express.Router();


    function getAttendingRaceRowers(res, mysql, context, complete){
        mysql.pool.query("SELECT tarr_id as id, race_name,  fname, lname FROM `table_attending_raceRowers` INNER JOIN `table_races` ON race_number=race_id INNER JOIN table_rowers ON rower_number=rower_id", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.attendingRaceRowers = results;
            complete();
        });
    }
function getRaces(res, mysql, context, complete){
        mysql.pool.query("SELECT race_id as id, race_name, date, location, registration_deadline, rules, type FROM `table_races` LEFT JOIN `table_race_venue` ON location_id = race_venue_id", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.race = results;
            complete();
        });
    }

 function getRowers(res, mysql, context, complete){
        mysql.pool.query("SELECT rower_id as id, fname, lname, age, height_inches, erg_score_watts, IFNULL(team_name,'No Team') AS team_name FROM `table_rowers` LEFT JOIN `table_teams` ON team=team_id", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.rower = results;
            complete();
        });
    }
 function getARower(res, mysql, context, id, complete){
       var sql = "SELECT rower_id as id, fname, lname, age, height_inches, erg_score_watts, team_name FROM `table_rowers` LEFT JOIN `table_teams` ON team=team_id WHERE rower_id= ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.rowers = results[0];
            complete();
        });
    }

    function getASingleAttendingRaceRower(res, mysql, context, id, complete){
        var sql = "SELECT tarr_id as id, race_name, fname, lname FROM `table_attending_raceRowers` INNER JOIN `table_races` ON race_number=race_id INNER JOIN table_rowers ON rower_number=rower_id WHERE tarr_id= ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.attendingRaceRower = results[0];
            complete();
        });
    }

    /*Display all people. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deleteAttendingRaceRower.js"];
        var mysql = req.app.get('mysql');
        getAttendingRaceRowers(res, mysql, context, complete);
	getRaces(res, mysql, context, complete);
	getRowers(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 3){
                res.render('attendingRaceRowers', context);
            }

        }
    });

     /*Display one person for the specific purpose of updating people*/

    router.get('/:id', function(req, res){
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateAttendingRaceRower.js"];
        var mysql = req.app.get('mysql');
        getASingleAttendingRaceRower(res, mysql, context, req.params.id, complete);
	getRaces(res, mysql, context, complete);
	getARower(res, mysql, context, req.body.id, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 3){
                res.render('update_attendingRaceRowers', context);
            }

        }
    });

    /*Adds a person, redirects to the people page after adding*/

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO `table_attending_raceRowers`(`race_number`, `rower_number`) VALUES (?,?)";
        var inserts = [req.body.race_number, req.body.rower_number];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/attendingRaceRowers');
            }
        });
    });

     /*The URI that update data is sent to in order to update a person*/ 

    router.put('/:id', function(req, res){
	console.log(req.body)
	console.log(req.params.id)
        var mysql = req.app.get('mysql');
        var sql = "UPDATE table_attending_raceRowers SET race_number=? WHERE tarr_id=?";
        var inserts = [req.body.race_number, req.params.id];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.status(200);
                res.end();
            }
        });
    });

    /*Route to delete a person, simply returns a 202 upon success. Ajax will handle this. */

    router.delete('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM `table_attending_raceRowers` WHERE tarr_id = ?";
        var inserts = [req.params.id];
        sql = mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
            }else{
                res.status(202).end();
            }
        })
    })

    return router;
}();
