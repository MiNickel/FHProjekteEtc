if (typeof(Storage) !== "undefined"){
    let visits = localStorage.getItem("visits");
    if (visits) {
        visitsNo = parseInt(visits);
        visitsNo++;
        localStorage.setItem("visits", visitsNo);
        
        if(visitsNo>5){
            localStorage.removeItem("visits");
        }
    } else {
        localStorage.setItem("visits", 1);
    }
    console.log("This is your " + localStorage.getItem("visits") + " visits");
    
} else {
    console.log("Sorry");
}