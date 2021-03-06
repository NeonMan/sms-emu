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

#include "test_z80.h"
#include "unity/unity.h"
#include "unity/unity_fixture.h"
#include <stdio.h>

#include <savestate/savestate.h>
#include <ram/ram.h>
#include <z80/z80.h>
#include <z80/z80_macros.h>
#include <psg/psg.h>
#include <io/io.h>
#include <peripheral/peripheral.h>
#include <rom/rom.h>
#include <vdp/vdp.h>
#include <vdp/vdp_internals.h>

// --- Constants ---
#define SAVE_FILE_NAME "SAMPLE.SAV"

#define VALUE_ADDRESS 0x0102
#define VALUE_DATA    0x03
#define VALUE_RD      0x04
#define VALUE_WR      0x05
#define VALUE_IOREQ   0x06
#define VALUE_MREQ    0x07
#define VALUE_RFSH    0x08
#define VALUE_M1      0x09
#define VALUE_INT     0x0A
#define VALUE_NMI     0x0B
#define VALUE_RESET   0x0C
#define VALUE_WAIT    0x0D
#define VALUE_BUSREQ  0x0E
#define VALUE_BUSACK  0x0F

static const uint16_t psg_tone_pattern[4] = {0x1011, 0x1213, 0x1415, 0x1617};
static const uint8_t  psg_volume_pattern[4] = {0x18, 0x19, 0x1A, 0x1B};

#define VALUE_IO_STAT 0x1C

#define VALUE_PERIPHERAL_CONTROL 0x1D
#define VALUE_PERIPHERAL_AB 0x1E
#define VALUE_PERIPHERAL_BM 0x1F

#define ROM_FILE_NAME "SAMPLE.ROM"
#define VALUE_SLOT0 0x20
#define VALUE_SLOT1 0x21
#define VALUE_SLOT2 0x22
#define VALUE_RAM 0x23

// --- Variables ---
static struct z80_s z80_pattern;
static struct z80_s z80_zero;
static struct vdp_s vdp_pattern;

static uint8_t ram_pattern[RAM_SIZE];
static uint8_t vram_pattern[VDP_VRAM_SIZE];

TEST_GROUP(grp_savestate);

