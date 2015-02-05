#include "z80_opcodes.h"
#include "z80_macros.h"
#include "z80_register_lut.h"

extern struct z80_s z80; //<-- Access to z80 internals

///ADD HL, rp[p] ; Size: 1; Flags N,C
int z80_op_ADD_HL_rp(){
    Z80_OPCODE_SUBDIV;
    const uint16_t old_hl = Z80_HL;
    Z80_HL = Z80_HL + *z80_rp[p[0]];
    //Clear N/Carry flag (bits 1,0)
    Z80_F = (Z80_F & (Z80_CLRFLAG_CARRY & Z80_CLRFLAG_ADD))
        //Set carry flag (bit 0)
        | Z80_SETFLAG_CARRY(old_hl, Z80_HL);
    return Z80_STAGE_RESET;
}

///ADD n; Size 2; Flags:ALL
int z80_op_ADD_n(){
    const uint8_t orig_a = Z80_A;
    Z80_A = Z80_A + z80.opcode[1];
    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_HC(orig_a, Z80_A);
    Z80_F |= Z80_SETFLAG_OVERFLOW(orig_a, Z80_A);
    Z80_F |= Z80_SETFLAG_CARRY(orig_a, Z80_A);
    return Z80_STAGE_RESET;
}

///EX AF, AFp; Size: 1; Flags: None
int z80_op_EX(){
    const uint16_t tmp_af = Z80_AF;
    Z80_AF = Z80_AFp;
    Z80_AFp = tmp_af;
    return Z80_STAGE_RESET;
}

///LD A, DE
int z80_op_LD_A_DE(){
    if (z80.read_index == 0){
        z80.read_address = Z80_DE;
        return Z80_STAGE_M2;
    }
    else{
        Z80_A = z80.read_buffer[0];
        return Z80_STAGE_RESET;
    }
}

///LD (BC), A; Size:1; Flags: None
int z80_op_LD_BC_A(){
    //If the write has not been performed, request it
    if (z80.write_index == 0){
        z80.write_address = Z80_BC;
        z80.write_buffer[0] = Z80_A;
        return Z80_STAGE_M3;
    }
    //Otherwise, reset pipeline
    else{
        return Z80_STAGE_RESET;
    }
}

///LD (DE), A; Size: 1; Flags: None
int z80_op_LD_DE_A(){
    if (z80.write_index == 0){
        z80.write_address = Z80_DE;
        z80.write_buffer[0] = Z80_A;
        return Z80_STAGE_M3;
    }
    else{
        return Z80_STAGE_RESET;
    }
}

///NOP; Size: 1; Flags: None
int z80_op_NOP(){
    return Z80_STAGE_RESET;
}

