/*
if('serviceWorker' in navigator) {
    let serviceworker = navigator.serviceWorker.register('serviceWorker.js');
    let successfullRegisterFunc = function(reg) {
        console.log("Erfolgreich registriert");
    }
    let errorRegisterFunc = function(err) {
        console.log("Fehler beim registrieren: " + err);
    }
    //serviceworker.then(successfullRegisterFunc, errorRegisterFunc);
} else {
    console.log("No ServiceWorker support");
}
*/
if ('serviceWorker' in navigator) {
	navigator.serviceWorker.register('/studboard/serviceworker-worker.js').then(function(registration) {
    // Registration was successful
    console.log('ServiceWorker registration successful with scope: ', registration.scope);
}).catch(function(err) {
    // registration failed :(
    	console.log('ServiceWorker registration failed: ', err);
    });
}