// --- Tests ---
TEST_SETUP(grp_savestate) {
    //Initialize with pattern
    for (int i = 0; i < (sizeof(struct z80_s)); ++i) {
        ((uint8_t*)&z80_pattern)[i] = (uint8_t)i;
    }
    for (int i = 0; i < sizeof(struct vdp_s); ++i) {
        ((uint8_t*)&vdp_pattern)[i] = (uint8_t)i;
    }
    for (int i = 0; i < RAM_SIZE; ++i) {
        ram_pattern[i] = (uint8_t)i;
    }
    for (int i = 0; i < VDP_VRAM_SIZE; ++i) {
        vram_pattern[i] = (uint8_t)i;
    }

    //Initialize with zeros
    memset(&z80_zero, 0, sizeof(struct z80_s));

    //Initialize modules with pattern
    *z80dbg_get_z80() = z80_pattern;
    vdp = vdp_pattern;
    memcpy(ramdbg_get_mem(), ram_pattern, RAM_SIZE);
    memcpy(vdp_get_vram(), vram_pattern, VDP_VRAM_SIZE);
    z80_address = VALUE_ADDRESS;
    z80_data = VALUE_DATA;
    z80_n_rd = VALUE_RD;
    z80_n_wr = VALUE_WR;
    z80_n_ioreq = VALUE_IOREQ;
    z80_n_mreq = VALUE_MREQ;
    z80_n_rfsh = VALUE_RFSH;
    z80_n_m1 = VALUE_M1;
    z80_n_int = VALUE_INT;
    z80_n_nmi = VALUE_NMI;
    z80_n_reset = VALUE_RESET;
    z80_n_wait = VALUE_WAIT;
    z80_n_busreq = VALUE_BUSREQ;
    z80_n_busack = VALUE_BUSACK;

    for (int i = 0; i < 4; ++i){
        psgdbg_get_tone()[i] = psg_tone_pattern[i];
        psgdbg_get_volume()[i] = psg_volume_pattern[i];
    }

    io_stat = VALUE_IO_STAT;

    *perdbg_reg_ab() = VALUE_PERIPHERAL_AB;
    *perdbg_reg_bm() = VALUE_PERIPHERAL_BM;
    *perdbg_reg_control() = VALUE_PERIPHERAL_CONTROL;

    *romdbg_get_slot(0) = VALUE_SLOT0;
    *romdbg_get_slot(1) = VALUE_SLOT1;
    *romdbg_get_slot(2) = VALUE_SLOT2;
    *romdbg_get_slot(3) = VALUE_RAM;


    //Dump file
    FILE* f;
    f = fopen(SAVE_FILE_NAME, "wb");
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL(0, ss_save(f, SAVE_FILE_NAME));
    fclose(f);

    //Clear modules
    *z80dbg_get_z80() = z80_zero;
    memset(&vdp, 0, sizeof(struct vdp_s));
    memset(ramdbg_get_mem(), 0, RAM_SIZE);
    memset(vdp_get_vram(), 0, VDP_VRAM_SIZE);
    z80_address = 0;
    z80_data = 0;
    z80_n_rd = 0;
    z80_n_wr = 0;
    z80_n_ioreq = 0;
    z80_n_mreq = 0;
    z80_n_rfsh = 0;
    z80_n_m1 = 0;
    z80_n_int = 0;
    z80_n_nmi = 0;
    z80_n_reset = 0;
    z80_n_wait = 0;
    z80_n_busreq = 0;
    z80_n_busack = 0;

    for (int i = 0; i < 4; ++i){
        psgdbg_get_tone()[i] = 0;
        psgdbg_get_volume()[i] = 0;
    }

    io_stat = 0;

    *perdbg_reg_ab() = 0;
    *perdbg_reg_bm() = 0;
    *perdbg_reg_control() = 0;

    *romdbg_get_slot(0) = 0;
    *romdbg_get_slot(1) = 0;
    *romdbg_get_slot(2) = 0;
    *romdbg_get_slot(3) = 0;

    //Restore
    f = fopen(SAVE_FILE_NAME, "rb");
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL(0, ss_restore(f));
    fclose(f);
}

TEST_TEAR_DOWN(grp_savestate) {
    remove(SAVE_FILE_NAME);
}

TEST(grp_savestate, peripheral){
    TEST_ASSERT_EQUAL(VALUE_PERIPHERAL_AB, *perdbg_reg_ab());
    TEST_ASSERT_EQUAL(VALUE_PERIPHERAL_BM, *perdbg_reg_bm());
    TEST_ASSERT_EQUAL(VALUE_PERIPHERAL_CONTROL, *perdbg_reg_control());
}

TEST(grp_savestate, ioc){
    TEST_ASSERT_EQUAL(VALUE_IO_STAT, io_stat);
}

TEST(grp_savestate, psg){
    TEST_ASSERT_EQUAL_INT16_ARRAY(psg_tone_pattern, psgdbg_get_tone(), 4);
    TEST_ASSERT_EQUAL_INT8_ARRAY(psg_volume_pattern, psgdbg_get_volume(), 4);
}

TEST(grp_savestate, ram) {
    TEST_ASSERT_EQUAL_HEX8_ARRAY(ram_pattern, ramdbg_get_mem(), RAM_SIZE);
}

TEST(grp_savestate, z80_pins) {
    TEST_ASSERT_EQUAL(VALUE_ADDRESS, z80_address);
    TEST_ASSERT_EQUAL(VALUE_DATA, z80_data);
    TEST_ASSERT_EQUAL(VALUE_RD, z80_n_rd);
    TEST_ASSERT_EQUAL(VALUE_WR, z80_n_wr);
    TEST_ASSERT_EQUAL(VALUE_IOREQ, z80_n_ioreq);
    TEST_ASSERT_EQUAL(VALUE_MREQ, z80_n_mreq);
    TEST_ASSERT_EQUAL(VALUE_RFSH, z80_n_rfsh);
    TEST_ASSERT_EQUAL(VALUE_M1, z80_n_m1);
    TEST_ASSERT_EQUAL(VALUE_INT, z80_n_int);
    TEST_ASSERT_EQUAL(VALUE_NMI, z80_n_nmi);
    TEST_ASSERT_EQUAL(VALUE_RESET, z80_n_reset);
    TEST_ASSERT_EQUAL(VALUE_WAIT, z80_n_wait);
    TEST_ASSERT_EQUAL(VALUE_BUSREQ, z80_n_busreq);
    TEST_ASSERT_EQUAL(VALUE_BUSACK, z80_n_busack);
}

