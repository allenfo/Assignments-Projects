function deleteAttendingRaceTeam(id)
{
	$.ajax({
		url: './attendingRaceTeams/' +id,
		type: 'DELETE',
		success: function(result){
			window.location.reload(true);
		}
	})
};
