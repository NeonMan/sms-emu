// generated by Fast Light User Interface Designer (fluid) version 1.0303

#include "DialogZ80.h"
#if 1
#endif

void DialogZ80::cb_buttonRunning_i(Fl_Light_Button* o, void*) {
  uint32_t* volatile rp = running_ptr;
  
  if(this->running_ptr){
    if(o->value())
      *rp = UINT32_MAX;
    else
      *rp = 0;
  };
}
void DialogZ80::cb_buttonRunning(Fl_Light_Button* o, void* v) {
  ((DialogZ80*)(o->parent()->parent()->user_data()))->cb_buttonRunning_i(o,v);
}

void DialogZ80::cb_buttonEdge_i(Fl_Button*, void*) {
  uint32_t* volatile rp = running_ptr;
  
  if(this->running_ptr){
      *rp = (uint32_t) spinEdgecount->value();;
  };
}
void DialogZ80::cb_buttonEdge(Fl_Button* o, void* v) {
  ((DialogZ80*)(o->parent()->parent()->user_data()))->cb_buttonEdge_i(o,v);
}

DialogZ80::DialogZ80() {
  { windowDialog = new Fl_Double_Window(565, 280, "z80");
    windowDialog->user_data((void*)(this));
    windowDialog->align(Fl_Align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE));
    { Fl_Group* o = new Fl_Group(0, 20, 165, 265, "Registers");
      { textAF = new Fl_Output(25, 30, 50, 30, "AF");
        textAF->textfont(13);
      } // Fl_Output* textAF
      { textBC = new Fl_Output(25, 60, 50, 30, "BC");
        textBC->textfont(13);
      } // Fl_Output* textBC
      { textDE = new Fl_Output(25, 90, 50, 30, "DE");
        textDE->textfont(13);
      } // Fl_Output* textDE
      { textHL = new Fl_Output(25, 120, 50, 30, "HL");
        textHL->textfont(13);
      } // Fl_Output* textHL
      { textIX = new Fl_Output(25, 150, 50, 30, "IX");
        textIX->textfont(13);
      } // Fl_Output* textIX
      { textIY = new Fl_Output(25, 180, 50, 30, "IY");
        textIY->textfont(13);
      } // Fl_Output* textIY
      { textSP = new Fl_Output(25, 215, 50, 30, "SP");
        textSP->textfont(13);
      } // Fl_Output* textSP
      { textPC = new Fl_Output(25, 245, 50, 30, "PC");
        textPC->textfont(13);
      } // Fl_Output* textPC
      { textAFp = new Fl_Output(110, 30, 50, 30, "AF\'");
        textAFp->textfont(13);
      } // Fl_Output* textAFp
      { textBCp = new Fl_Output(110, 60, 50, 30, "BC\'");
        textBCp->textfont(13);
      } // Fl_Output* textBCp
      { textDEp = new Fl_Output(110, 90, 50, 30, "DE\'");
        textDEp->textfont(13);
      } // Fl_Output* textDEp
      { textHLp = new Fl_Output(110, 120, 50, 30, "HL\'");
        textHLp->textfont(13);
      } // Fl_Output* textHLp
      { textIR = new Fl_Output(110, 150, 50, 30, "IR");
        textIR->textfont(13);
      } // Fl_Output* textIR
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(190, 20, 235, 165, "Signals");
      { checkM1 = new Fl_Check_Button(245, 25, 25, 25, "!M1");
        checkM1->down_box(FL_DOWN_BOX);
        checkM1->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkM1
      { checkMreq = new Fl_Check_Button(245, 45, 25, 25, "!MREQ");
        checkMreq->down_box(FL_DOWN_BOX);
        checkMreq->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkMreq
      { checkIoreq = new Fl_Check_Button(245, 65, 25, 25, "!IOREQ");
        checkIoreq->down_box(FL_DOWN_BOX);
        checkIoreq->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkIoreq
      { checkRd = new Fl_Check_Button(245, 85, 25, 25, "!RD");
        checkRd->down_box(FL_DOWN_BOX);
        checkRd->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkRd
      { checkWr = new Fl_Check_Button(245, 105, 25, 25, "!WR");
        checkWr->down_box(FL_DOWN_BOX);
        checkWr->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkWr
      { checkRfsh = new Fl_Check_Button(245, 125, 25, 25, "!RFSH");
        checkRfsh->down_box(FL_DOWN_BOX);
        checkRfsh->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkRfsh
      { checkHalt = new Fl_Check_Button(245, 145, 25, 25, "!HALT");
        checkHalt->down_box(FL_DOWN_BOX);
        checkHalt->align(Fl_Align(FL_ALIGN_LEFT));
        checkHalt->deactivate();
      } // Fl_Check_Button* checkHalt
      { checkWait = new Fl_Check_Button(330, 25, 25, 25, "!WAIT");
        checkWait->down_box(FL_DOWN_BOX);
        checkWait->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkWait
      { checkInt = new Fl_Check_Button(330, 45, 25, 25, "!INT");
        checkInt->down_box(FL_DOWN_BOX);
        checkInt->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkInt
      { checkNmi = new Fl_Check_Button(330, 65, 25, 25, "!NMI");
        checkNmi->down_box(FL_DOWN_BOX);
        checkNmi->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkNmi
      { checkReset = new Fl_Check_Button(330, 85, 25, 25, "!RESET");
        checkReset->down_box(FL_DOWN_BOX);
        checkReset->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkReset
      { checkClk = new Fl_Check_Button(330, 105, 25, 25, "!CLK");
        checkClk->down_box(FL_DOWN_BOX);
        checkClk->align(Fl_Align(FL_ALIGN_LEFT));
        checkClk->deactivate();
      } // Fl_Check_Button* checkClk
      { checkBusreq = new Fl_Check_Button(330, 125, 25, 25, "!BUSRQ");
        checkBusreq->down_box(FL_DOWN_BOX);
        checkBusreq->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkBusreq
      { checkBusack = new Fl_Check_Button(330, 145, 25, 25, "!BUSACK");
        checkBusack->down_box(FL_DOWN_BOX);
        checkBusack->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Check_Button* checkBusack
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(190, 195, 170, 90, "Buses");
      { textAddress = new Fl_Output(245, 205, 105, 25, "Address");
        textAddress->textfont(13);
      } // Fl_Output* textAddress
      { textData = new Fl_Output(245, 230, 105, 25, "Data");
        textData->textfont(13);
      } // Fl_Output* textData
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(355, 20, 225, 140, "Internal state");
      { textOpcode = new Fl_Output(420, 30, 140, 25, "Opcode");
        textOpcode->textfont(13);
      } // Fl_Output* textOpcode
      { textStage = new Fl_Output(420, 80, 45, 25, "Stage");
        textStage->textfont(13);
      } // Fl_Output* textStage
      { textDasm = new Fl_Output(420, 55, 140, 25, "Disasm");
        textDasm->textfont(13);
      } // Fl_Output* textDasm
      { textRbuffer = new Fl_Output(420, 105, 140, 25, "R Buffer");
        textRbuffer->textfont(13);
      } // Fl_Output* textRbuffer
      { textWbuffer = new Fl_Output(420, 130, 140, 25, "W Buffer");
        textWbuffer->textfont(13);
      } // Fl_Output* textWbuffer
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(360, 175, 215, 100, "Buttons");
      o->labeltype(FL_NO_LABEL);
      { buttonRunning = new Fl_Light_Button(430, 200, 125, 25, "Running");
        buttonRunning->callback((Fl_Callback*)cb_buttonRunning);
      } // Fl_Light_Button* buttonRunning
      { buttonEdge = new Fl_Button(430, 225, 75, 25, "Edge");
        buttonEdge->callback((Fl_Callback*)cb_buttonEdge);
      } // Fl_Button* buttonEdge
      { spinEdgecount = new Fl_Spinner(505, 225, 50, 25);
      } // Fl_Spinner* spinEdgecount
      { buttonStep = new Fl_Button(430, 250, 125, 25, "Step");
        buttonStep->deactivate();
      } // Fl_Button* buttonStep
      o->end();
    } // Fl_Group* o
    windowDialog->end();
  } // Fl_Double_Window* windowDialog
  // --- BEGIN Initial vaules ---
  //Main registers
  this->textAF->value("0x0000 ?");
  this->textBC->value("0x0000 ?");
  this->textDE->value("0x0000 ?");
  this->textHL->value("0x0000 ?");
  this->textIX->value("0x0000 ?");
  this->textIY->value("0x0000 ?");
  this->textSP->value("0x0000 ?");
  this->textPC->value("0x0000 ?");
  this->textIR->value("0x0000 ?");
  //'prime' registers
  this->textAFp->value("0x0000 ?");
  this->textBCp->value("0x0000 ?");
  this->textDEp->value("0x0000 ?");
  this->textHLp->value("0x0000 ?");
  //Buses
  this->textAddress->value("0x0000 ?");
  this->textData->value("0x0000 ?");
  //Internals
  this->textOpcode->value("NOP ?");
  this->textStage->value("M1 ?");
  //Buttons
  this->buttonRunning->value(1);
  // --- END Initial values ---
}

/**
   Sets a pointer to the clock on/of var.
*/
void DialogZ80::set_running_ptr(uint32_t* p) {
  this->running_ptr = p;
}

/**
   Sets a pointer to the z80 internals struct.
*/
void DialogZ80::set_z80_ptr(struct z80_s* p) {
  this->z80_ptr = p;
}

/**
   Updates the dialog values
*/
void DialogZ80::update_values() {
  if(this->z80_ptr){    
      /*to use the Z80_* macros, the z80
        struct variable must be accesible
        by the identifier 'z80'*/
      #define z80 (*(this->z80_ptr))
      #define __TMP_STR_LEN 64
      char tmp_str[__TMP_STR_LEN];
      memset(tmp_str,0,__TMP_STR_LEN);
      
      // --- Update z80 registers ---
      //AF
      sprintf(tmp_str, "0x%04X", Z80_AF);
      textAF->value(tmp_str);
      //BC
      sprintf(tmp_str, "0x%04X", Z80_BC);
      textBC->value(tmp_str);
      //DE
      sprintf(tmp_str, "0x%04X", Z80_DE);
      textDE->value(tmp_str);
      //HL
      sprintf(tmp_str, "0x%04X", Z80_HL);
      textHL->value(tmp_str);
      //IX
      sprintf(tmp_str, "0x%04X", Z80_IX);
      textIX->value(tmp_str);
      //IY
      sprintf(tmp_str, "0x%04X", Z80_IY);
      textIY->value(tmp_str);
      //SP
      sprintf(tmp_str, "0x%04X", Z80_SP);
      textSP->value(tmp_str);
      //PC
      sprintf(tmp_str, "0x%04X", Z80_PC);
      textPC->value(tmp_str);
      
      //AF'
      sprintf(tmp_str, "0x%04X", Z80_AFp);
      textAFp->value(tmp_str);
      //BC'
      sprintf(tmp_str, "0x%04X", Z80_BCp);
      textBCp->value(tmp_str);
      //DE'
      sprintf(tmp_str, "0x%04X", Z80_DEp);
      textDEp->value(tmp_str);
      //HL'
      sprintf(tmp_str, "0x%04X", Z80_HLp);
      textHLp->value(tmp_str);
      
      //IR
      sprintf(tmp_str, "0x%02X%02X", Z80_I, Z80_R);
      textIR->value(tmp_str);
      
      // --- Update signals ---
      checkM1->value(1 && z80_n_m1);
      checkMreq->value(1 && z80_n_mreq);
      checkIoreq->value(1 && z80_n_ioreq);
      checkRd->value(1 && z80_n_rd);
      checkWr->value(1 && z80_n_wr);
      checkRfsh->value(1 && z80_n_rfsh);
      //checkHalt->value(1 && z80_n_halt);
      checkWait->value(1 && z80_n_wait);
      checkInt->value(1 && z80_n_int);
      checkNmi->value(1 && z80_n_nmi);
      checkReset->value(1 && z80_n_reset);
      checkBusreq->value(1 && z80_n_busreq);
      checkBusack->value(1 && z80_n_busack);
      
      // --- Update buses ---
      //Data
      sprintf(tmp_str, "0x%04X", z80_data);
      textData->value(tmp_str);
      //Address
      sprintf(tmp_str, "0x%04X", z80_address);
      textAddress->value(tmp_str);
      
      // --- Internals ---
      //Opcode
      sprintf(tmp_str, "%02X %02X %02X %02X (%d)", z80.opcode[0], z80.opcode[1], z80.opcode[2], z80.opcode[3], z80.opcode_index);
      textOpcode->value(tmp_str);
      //Stage
      switch(z80.stage){
        case 0:
        textStage->value("Reset"); break;
        case 1:
        textStage->value("M1"); break;
        case 2:
        textStage->value("M2"); break;
        case 3:
        textStage->value("M3"); break;
        default:
        sprintf(tmp_str, "%d !", z80.stage);
        textStage->value(tmp_str); break;
      }
      //Read buffer
      sprintf(tmp_str, "%02X %02X (%d)", z80.read_buffer[0], z80.read_buffer[1], z80.read_index);
      textRbuffer->value(tmp_str);
      //Write buffer
      sprintf(tmp_str, "%02X %02X (%d)", z80.write_buffer[0], z80.write_buffer[1], z80.write_index);
      textWbuffer->value(tmp_str);
      //Disasm
      z80d_opcode op = z80d_decode_op(z80.opcode, Z80_PC);
      sprintf(tmp_str, "%s ;(Size: %d)", op.opcode_str, op.size);
      textDasm->value(tmp_str);
      #undef z80
    }
}
