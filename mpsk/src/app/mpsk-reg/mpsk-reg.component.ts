import { Component, OnInit } from '@angular/core';
import { MpskRegService } from './mpsk-reg.service';
import { RequestBodyEmail, RequestBodyName } from 'app/app.model';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-mpsk-reg',
  templateUrl: './mpsk-reg.component.html',
  styleUrls: ['./mpsk-reg.component.css']
})
export class MpskRegComponent implements OnInit {

  public title: string;
  public info = 'Bitte geben Sie ihre E-Mail-Adresse ein. Sie erhalten daraufhin Ihr persönliches WLAN-Kennwort.';
  public disabledButton = true;
  public disabledContainer = false;
  public disabledInput = false;
  public email = '';
  public name: string;
  public validator: string;
  public displayName = '';

  constructor(private mpskRegService: MpskRegService, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.name = this.route.snapshot.paramMap.get('name');
    this.validator = this.route.snapshot.paramMap.get('validator');
    const requestBodyName = new RequestBodyName(this.name, this.validator);
    this.mpskRegService.getDisplayName(requestBodyName).subscribe((result: string) => {
      this.displayName = result;
      this.title = 'Registration eines WLAN-Zugangs bei ' +  this.displayName;
    }, e => {
      this.title = 'Registration eines WLAN-Zugangs';
    });
  }

  public checkInput(input: string): void {
    const emailRegEx = /\S+@\S+\.\S+/;

    if (emailRegEx.test(input)) {
      this.disabledButton = false;
    } else {
      this.disabledButton = true;
    }
  }

  public submit(): void {
    const requestBody = new RequestBodyEmail(this.name, this.validator, this.email);

    this.mpskRegService.postRequest(requestBody).subscribe(result => {
      this.title = 'Fertig';
      this.info = 'Sie erhalten eine Email, nachdem eine zuständige Person Ihre Anmeldung freigeschalten hat.';
      this.disabledContainer = true;
    }, e => {
      this.handleError(e);
    });
  }

  public back(): void {
    this.disabledInput = false;
    if (this.displayName === '') {
      this.title = 'Registration eines WLAN-Zugangs';
    } else {
      this.title = 'Registration eines WLAN-Zugangs bei ' + this.displayName;
    }
    this.info = 'Bitte geben Sie ihre E-Mail-Adresse ein. Sie erhalten daraufhin Ihr persönliches WLAN-Kennwort.';
    this.email = '';
  }

  private handleError(e: any): void {
    this.title = 'Fehler';
    this.disabledInput = true;
    if (e.status === 400) {
      this.info = 'Korrigieren Sie das Format Ihrer Email-Adresse.';
    } else {
      this.info = 'Ihre Eingabe konnte vom System nicht verarbeitet werden.';
    }
  }

}
