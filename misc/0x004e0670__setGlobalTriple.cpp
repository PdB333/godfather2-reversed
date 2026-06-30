// FUNC_NAME: setGlobalTriple
// Address: 0x004e0670
// Stores three parameters into global variables.

#include <cstdint>

extern uint32_t DAT_012054cc;
extern uint32_t DAT_012054d0;
extern uint32_t DAT_012054d4;

void setGlobalTriple(uint32_t param1, uint32_t param2, uint32_t param3)
{
    DAT_012054cc = param1;
    DAT_012054d0 = param2;
    DAT_012054d4 = param3;
}