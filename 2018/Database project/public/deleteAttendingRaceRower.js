function deleteAttendingRaceRower(id)
{
	$.ajax({
		url: './attendingRaceRowers/' +id,
		type: 'DELETE',
		success: function(result){
			window.location.reload(true);
		}
	})
};
