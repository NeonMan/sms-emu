// Copyright 2015 Juan Luis Álvarez Martínez

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// generated by Fast Light User Interface Designer (fluid) version 1.0303

#include "DialogBreakpoint.h"
#if 1
#endif

void DialogBreakpoints::cb_buttonCreate_i(Fl_Button*, void*) {
  //Parse the address
const unsigned long addr = std::stol(textAddress->value(), 0, 16);

//Is a PC breakpoint?
if(checkPc->value()){
  bp_table[addr] |= Z80_BREAK_PC;
}
//Is IO ?
else if (checkIo->value()){
  //Is IO write?
  if(checkWrite->value())
    bp_table[addr] |= Z80_BREAK_IO_WR;
  //Is IO read?
  if(checkRead->value())
    bp_table[addr] |= Z80_BREAK_IO_RD;
}
//Is Memory bp
else{
  //Is Mem write?
  if(checkWrite->value())
    bp_table[addr] |= Z80_BREAK_WR;
  //Is Mem read?
  if(checkRead->value())
    bp_table[addr] |= Z80_BREAK_RD;
};
}
void DialogBreakpoints::cb_buttonCreate(Fl_Button* o, void* v) {
  ((DialogBreakpoints*)(o->parent()->parent()->user_data()))->cb_buttonCreate_i(o,v);
}

void DialogBreakpoints::cb_buttonRemove_i(Fl_Button*, void*) {
  const unsigned long addr = std::stol(textAddress->value(), 0, 16);
bp_table[addr] = 0;
}
void DialogBreakpoints::cb_buttonRemove(Fl_Button* o, void* v) {
  ((DialogBreakpoints*)(o->parent()->parent()->user_data()))->cb_buttonRemove_i(o,v);
}

void DialogBreakpoints::cb_checkVdpcontrol_i(Fl_Check_Button* o, void*) {
  vdp_control(o->value());
}
void DialogBreakpoints::cb_checkVdpcontrol(Fl_Check_Button* o, void* v) {
  ((DialogBreakpoints*)(o->parent()->parent()->user_data()))->cb_checkVdpcontrol_i(o,v);
}

void DialogBreakpoints::cb_checkVdpread_i(Fl_Check_Button* o, void*) {
  this->vdp_data(o->value(), 1);
}
void DialogBreakpoints::cb_checkVdpread(Fl_Check_Button* o, void* v) {
  ((DialogBreakpoints*)(o->parent()->parent()->user_data()))->cb_checkVdpread_i(o,v);
}

void DialogBreakpoints::cb_checkVdpwrite_i(Fl_Check_Button* o, void*) {
  this->vdp_data(o->value(), 0);
}
void DialogBreakpoints::cb_checkVdpwrite(Fl_Check_Button* o, void* v) {
  ((DialogBreakpoints*)(o->parent()->parent()->user_data()))->cb_checkVdpwrite_i(o,v);
}

void DialogBreakpoints::cb_checkVcounter_i(Fl_Check_Button* o, void*) {
  this->vdp_vcounter(o->value());
}
void DialogBreakpoints::cb_checkVcounter(Fl_Check_Button* o, void* v) {
  ((DialogBreakpoints*)(o->parent()->parent()->user_data()))->cb_checkVcounter_i(o,v);
}

