module.exports = function(){
    var express = require('express');
    var router = express.Router();


    function getTeams(res, mysql, context, complete){
        mysql.pool.query("SELECT team_id as id, team_name, rowers, boats, coaches, location, focus FROM `table_teams`", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.teams = results;
            complete();
        });
    }

    function getOneTeam(res, mysql, context, id, complete){
        var sql = "SELECT team_id as id,team_name, rowers, boats, coaches, location, focus FROM `table_teams` WHERE team_id= ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.teams = results[0];
            complete();
        });
    }

    /*Display all people. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res){
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deleteTeam.js"];
        var mysql = req.app.get('mysql');
        getTeams(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 1){
                res.render('teams', context);
            }

        }
    });

    /* Display one person for the specific purpose of updating people*/

    router.get('/:id', function(req, res){
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateTeam.js"];
        var mysql = req.app.get('mysql');
        getOneTeam(res, mysql, context, req.params.id, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 1){
                res.render('update_teams', context);
            }

        }
    });

    /*Adds a person, redirects to the people page after adding */

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO `table_teams`(team_name, rowers, coaches, boats, location, focus) VALUES(? ,? ,?,?,?, ?)";
        var inserts = [req.body.team_name, req.body.rowers, req.body.coaches, req.body.boats, req.body.location, req.body.focus];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/teams');
            }
        });
    });

    /* The URI that update data is sent to in order to update a person*/ 

    router.put('/:id', function(req, res){
	console.log(req.body)
	console.log(req.params.id)
        var mysql = req.app.get('mysql');
        var sql = "UPDATE `table_teams` SET team_name=?, rowers=?, boats=?, coaches=?, location=?, focus=? WHERE team_id =?";
 	var inserts = [req.body.team_name, req.body.rowers, req.body.coaches, req.body.boats, req.body.location, req.body.focus, req.params.id];        
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
        var sql = "DELETE FROM `table_teams` WHERE team_id = ?";
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
