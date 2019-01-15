var express = require('express');
//mysql info in dbcon.js
var mysql = require('./dbcon.js');
var bodyParser = require('body-parser')

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 49911);

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));
//linking the other javascript page
app.use(express.static('public'));
//home
app.get('/', function(req, res, next)
{
	var context = {};
	mysql.pool.query('SELECT * FROM workouts', function(err, rows, fields)
	{
		if(err)
		{
        		next(err);
        		return;
    		}
//making an array
	var list = [];
 	for(var row in rows)
	{
        	var items = {'name': rows[row].name, 
                	    	'reps': rows[row].reps, 
                   		 'weight': rows[row].weight, 
                    		'date':rows[row].date, 
                   		 'id':rows[row].id};
        	if(rows[row].lbs)
		{
            		items.lbs = "LBS";
        	}
        	else
		{
            		items.lbs = "KG";
        	}
        	list.push(items);
    	}
	context.results = list;
    	res.render('home', context);
    })
});
//Taken from the submit page.
app.get('/reset-table',function(req,res,next)
{
    	var context = {};
    	mysql.pool.query("DROP TABLE IF EXISTS workouts", function(err)
	{
        	var createString = "CREATE TABLE workouts("+
        	"id INT PRIMARY KEY AUTO_INCREMENT,"+
        	"name VARCHAR(255) NOT NULL,"+
        	"reps INT,"+
        	"weight INT,"+
        	"date DATE,"+
        	"lbs BOOLEAN)";
        	mysql.pool.query(createString, function(err)
		{
            		res.render('home',context);
        	})
    	});
});
app.get('/insert',function(req,res,next)
{
  	var context = {};
	mysql.pool.query("INSERT INTO `workouts` (`name`, `reps`, `weight`, `date`, `lbs`) VALUES (?, ?, ?, ?, ?)", 
    	[req.query.exercise, 
    	req.query.reps, 
    	req.query.weight, 
    	req.query.date,
//measurment is there for lbs or kg 
    	req.query.lbsOrKg], 
    	function(err, result)
	{
        	if(err)
		{
          		next(err);
          		return;
        	}	 
		context.inserted = result.insertId;
        	res.send(JSON.stringify(context));
  	});
});
app.get('/delete', function(req, res, next) 
{
    	var context = {};
 	mysql.pool.query("DELETE FROM `workouts` WHERE id = ?", 
        [req.query.id], 
        function(err, result) 
	{
        	if(err)
		{
                	next(err);
                	return;
            	}
    	});
});
app.get('/update',function(req, res, next)
{
    	var context = {};
	mysql.pool.query('SELECT * FROM `workouts` WHERE id=?',
        [req.query.id], 
        function(err, rows, fields)
	{
        	if(err)
		{
                	next(err);
                	return;
            	}
            	var list = [];
		for(var row in rows)
		{
                	var items = {'name': rows[row].name, 
                            	'reps': rows[row].reps, 
                            	'weight': rows[row].weight, 
                            	'date':rows[row].date, 
                            	'lbs':rows[row].lbs,
                            	'id':rows[row].id};

                	list.push(items);
            	}
 		context.results = list[0];
       	 	res.render('update', context);
    	});
});
app.get('/updateBack', function(req, res, next)
{
    	var context = {};
	mysql.pool.query("SELECT * FROM `workouts` WHERE id=?", 
        [req.query.id], 
        function(err, result)
	{
            	if(err)
		{
                next(err);
                return;
            	}	
            	if(result.length == 1)
		{
 			var curVals = result[0];
 			if(req.query.lbsOrKg === "on")
			{		//lbs or kg
                    		req.query.lbsOrKg = "1";
                	}
               		else
			{
                    		req.query.lbsOrKg = "0";
                	}
		mysql.pool.query('UPDATE `workouts` SET name=?, reps=?, weight=?, date=?, lbs=? WHERE id=?', 
                [req.query.exercise || curVals.name, 
                req.query.reps || curVals.reps, 
                req.query.weight || curVals.weight, 
                req.query.date || curVals.date, 
                req.query.lbsOrKg, 
                req.query.id],
                function(err, result)
		{
                    	if(err)
			{
                        	next(err);
                        	return;
                    	}
   			mysql.pool.query('SELECT * FROM `workouts`', 
			function(err, rows, fields)
			{
                        	if(err)
				{
                            		next(err);
                            		return;
                        	}
                        	var list = [];
                        	for(var row in rows)
				{
                            		var items = {'name': rows[row].name, 
                            			'reps': rows[row].reps,
                            			'weight': rows[row].weight, 
                            			'date':rows[row].date, 
                            			'id':rows[row].id};

                            		if(rows[row].lbs)
					{
                                		items.lbs = "LBS";
                            		}
                            		else
					{
                                		items.lbs = "KG";
                            		}
                            		list.push(items);
                        	}
                        	context.results = list;
                        	res.render('home', context);
                    	});
                });
	}
    });
});
//standard 404 and 500
app.use(function(req,res)
{
	res.status(404);
    	res.render('404');
});

app.use(function(err, req, res, next)
{
    	console.error(err.stack);
    	res.type('plain/text');
    	res.status(500);
    	res.render('500');
});

app.listen(app.get('port'), function()
{
    console.log('Express started on flip2.engr.oregonstate.edu:' + app.get('port') + '; press Ctrl-C to terminate.');
});
