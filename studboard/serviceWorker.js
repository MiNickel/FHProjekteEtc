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
	navigator.serviceWorker.register('/serviceWorker.js').then(function(registration) {
    // Registration was successful
    console.log('ServiceWorker registration successful with scope: ', registration.scope);
}).catch(function(err) {
    // registration failed :(
    	console.log('ServiceWorker registration failed: ', err);
    });
}


//Called on install stage
this.addEventListener('install', function(event) {
    //Sicherstellen, das zuerst alle Dateien im Cache laden
    event.waitUntil(
            caches.open('v1').then(function(cache) {
                return cache.addAll([
                   'studboard',
                   'studboard/Startseite.html',
                   'studboard/News.html',
                   'studboard/Projekte.html',
                   'studboard/Aufgaben.html',
                   'studboard/NeuenArtikelAnlegen.html',
                   'studboard/style.css',
                   'studboard/GeoLocation.jsx',
                   'studboard/test.jsx',
                   'studboard/JSON_Umwandlung.jsx',
                   'studboard/Uebersetzung.jsx',
                   'studboard/WebStorage.jsx',
                   'studboard/serviceWorker.js'
                ]);
            })
    );
            
});

// Wird aufgerufen wenn Dateien angefragt werden
this.addEventListener('fetch', function(evt) {
   console.log("Hole " + evt.request.url);
   
   evt.respondWith(
           //Responde with erwartet eine asynchrone Funktion
           caches.match(evt.request).then(      //res ist Ergebnis von caches.match
                   function(res) {
                       console.log("Resource >" + res.url + "< aus dem cache geholt");
                       return res;
                   }).catch(function(err) {
                       console.log("Resource >" + evt.request.url + "< nicht im Chache gefunden");
                       //return fetch(evt.request);
                   })
    );
});
