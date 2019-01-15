function updateRaceVenue(id){
    $.ajax({
        url: '/raceVenue/' + id,
        type: 'PUT',
        data: $('#update-raceVenue').serialize(),
        success: function(result){
            window.location.replace("/raceVenue");
        }
    })
};