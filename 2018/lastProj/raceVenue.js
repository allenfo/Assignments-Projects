module.exports = function(){
    var express = require('express');
    var router = express.Router();


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

    function getOneRaceVenue(res, mysql, context, id, complete){
        var sql = "SELECT race_venue_id as id, location, water_type, current_speed_fps, length_of_course_meters FROM `table_race_venue` WHERE race_venue_id= ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.raceVenue = results[0];
            complete();
        });
    }

    /*Display all people. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deleteRaceVenue.js"];
        var mysql = req.app.get('mysql');
        getRaceVenues(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 1){
                res.render('raceVenue', context);
            }

        }
    });

     /*Display one person for the specific purpose of updating people*/

    router.get('/:id', function(req, res){
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateRaceVenue.js"];
        var mysql = req.app.get('mysql');
        getOneRaceVenue(res, mysql, context, req.params.id, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 1){
                res.render('update_raceVenue', context);
            }

        }
    });

   /* Adds a person, redirects to the people page after adding*/ 

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO `table_race_venue`(`location`, `water_type`, `current_speed_fps`, `length_of_course_meters`) VALUES (?,?,?,?)";
        var inserts = [req.body.location, req.body.water_type, req.body.current_speed_fps, req.body.length_of_course_meters];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/raceVenue');
            }
        });
    });

     /*The URI that update data is sent to in order to update a person*/ 

    router.put('/:id', function(req, res){
	console.log(req.body)
	console.log(req.params.id)
        var mysql = req.app.get('mysql');
        var sql = "UPDATE `table_race_venue` SET location=?, water_type=?, current_speed_fps=?, length_of_course_meters=? WHERE race_venue_id=?";
        var inserts = [req.body.location, req.body.water_type, req.body.current_speed_fps, req.body.length_of_course_meters, req.params.id];
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
        var sql = "DELETE FROM `table_race_venue` WHERE race_venue_id = ?";
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
