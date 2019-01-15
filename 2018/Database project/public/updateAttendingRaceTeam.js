function updateAttendingRaceTeam(id){
    $.ajax({
        url: '/attendingRaceTeams/' + id,
        type: 'PUT',
        data: $('#update-art').serialize(),
        success: function(result){
            window.location.replace("/attendingRaceTeams");
        }
    })
};