
if (navigator.geolocation){
    navigator.geolocation.watchPosition(positionReciveHandler, errorHandler);
} else {
    console.log("Geolocation not supoorted");
}

function positionReciveHandler(position) {
    console.log("Ihre Positionsinformationen:");
    for(let i in position.coords){
        console.log(i + " = " + position.coords[i]);
    }
}

function errorHandler(error) {
    console.log("Keine geolocation Daten vorhanden.");
}