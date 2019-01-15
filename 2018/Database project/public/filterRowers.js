function filterRowersByTeam() {
    var teams_id = document.getElementById('team_filter').value
    //construct the URL and redirect to it
    window.location = '/rowers/filter/' + parseInt(teams_id)
}