/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { MpskRegComponent } from './mpsk-reg.component';

describe('MpskRegComponent', () => {
  let component: MpskRegComponent;
  let fixture: ComponentFixture<MpskRegComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ MpskRegComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(MpskRegComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
