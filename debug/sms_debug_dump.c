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

#include "sms_debug.h"
#include <stdio.h>
#include "savestate/savestate.h"

#ifdef WIN32
#include <assert.h>
static void platform_assert(const char* exp, const char* file, unsigned int line) {
    assert(0);
}
#else
static void platform_assert(const char* exp, const char* file, unsigned int line) {
    exit(-1);
}
#endif

void sms_assert(const char* exp, const char* file, unsigned int line) {
    //Show info
    fprintf(stderr, "\r\n\r\n");
    fprintf(stderr, "--- ASSERTION ERROR !!! ---\r\n");
    fprintf(stderr, "   [%s @%d] Assert failed: %s\r\n", file, line, exp);

    //Dump state
    FILE* f = fopen("CRASH_DUMP.sav", "wb");
    if (f) {
        fprintf(stderr, "   Dumping state to CRASH_DUMP.sav\r\n");
        ss_save(f, 0);
        fclose(f);
    }
    else {
        fprintf(stderr, "   Warning: Unable to create crash dump.\r\n");
    }
    //Some more info
    fprintf(stderr, "---------------------------\r\n");
    fprintf(stderr, "Please file a bug report with the crash dump file and the block above.\r\n");
    //Call inner assert
    platform_assert(exp, file, line);
}
