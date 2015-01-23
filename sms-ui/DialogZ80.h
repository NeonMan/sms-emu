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

#ifndef DialogZ80_h
#define DialogZ80_h
#include <FL/Fl.H>
#if 1
#include <stdint.h>
#include <z80/z80.h>
#include <z80/z80_macros.h>
#include <z80/z80_externs.h>
#include <z80/z80_dasm.h>
#endif
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Spinner.H>

/**
   Shows the z80 internal state
*/
class DialogZ80 {
  /**
     Pointer to z80 internals.
  */
  struct z80_s* z80_ptr = 0;
  /**
     A pointer to the z80 clock on/off variable.
  */
  uint32_t* running_ptr = 0; 
public:
  DialogZ80();
  Fl_Double_Window *windowDialog;
private:
  Fl_Output *textAF;
  Fl_Output *textBC;
  Fl_Output *textDE;
  Fl_Output *textHL;
  Fl_Output *textIX;
  Fl_Output *textIY;
  Fl_Output *textSP;
  Fl_Output *textPC;
  Fl_Output *textAFp;
  Fl_Output *textBCp;
  Fl_Output *textDEp;
  Fl_Output *textHLp;
  Fl_Output *textIR;
  Fl_Check_Button *checkM1;
  Fl_Check_Button *checkMreq;
  Fl_Check_Button *checkIoreq;
  Fl_Check_Button *checkRd;
  Fl_Check_Button *checkWr;
  Fl_Check_Button *checkRfsh;
  Fl_Check_Button *checkHalt;
  Fl_Check_Button *checkWait;
  Fl_Check_Button *checkInt;
  Fl_Check_Button *checkNmi;
  Fl_Check_Button *checkReset;
  Fl_Check_Button *checkClk;
  Fl_Check_Button *checkBusreq;
  Fl_Check_Button *checkBusack;
  Fl_Output *textAddress;
  Fl_Output *textData;
  Fl_Output *textOpcode;
  Fl_Output *textStage;
  Fl_Output *textDasm;
  Fl_Output *textRbuffer;
  Fl_Output *textWbuffer;
  Fl_Light_Button *buttonRunning;
  inline void cb_buttonRunning_i(Fl_Light_Button*, void*);
  static void cb_buttonRunning(Fl_Light_Button*, void*);
  Fl_Button *buttonEdge;
  inline void cb_buttonEdge_i(Fl_Button*, void*);
  static void cb_buttonEdge(Fl_Button*, void*);
  Fl_Spinner *spinEdgecount;
  Fl_Button *buttonStep;
public:
  Fl_Check_Button *checkCarry;
  Fl_Check_Button *checkAdd;
  Fl_Check_Button *checkParity;
  Fl_Check_Button *checkUnk3;
  Fl_Check_Button *checkHCarry;
  Fl_Check_Button *checkUnk5;
  Fl_Check_Button *checkZero;
  Fl_Check_Button *checkSign;
  void set_running_ptr(uint32_t* p);
  void set_z80_ptr(struct z80_s* p);
  void update_values();
};
#endif
