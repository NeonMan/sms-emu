// Copyright 2015 Juan Luis Álvarez Martínez
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "z80_opcodes.h"
#include "z80_macros.h"
#include "z80_register_lut.h"
#include <assert.h>

extern struct z80_s z80; //<-- Access to z80 internals

///ADC n; Size: 2; Flags: ???
int ADC_n() {
    assert(z80.opcode_index == 2);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///ADC (HL); Size: 1; Flags: ???
int ADC_HLp() {
    assert(z80.opcode_index == 1);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///ADC r; Size: 1; Flags: ???
int ADC_r() {
    assert(z80.opcode_index == 1);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///ADD (HL); Size: 1; Flags: ???
int ADD_HLp() {
    assert(z80.opcode_index == 1);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///ADD n; Size 2; Flags:ALL
int ADD_n() {
    assert(z80.opcode_index == 2);
    const uint8_t orig_a = Z80_A;
    Z80_A = Z80_A + z80.opcode[1];
    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_HALF_CARRY(orig_a, z80.opcode[1]);
    Z80_F |= Z80_SETFLAG_OVERFLOW(orig_a, Z80_A);
    Z80_F |= Z80_SETFLAG_CARRY(orig_a, Z80_A);
    return Z80_STAGE_RESET;
}

///ADD r; Size: 1; Flags:ALL
int ADD_r() {
    assert(z80.opcode_index == 1);
    assert(0);
    return Z80_STAGE_RESET;
}

///AND n; Size 2; Flags:ALL
int AND_n() {
    assert(z80.opcode_index == 2);
    const uint8_t orig_a = Z80_A;
    Z80_A = Z80_A & z80.opcode[1];
    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_OVERFLOW(orig_a, Z80_A);
    Z80_F |= Z80_FLAG_HC;
    return Z80_STAGE_RESET;
}

///AND r[z]; Size: 1; Flags: All
int AND_r() {
    assert(z80.opcode_index == 1);
    Z80_OPCODE_SUBDIV;
    assert(z[0] != Z80_R_INDEX_HL);

    const uint8_t orig_a = Z80_A;
    Z80_A = Z80_A & (*(z80_r[z[0]]));

    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_FLAG_HC;
    Z80_F |= Z80_SETFLAG_OVERFLOW(orig_a, Z80_A);
    return Z80_STAGE_RESET;
}

///AND (HL); Size: 1; Flags: ???
int AND_HLp() {
    assert(z80.opcode_index == 1);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///CP n; Size: 2; Flags: All
int CP_n() {
    assert(z80.opcode_index == 2);
    Z80_F = 0;
    Z80_F |= Z80_FLAG_SUBTRACT; //Flag is set, always
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A - z80.opcode[1]);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A - z80.opcode[1]);
    Z80_F |= Z80_SETFLAG_HALF_BORROW(Z80_A, z80.opcode[1]);
    Z80_F |= Z80_SETFLAG_OVERFLOW(Z80_A, Z80_A - z80.opcode[1]);
    Z80_F |= Z80_SETFLAG_BORROW(Z80_A, Z80_A - z80.opcode[1]);
    return Z80_STAGE_RESET;
}

///CP (HL); Size: 1; Flags: ???
int CP_HLp() {
    assert(z80.opcode_index == 1);
    Z80_8BIT_READ(Z80_HL, 0);
    const uint8_t result = Z80_A - z80.read_buffer[0];

    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(result);
    Z80_F |= Z80_SETFLAG_ZERO(result);
    Z80_F |= Z80_SETFLAG_HALF_BORROW(Z80_A, result);
    Z80_F |= Z80_SETFLAG_OVERFLOW(Z80_A, result);
    Z80_F |= Z80_FLAG_SUBTRACT;
    Z80_F |= Z80_SETFLAG_BORROW(Z80_A, result);
    return Z80_STAGE_RESET;
}

///CP r[z]; Size: 1; Flags: All
int CP_r() {
    assert(z80.opcode_index == 1);
    Z80_OPCODE_SUBDIV;
    assert(z[0] != Z80_R_INDEX_HL);

    uint8_t new_a;
    new_a = Z80_A - *(z80_r[z[0]]);

    Z80_F = Z80_SETFLAG_SIGN(Z80_A)
        | Z80_SETFLAG_ZERO(Z80_A)
        | Z80_SETFLAG_HALF_BORROW(Z80_A, *(z80_r[z[0]]))
        | Z80_SETFLAG_OVERFLOW(Z80_A, new_a)
        | Z80_FLAG_SUBTRACT
        | Z80_SETFLAG_BORROW(Z80_A, new_a);
    return Z80_STAGE_RESET;
}

///DEC(r[y]); Size:1; Flags: S,Z,H,P,N
int DEC_r() {
    assert(z80.opcode_index == 1);
    Z80_OPCODE_SUBDIV;
    const uint8_t old_r = *z80_r[y[0]];
    --(*(z80_r[y[0]]));
    Z80_F = (Z80_F & (
        Z80_CLRFLAG_SIGN & Z80_CLRFLAG_ZERO & Z80_CLRFLAG_HC
        & Z80_CLRFLAG_PARITY & Z80_CLRFLAG_SUBTRACT)
        )  //Clear S,Z,H,P,N (7,6,4,2,1) ***V0-
        | Z80_SETFLAG_SIGN(*z80_r[y[0]])
        | Z80_SETFLAG_ZERO(*z80_r[y[0]])
        | Z80_SETFLAG_HALF_BORROW(old_r, 1)
        | Z80_SETFLAG_OVERFLOW(*z80_r[y[0]], old_r);
    return Z80_STAGE_RESET;
}

///DEC (HL); Size: 1; Flags: ???
int DEC_HLp() {
    assert(z80.opcode_index == 1);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///INC r; Size: 1; Flags: All
int INC_r() {
    assert(z80.opcode_index == 1);
    Z80_OPCODE_SUBDIV;

    uint8_t old_r = *z80_r[y[0]];
    ++(*(z80_r[y[0]]));
    Z80_F = (Z80_F & (
        Z80_CLRFLAG_SIGN & Z80_CLRFLAG_ZERO & Z80_CLRFLAG_HC
        & Z80_CLRFLAG_PARITY & Z80_CLRFLAG_SUBTRACT)
        )  //Clear S,Z,H,P,N (7,6,4,2,1) ***V0-
        | Z80_SETFLAG_SIGN(*z80_r[y[0]])
        | Z80_SETFLAG_ZERO(*z80_r[y[0]])
        | Z80_SETFLAG_HALF_CARRY(old_r, 1)
        | Z80_SETFLAG_OVERFLOW(old_r, *z80_r[y[0]]);
    return Z80_STAGE_RESET;
}

///NEG; Size: 2; Flags: ???
int NEG() {
    assert(z80.opcode_index == 2);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///OR (HL); Size: 1; Flags: ???
int OR_HLp() {
    assert(z80.opcode_index == 1);
    Z80_OPCODE_SUBDIV;
    Z80_8BIT_READ(Z80_HL, 0);

    const uint8_t orig_a = Z80_A;
    Z80_A = Z80_A | z80.read_buffer[0];
    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_OVERFLOW(orig_a, Z80_A);
    return Z80_STAGE_RESET;

}

///OR n; Size: 2; Flags:ALL
int OR_n() {
    assert(z80.opcode_index == 2);
    const uint8_t orig_a = Z80_A;
    Z80_A = Z80_A | z80.opcode[1];
    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_OVERFLOW(orig_a, Z80_A);
    return Z80_STAGE_RESET;
}

///OR r[z]; Size: 1; Flags: All
int OR_r() {
    assert(z80.opcode_index == 1);
    Z80_OPCODE_SUBDIV;
    const uint8_t orig_a = Z80_A;

    Z80_A = Z80_A | *(z80_r[z[0]]);
    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_OVERFLOW(orig_a, Z80_A);
    return Z80_STAGE_RESET;
}

///SBC (HL); Size: 1; Flags: ???
int SBC_HLp() {
    assert(z80.opcode_index == 1);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///SBC n; Size: 2; Flags: ???
int SBC_n() {
    assert(z80.opcode_index == 2);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///SBC r; Size: 1; Flags: ???
int SBC_r() {
    assert(z80.opcode_index == 1);
    assert(0);
    return Z80_STAGE_RESET;
}

///SUB (HL); Size: 1; Flags: ???
int SUB_HLp() {
    assert(z80.opcode_index == 1);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///SUB n; Size: 2; Flags: ???
int SUB_n() {
    assert(z80.opcode_index == 2);
    assert(0); ///<-- Unimplemented
    return Z80_STAGE_RESET;
}

///SUB r; Size: 1; Flags: ???
int SUB_r() {
    assert(z80.opcode_index == 1);
    assert(0);
    return Z80_STAGE_RESET;
}

///XOR (HL); Size: 1; Flags: All
int XOR_HLp() {
    assert(z80.opcode_index == 1);
    Z80_8BIT_READ(Z80_HL, 0);
    Z80_A = Z80_A ^ z80.read_buffer[0];

    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_PARITY(Z80_A);
    return Z80_STAGE_RESET;
}

///XOR n; Size: 2; Flags: ???
int XOR_n() {
    assert(z80.opcode_index == 2);
    assert(0); ///<-- unimplemented
    return Z80_STAGE_RESET;
}

///XOR r[z]; Size: 1; Flags: All
int XOR_r() {
    Z80_OPCODE_SUBDIV;
    assert(z80.opcode_index == 1);
    assert(z80_r[z[0]] != 0);

    Z80_A = Z80_A ^ *(z80_r[z[0]]);

    Z80_F = 0;
    Z80_F |= Z80_SETFLAG_SIGN(Z80_A);
    Z80_F |= Z80_SETFLAG_ZERO(Z80_A);
    Z80_F |= Z80_SETFLAG_PARITY(Z80_A);
    return Z80_STAGE_RESET;
}

/* Stubs for IX/IY/(IX+d)/(IY+d)*/

int INC_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int DEC_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int ADD_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int ADC_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int SUB_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int SBC_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int AND_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int XOR_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int OR_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}

int CP_IXYp() {
    assert(0); /*<-- Unimplemented*/
    return Z80_STAGE_RESET;
}
