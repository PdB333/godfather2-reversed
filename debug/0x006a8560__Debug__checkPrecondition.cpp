// FUNC_NAME: Debug::checkPrecondition
#include <cstdint>

// Global data references (from .data section)
extern uint32_t g_debugFlag1;            // DAT_00e50ca4
extern uint32_t g_debugFlag2;            // DAT_00e50ca0
extern uint32_t g_someGlobalValue;       // _DAT_00d5780c
extern void* g_functionTablePointer;     // PTR_FUN_00e32a8c

// Forward declarations of called functions
void debugLog(uint32_t param1, uint32_t param2, uint32_t flag1, uint32_t flag2, int zero1, int zero2);   // FUN_00542650
void initBuffer(uint8_t* buffer, void** tablePointer);                                                      // FUN_009e5ed0

bool Debug::checkPrecondition(uint32_t param1, uint32_t param2)
{
    uint8_t localBuffer[32];             // local_60
    uint32_t localCC = g_someGlobalValue; // local_cc
    uint32_t localB0 = g_someGlobalValue; // local_b0
    uint32_t localAC = 0xFFFFFFFF;       // local_ac
    uint32_t localA0 = 0xFFFFFFFF;       // local_a0
    uint8_t unknownFlag = 1;             // local_40 (unused flag)
    void** tablePtrAddr = (void**)&g_functionTablePointer; // local_d0
    int32_t returnFlag = 0;              // local_70 (never modified, always 0)
    uint32_t local80 = 0;                // local_80

    debugLog(param1, param2, g_debugFlag1, g_debugFlag2, 0, 0);
    initBuffer(localBuffer, tablePtrAddr);
    return returnFlag != 0; // always false because returnFlag remains 0
}