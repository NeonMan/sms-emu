#Savestate load/save
project(test_savestate)

add_executable (zzz_test_savestate test_savestate.c)
target_link_libraries (zzz_test_savestate unity savestate smsram smsrom smsio peripheral psg z80 glue sms_debug vdp)
add_test(test_savestate zzz_test_savestate)

add_executable (zzz_test_savestate_rom test_savestate_rom.c)
target_link_libraries (zzz_test_savestate_rom unity savestate smsram smsrom smsio peripheral psg z80 glue sms_debug vdp)
add_test(test_savestate_rom zzz_test_savestate_rom)
