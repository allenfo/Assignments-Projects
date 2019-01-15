function updateRower(id){
    $.ajax({
        url: '/rowers/' + id,
        type: 'PUT',
        data: $('#update-rowers').serialize(),
        success: function(result){
            window.location.replace("/rowers");
        }
    })
};