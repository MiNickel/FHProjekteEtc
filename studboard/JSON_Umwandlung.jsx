class JSONUmwandler{
    NewsToJSON(News){
       var jsonStr = JSON.stringify(News);
       return jsonStr;
    }
    
    ProjektToJSON(Projekt){
       var jsonStr = JSON.stringify({Projekt});
       return jsonStr;
    }
    
    AufgabeToJSON(Aufgabe){
       var jsonStr = JSON.stringify({Aufgabe});
       return jsonStr;
    }
    
    ArtikelToJSON(Artikel) {
        var jsonStr = JSON.stringify(Artikel);
        return jsonStr;
    }
    
    JsonToObject(jsonStr){
      var jsonObj = JSON.parse(jsonStr);
      if (jsonObj.Kategorie){
        var Obj = Object.assign(new News, jsonObj);
      } else if (jsonObj.Professor) {
       	var Obj = Object.assign(new Projekt, jsonObj); 
      } else {
       	var Obj = Object.assign(new Aufgabe, jsonObj); 
      }
      return Obj;
    }
    
}

/*
JsonParser = new JSONUmwandler();
var json =JsonParser.NewsToJSON(artikel3);
console.log(json);
var Obj = JsonParser.JsonToObject(json);
console.log(Obj.Kategorie);
console.log(Obj.Professor);
console.log(Obj.Fach); */