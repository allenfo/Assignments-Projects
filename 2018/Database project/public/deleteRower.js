function deleteRower(id)
{
	$.ajax({
		url: './rowers/' +id,
		type: 'DELETE',
		success: function(result){
			window.location.reload(true);
		}
	})
};