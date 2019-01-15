function updateAttendingRaceRower(id){
    $.ajax({
        url: '/attendingRaceRowers/' + id,
        type: 'PUT',
        data: $('#update-arr').serialize(),
        success: function(result){
            window.location.replace("/attendingRaceRowers");
        }
    })
};