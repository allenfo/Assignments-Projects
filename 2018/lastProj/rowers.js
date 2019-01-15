module.exports = function(){
    var express = require('express');
    var router = express.Router();


    function getRowers(res, mysql, context, complete){
        mysql.pool.query("SELECT rower_id as id, fname, lname, age, height_inches, erg_score_watts, IFNULL(team_name,'No Team') AS team_name FROM `table_rowers` LEFT JOIN `table_teams` ON team=team_id", function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.rowers = results;
            complete();
        });
    }
function getRowersByTeam(req, res, mysql, context, complete){
        var query="SELECT rower_id as id, fname, lname, age, height_inches, erg_score_watts, IFNULL(team_name,'No Team') AS team_name FROM `table_rowers` LEFT JOIN `table_teams` ON team=team_id WHERE team=?";
 	console.log(req.params);
	var inserts= [req.params.team];
	mysql.pool.query(query,inserts,function(error, results, fields){
            if(error){
                res.write(JSON.stringify(error));
                res.end();
            }
            context.rowers = results;
            complete();
        });
    }

/*Added to get the list of teams for the form*/
function getTeams(res, mysql, context, complete){
        mysql.pool.query("SELECT team_id as id, team_name, rowers, boats, coaches, location, focus FROM `table_teams`", function(error, results, fields){
            if(error){
               // res.write(JSON.stringify(error));
               // res.end();
               console.log(error);
            }
            context.teams = results;
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

    /*Display all people. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res)
	{
       	 	var  callbackCount = 0;
        	var context = {};
        	context.jsscripts = ["deleteRower.js","filterRowers.js"];
        	var mysql = req.app.get('mysql');
		getRowers(res, mysql, context, complete);
		getTeams(res, mysql, context, complete);
		function complete(){
            	callbackCount++;
            	if(callbackCount >= 2)
		{
               	 	res.render('rowers', context);
           	}
        
	}
	
    });

router.get('/filter/:team', function(req, res){
	var callbackCount = 0;
        var context = {};
        context.jsscripts = ["deleteRower.js","filterRowers.js"];
        var mysql = req.app.get('mysql');
        getRowersByTeam(req, res, mysql, context, complete);
        getTeams(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 2){
                res.render('rowers', context);
            }

        }
    });     /*Display one person for the specific purpose of updating people*/

    router.get('/:id', function(req, res){
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["updateRower.js"];
        var mysql = req.app.get('mysql');
        getARower(res, mysql, context, req.params.id, complete);
        getTeams(res, mysql, context, complete);
        function complete(){
            callbackCount++;
            if(callbackCount >= 2){
                res.render('update_rower', context);
            }

        }
    });

    /*Adds a person, redirects to the people page after adding*/ 

    router.post('/', function(req, res){
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO `table_rowers`(fname, lname, age, height_inches, erg_score_watts, team) VALUES (?,?,?,?,?,?)";
        var inserts = [req.body.fname, req.body.lname, req.body.age, req.body.height_inches, req.body.erg_score_watts, req.body.team];
        sql = mysql.pool.query(sql,inserts,function(error, results, fields){
            if(error){
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            }else{
                res.redirect('/rowers');
            }
        });
    });

     /*The URI that update data is sent to in order to update a person*/ 

    router.put('/:id', function(req, res){
	console.log(req.body)
	console.log(req.params.id)
        var mysql = req.app.get('mysql');
        var sql = "UPDATE `table_rowers` SET fname=?, lname=?, age=?, height_inches=?, erg_score_watts=?, team=? WHERE rower_id=?";
        var inserts = [req.body.fname, req.body.lname, req.body.age, req.body.height_inches, req.body.erg_score_watts, req.body.team, req.params.id];
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
        var sql = "DELETE FROM `table_rowers` WHERE rower_id = ?";
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