/**
   Dialog constructor
*/
DialogBreakpoints::DialogBreakpoints() {
  { windowDialog = new Fl_Double_Window(376, 457, "Breakpoints");
    windowDialog->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(15, 235, 340, 95, "New breakpoint");
      { textAddress = new Fl_Input(70, 275, 80, 25, "Address");
        textAddress->textfont(13);
      } // Fl_Input* textAddress
      { checkIo = new Fl_Check_Button(35, 250, 25, 25, "IO");
        checkIo->down_box(FL_DOWN_BOX);
        checkIo->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkIo
      { checkPc = new Fl_Check_Button(90, 250, 25, 25, "PC");
        checkPc->down_box(FL_DOWN_BOX);
        checkPc->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkPc
      { checkRead = new Fl_Check_Button(150, 250, 25, 25, "Read");
        checkRead->down_box(FL_DOWN_BOX);
        checkRead->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkRead
      { checkWrite = new Fl_Check_Button(210, 250, 25, 25, "Write");
        checkWrite->down_box(FL_DOWN_BOX);
        checkWrite->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkWrite
      { textNote = new Fl_Input(195, 275, 135, 25, "Note");
        textNote->textfont(13);
      } // Fl_Input* textNote
      { buttonCreate = new Fl_Button(15, 305, 80, 25, "Create");
        buttonCreate->callback((Fl_Callback*)cb_buttonCreate);
      } // Fl_Button* buttonCreate
      { buttonRemove = new Fl_Button(95, 305, 80, 25, "Remove");
        buttonRemove->callback((Fl_Callback*)cb_buttonRemove);
      } // Fl_Button* buttonRemove
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(15, 20, 355, 145, "Common breakpoints");
      { checkVdpcontrol = new Fl_Check_Button(150, 50, 25, 25, "VDP Control");
        checkVdpcontrol->down_box(FL_DOWN_BOX);
        checkVdpcontrol->callback((Fl_Callback*)cb_checkVdpcontrol);
        checkVdpcontrol->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkVdpcontrol
      { checkPsgwrite = new Fl_Check_Button(280, 100, 25, 25, "PSG Write");
        checkPsgwrite->down_box(FL_DOWN_BOX);
        checkPsgwrite->align(Fl_Align(FL_ALIGN_LEFT));
        checkPsgwrite->deactivate();
      } // Fl_Check_Button* checkPsgwrite
      { checkVdpread = new Fl_Check_Button(150, 25, 25, 25, "VDP Data Read");
        checkVdpread->down_box(FL_DOWN_BOX);
        checkVdpread->callback((Fl_Callback*)cb_checkVdpread);
        checkVdpread->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkVdpread
      { checkVdpwrite = new Fl_Check_Button(280, 25, 25, 25, "VDP Data Write");
        checkVdpwrite->down_box(FL_DOWN_BOX);
        checkVdpwrite->callback((Fl_Callback*)cb_checkVdpwrite);
        checkVdpwrite->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkVdpwrite
      { checkVcounter = new Fl_Check_Button(150, 75, 25, 25, "V Counter");
        checkVcounter->down_box(FL_DOWN_BOX);
        checkVcounter->callback((Fl_Callback*)cb_checkVcounter);
        checkVcounter->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkVcounter
      { checkHcounter = new Fl_Check_Button(150, 100, 25, 25, "H Counter");
        checkHcounter->down_box(FL_DOWN_BOX);
        checkHcounter->align(Fl_Align(FL_ALIGN_LEFT));
        checkHcounter->deactivate();
      } // Fl_Check_Button* checkHcounter
      o->end();
    } // Fl_Group* o
    windowDialog->end();
  } // Fl_Double_Window* windowDialog
  //Initial values
  textAddress->value("0x0000");
  textNote->value("Pointless pointer breakpoint");
}

void DialogBreakpoints::set_breakpoint_table(uint8_t* p) {
  this->bp_table = p;
}

void DialogBreakpoints::vdp_data(uint8_t enable, uint8_t read) {
  const uint8_t en_value = read ? Z80_BREAK_IO_RD : Z80_BREAK_IO_WR;
  const uint8_t value = enable ? en_value : 0;
  //Add breakpoint at even ports in range [0x80-0xBF]
  for(int i=0x80; i<=0xBF; i+=2){
    bp_table[i] = value;
  }
}

void DialogBreakpoints::vdp_control(uint8_t enable) {
  const uint8_t v = enable ? Z80_BREAK_IO_RD : 0;
  //Set a read breakpoint at odd ports in range [0x80-0xBF]
  for(int i = 0x81; i<= 0xBF; i+=2){
    bp_table[i] = v;
  }
}

void DialogBreakpoints::vdp_vcounter(uint8_t enable) {
  //Make an io read breakpoint at even ports in range [0x40-0x7f]
  const uint8_t v = enable ? Z80_BREAK_IO_RD : 0;
  for(int i = 0x40; i<=0x7F; i+=2){
     bp_table[i] = v;
  }
}
