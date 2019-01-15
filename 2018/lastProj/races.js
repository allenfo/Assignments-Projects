module.exports = function(){
    var express = require('express');
    var router = express.Router();


    function getRaces(res, mysql, context, complete){
        mysql.pool.query("SELECT race_id as id, race_name, date, location, registration_deadline, rules, type FROM `table_races` LEFT JOIN `table_race_venue` ON location_id = race_venue_id", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.races = results;
            complete();
        });
    }
 function getRaceVenues(res, mysql, context, complete){
        mysql.pool.query("SELECT race_venue_id as id, location, water_type, current_speed_fps, length_of_course_meters FROM `table_race_venue`", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.raceVenue= results;
            complete();
        });
    }

    function getARace(res, mysql, context, id, complete){
        var sql = "SELECT race_id as id, race_name, date, location_id, registration_deadline, rules, type FROM `table_races` WHERE race_id= ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.races = results[0];
            complete();
        });
    }

    /*Display all people. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deleteRace.js"];
        var mysql = req.app.get('mysql');
        getRaces(res, mysql, context, complete);
	getRaceVenues(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 2){
                res.render('races', context);
            }

        }
    });

     /*Display one person for the specific purpose of updating people*/

    router.get('/:id', function(req, res){
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateRace.js"];
        var mysql = req.app.get('mysql');
        getARace(res, mysql, context, req.params.id, complete);
       getRaceVenues(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 2){
                res.render('update_race', context);
            }

        }
    });

    /*Adds a person, redirects to the people page after adding*/ 

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO `table_races`(`race_name`, `date`, `location_id`, `registration_deadline`, `rules`, `type`) VALUES (?,?,?,?,?,?)";
        var inserts = [req.body.race_name, req.body.date, req.body.location_id, req.body.registration_deadline, req.body.rules, req.body.type];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/races');
            }
        });
    });

     /*The URI that update data is sent to in order to update a person*/ 

    router.put('/:id', function(req, res){
	console.log(req.body)
	console.log(req.params.id)
        var mysql = req.app.get('mysql');
        var sql = "UPDATE table_races SET race_name=?, date=?, location_id=?, registration_deadline=?, rules=?, type=? WHERE race_id=?";
        var inserts = [req.body.race_name, req.body.date, req.body.location_id, req.body.registration_deadline, req.body.rules, req.body.type, req.params.id];
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

   /* Route to delete a person, simply returns a 202 upon success. Ajax will handle this. */

    router.delete('/:id', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM `table_races` WHERE race_id = ?";
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
