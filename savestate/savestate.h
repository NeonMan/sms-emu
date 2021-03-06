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

/**
 *  @file save-state.h
 *  @brief Save state function declarations
 */
#ifndef __SAVE_STATE_H
#define __SAVE_STATE_H

#include <stdint.h>
#include <stdio.h>

#define SAVESTATE_VERSION "DEVEL"

#define SAVESTATE_LINE_BUFFER 256

#ifdef __cplusplus
extern "C" {
#endif

    int ss_save(FILE* f, const char* rom_name);
    int ss_restore(FILE* f);

#ifdef __cplusplus
}
#endif

#endif
