import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import {FormsModule} from '@angular/forms';

import { AppComponent } from './app.component';
import {AppRoutingModule} from './app-routing.module';
import { MpskRegComponent } from './mpsk-reg/mpsk-reg.component';
import {MpskRegService} from './mpsk-reg/mpsk-reg.service';
import { HttpClientModule } from '@angular/common/http';

@NgModule({
   declarations: [
      AppComponent,
      MpskRegComponent
   ],
   imports: [
      BrowserModule,
      AppRoutingModule,
      FormsModule,
      HttpClientModule
   ],
   providers: [
      MpskRegService
   ],
   bootstrap: [
      AppComponent
   ]
})
export class AppModule { }
