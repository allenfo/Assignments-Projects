module.exports = function(){
    var express = require('express');
    var router = express.Router();


    function getAttendingRaceTeams(res, mysql, context, complete){
        mysql.pool.query("SELECT tart_id as id, race_name,team_name FROM `table_attending_raceTeams` INNER JOIN `table_races` ON race_number=race_id INNER JOIN table_teams ON team_number=team_id", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.attendingRaceTeams = results;
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
 function getTeams(res, mysql, context, complete){
        mysql.pool.query("SELECT team_id as id, team_name, rowers, boats, coaches, location, focus FROM `table_teams`", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.team = results;
            complete();
        });
    }

    function getASingleAttendingRaceTeams(res, mysql, context, id, complete){
        var sql = "SELECT tart_id as id, race_name FROM `table_attending_raceTeams` INNER JOIN `table_races` ON race_number=race_id INNER JOIN table_teams ON team_number=team_id WHERE tart_id= ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.attendingRaceTeams = results[0];
            complete();
        });
    }

    /*Display all people. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deleteAttendingRaceTeam.js"];
        var mysql = req.app.get('mysql');
        getAttendingRaceTeams(res, mysql, context, complete);
	getRaces(res, mysql, context, complete);
	getTeams(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 3){
                res.render('attendingRaceTeams', context);
            }

        }
    });

     /*Display one person for the specific purpose of updating people*/

    router.get('/:id', function(req, res){
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateAttendingRaceTeam.js"];
        var mysql = req.app.get('mysql');
        getASingleAttendingRaceTeams(res, mysql, context, req.params.id, complete);
	getRaces(res, mysql, context, complete);
	getTeams(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 3){
                res.render('update_attendingRaceTeams', context);
            }

        }
    });

    /*Adds a person, redirects to the people page after adding*/

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO `table_attending_raceTeams`(`race_number`, `team_number`) VALUES (?,?)";
        var inserts = [req.body.race_number, req.body.team_number];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/attendingRaceTeams');
            }
        });
    });

     /*The URI that update data is sent to in order to update a person*/ 

    router.put('/:id', function(req, res){
	console.log(req.body)
	console.log(req.params.id)
        var mysql = req.app.get('mysql');
        var sql = "UPDATE table_attending_raceTeams SET race_number=? WHERE tart_id=?";
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
        var sql = "DELETE FROM `table_attending_raceTeams` WHERE tart_id = ?";
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
