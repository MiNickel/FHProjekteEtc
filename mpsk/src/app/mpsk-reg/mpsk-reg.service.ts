import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { RequestBodyName, RequestBodyEmail } from '../app.model';

@Injectable({
  providedIn: 'root'
})
export class MpskRegService {

  private url = 'http://api.node.internal.airfy.io:8531/mpsk/self_service';

  constructor(private http: HttpClient) { }

  // tslint:disable-next-line: typedef
  postRequest(requestBody: RequestBodyEmail) {
    return this.http.post(this.url,
      requestBody,
      {
        observe: 'response'
      });
  }

  // tslint:disable-next-line: typedef
  getDisplayName(requestBodyName: RequestBodyName) {
    return this.http.post(this.url + '/get_display_name',
    requestBodyName);
  }
}
