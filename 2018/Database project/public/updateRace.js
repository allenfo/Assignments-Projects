function updateRace(id){
    $.ajax({
        url: '/races/' + id,
        type: 'PUT',
        data: $('#update-races').serialize(),
        success: function(result){
            window.location.replace("/races");
        }
    })
};