TEST(grp_savestate, z80) {
    const struct z80_s z80_ = *z80dbg_get_z80();
    TEST_ASSERT_EQUAL(z80_pattern.data_latch, z80_.data_latch);
    TEST_ASSERT_EQUAL(z80_pattern.m1_tick_count, z80_.m1_tick_count);
    TEST_ASSERT_EQUAL(z80_pattern.m2_tick_count, z80_.m2_tick_count);
    TEST_ASSERT_EQUAL(z80_pattern.m3_tick_count, z80_.m3_tick_count);
    TEST_ASSERT_EQUAL(z80_pattern.opcode_index, z80_.opcode_index);
    TEST_ASSERT_EQUAL(z80_pattern.read_address, z80_.read_address);
    TEST_ASSERT_EQUAL(z80_pattern.read_index, z80_.read_index);
    TEST_ASSERT_EQUAL(z80_pattern.read_is_io, z80_.read_is_io);
    TEST_ASSERT_EQUAL(z80_pattern.stage, z80_.stage);
    TEST_ASSERT_EQUAL(z80_pattern.write_address, z80_.write_address);
    TEST_ASSERT_EQUAL(z80_pattern.write_index, z80_.write_index);
    TEST_ASSERT_EQUAL(z80_pattern.write_is_io, z80_.write_is_io);
    TEST_ASSERT_EQUAL(z80_pattern.rI, z80_.rI);
    TEST_ASSERT_EQUAL(z80_pattern.rR, z80_.rR);
    TEST_ASSERT_EQUAL(z80_pattern.rIX, z80_.rIX);
    TEST_ASSERT_EQUAL(z80_pattern.rIY, z80_.rIY);
    TEST_ASSERT_EQUAL(z80_pattern.rPC, z80_.rPC);
    TEST_ASSERT_EQUAL(z80_pattern.rSP, z80_.rSP);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.iff, z80_.iff, 2);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.opcode, z80_.opcode, 4);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.rAF, z80_.rAF, 4);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.rBC, z80_.rBC, 4);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.rDE, z80_.rDE, 4);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.rHL, z80_.rHL, 4);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.read_buffer, z80_.read_buffer, 2);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(z80_pattern.write_buffer, z80_.write_buffer, 2);
}

TEST(grp_savestate, mapper){
    TEST_ASSERT_EQUAL_UINT8(VALUE_SLOT0, *romdbg_get_slot(0));
    TEST_ASSERT_EQUAL_UINT8(VALUE_SLOT1, *romdbg_get_slot(1));
    TEST_ASSERT_EQUAL_UINT8(VALUE_SLOT2, *romdbg_get_slot(2));
}

TEST(grp_savestate, vram) {
    TEST_ASSERT_EQUAL_UINT8_ARRAY(vram_pattern, vdp_get_vram(), VDP_VRAM_SIZE);
}

IGNORE_TEST(grp_savestate, vdp) {
    
}

TEST_GROUP_RUNNER(grp_savestate) {
    RUN_TEST_CASE(grp_savestate, ram);
    RUN_TEST_CASE(grp_savestate, z80);
    RUN_TEST_CASE(grp_savestate, z80_pins);
    RUN_TEST_CASE(grp_savestate, psg);
    RUN_TEST_CASE(grp_savestate, ioc);
    RUN_TEST_CASE(grp_savestate, peripheral);
    RUN_TEST_CASE(grp_savestate, mapper);
    RUN_TEST_CASE(grp_savestate, vram);
    RUN_TEST_CASE(grp_savestate, vdp);
}

// ----------------------
// --- Helpers & Main ---
// ----------------------
//Helper 'run all' function
static void RunAllTests(void) {
    RUN_TEST_GROUP(grp_savestate);
}

//Main
int main(int argc, const char** argv) {
    int rv = UnityMain(argc, argv, RunAllTests);
    return rv;
}
