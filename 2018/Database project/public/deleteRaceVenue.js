function deleteRaceVenue(id)
{
	$.ajax({
		url: './raceVenue/' +id,
		type: 'DELETE',
		success: function(result){
			window.location.reload(true);
		}
	})
};
