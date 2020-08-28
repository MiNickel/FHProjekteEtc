import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { MpskRegComponent } from './mpsk-reg/mpsk-reg.component';
import { AppComponent } from './app.component';

const routes: Routes = [
    { path: ':name/mpsk_self_service/:validator', component: MpskRegComponent },
    { path: '', component: AppComponent }
];

@NgModule({
    imports: [RouterModule.forRoot(routes)],
    exports: [RouterModule]
})
export class AppRoutingModule { }
