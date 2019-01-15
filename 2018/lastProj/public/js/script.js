document.getElementById('submitItem').addEventListener('click',function(event)
{
	var addExercise = document.getElementById("exerciseForm");
	var req = new XMLHttpRequest();
	var parameters = "exercise="+addExercise.elements.exercise.value+
			"&reps="+addExercise.elements.reps.value+
			"&weight="+addExercise.elements.weight.value+
			"&date="+addExercise.elements.date.value;
	if(addExercise.elements.lbsOrKg.checked)
	{
		parameters+="&lbsOrKg=1";
	}
	else
	{
		parameters+="&lbsOrKg=0";
	}
	req.open("GET", "/insert?"+parameters, true);
	req.setRequestHeader('Content-Type','application/x-www-form-urlencoded');
	req.addEventListener('load', function()
	{
		if(req.status >= 200 && req.status < 400)
		{
			var response = JSON.parse(req.responseText);
			var id = response.inserted;
			var table = document.getElementById("workoutTable");
			var row = table.insertRow(-1);
			var exerciseCell = document.createElement('td');
			exerciseCell.textContent = addExercise.elements.exercise.value;
			row.appendChild(exerciseCell);
			var repCell = document.createElement('td');
			repCell.textContent = addExercise.elements.reps.value;
			row.appendChild(repCell);
			var weightCell = document.createElement('td');
			weightCell.textContent = addExercise.elements.weight.value;
			row.appendChild(weightCell);
			var lbsOrKgCell = document.createElement('td');
			if(addExercise.elements.lbsOrKg.checked)
			{
				lbsOrKgCell.textContent = "LBS"
			}
			else
			{
				lbsOrKgCell.textContent = "KG"
			}
			row.appendChild(lbsOrKgCell);
			var dateCell = document.createElement('td');
			dateCell.textContent = addExercise.elements.date.value;
			row.appendChild(dateCell);
			var updateCell = document.createElement('td');
			var updateLink = document.createElement('a');
			updateLink.setAttribute('href','/update?id='+id);
			var updateButton = document.createElement('input');
			updateButton.setAttribute('type','button');
			updateButton.setAttribute('value','Update');
			updateLink.appendChild(updateButton);
			updateCell.appendChild(updateLink);
			row.appendChild(updateCell);
			var deleteCell = document.createElement('td');
			var deleteButton = document.createElement('input');
			deleteButton.setAttribute('type','button');
			deleteButton.setAttribute('name','delete');
			deleteButton.setAttribute('value','Delete');
			deleteButton.setAttribute('onClick', 'deleteRow("workoutTable",'+id+')');
			var deleteHidden = document.createElement('input');
			deleteHidden.setAttribute('type','hidden');
			deleteHidden.setAttribute('id', 'delete'+id);
			deleteCell.appendChild(deleteButton);
			deleteCell.appendChild(deleteHidden);
			row.appendChild(deleteCell);
		}
		else 
		{
	    		console.log('there was an error');
		}
	});
	
	req.send("/insert?"+parameters);
	event.preventDefault();
});

function deleteRow(workoutTable, id)
{
	var table = document.getElementById(workoutTable);
	var rowCount = table.rows.length;
	var deleteString = "delete"+id;
	for(var i = 1; i < rowCount; i++)
	{
		var row = table.rows[i];
		var dataCells = row.getElementsByTagName("td");
		var deleteCell = dataCells[dataCells.length -1];
		if(deleteCell.children[1].id === deleteString)
		{
			table.deleteRow(i);
		}
	}
	var req = new XMLHttpRequest();
	req.open("GET","/delete?id="+id, true);
	req.addEventListener("load",function()
	{
		if(req.status >= 200 && req.status < 400)
		{
	    	console.log('delete request sent');
		}
		else 
		{
		    console.log('there was an error');
		}
	});
	req.send("/delete?id="+id );
}
