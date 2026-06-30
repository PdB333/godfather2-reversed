// FUNC_NAME: StringTable::initialize

#include <cstdint>

// Global engine object (vtable pointer at offset 0)
extern void* g_engineObject; // 0x01205750

// Error handler function (takes int parameter)
extern void (*g_errorHandler)(int); // PTR_FUN_00f15a3c

// String table array (26 entries, starting at 0x01164010)
extern const char* g_stringTable[26];

// Method at vtable offset 0x158 (index 86): registers a string and returns status
typedef int (__thiscall *RegisterStringFunc)(void* self, const char* str);
static RegisterStringFunc s_registerString = nullptr;

// Alternative method for last entry (takes extra output pointer)
typedef int (__thiscall *RegisterStringExFunc)(void* self, const char* str, const char** outPtr);
static RegisterStringExFunc s_registerStringEx = nullptr;

void StringTable::initialize() {
    // Initialize function pointers from vtable
    void** vtable = *(void***)g_engineObject;
    s_registerString = (RegisterStringFunc)vtable[86];
    s_registerStringEx = (RegisterStringExFunc)vtable[86]; // Same offset, different signature

    const char* str;
    int result;

    // Entry 0
    str = (const char*)0x011286c8;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[0] = str;

    // Entry 1
    str = (const char*)0x01128700;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[1] = str;

    // Entry 2
    str = (const char*)0x01128738;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[2] = str;

    // Entry 3
    str = (const char*)0x01128768;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[3] = str;

    // Entry 6 (skipping indices 4,5)
    str = (const char*)0x01128798;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[6] = str;

    // Entry 7
    str = (const char*)0x011287c8;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[7] = str;

    // Entry 8
    str = (const char*)0x011287f8;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[8] = str;

    // Entry 9
    str = (const char*)0x01128820;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[9] = str;

    // Entry 10
    str = (const char*)0x01128848;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[10] = str;

    // Entry 11
    str = (const char*)0x01128868;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[11] = str;

    // Entry 12 (zero)
    g_stringTable[12] = 0;

    // Entry 13
    str = (const char*)0x01128888;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[13] = str;

    // Entry 14 (zero)
    g_stringTable[14] = 0;

    // Entry 15
    str = (const char*)0x011288a8;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[15] = str;

    // Entry 16 (zero)
    g_stringTable[16] = 0;

    // Entry 17
    str = (const char*)0x011288c0;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[17] = str;

    // Entry 18
    str = (const char*)0x011288e0;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[18] = str;

    // Entry 19
    str = (const char*)0x011288f8;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[19] = str;

    // Entry 20
    str = (const char*)0x01128910;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[20] = str;

    // Entry 21
    str = (const char*)0x01128930;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[21] = str;

    // Entry 4 (delayed)
    str = (const char*)0x01128940;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[4] = str;

    // Entry 5 (delayed)
    str = (const char*)0x01128968;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[5] = str;

    // Entry 22
    str = (const char*)0x01128990;
    result = s_registerString(g_engineObject, str);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[22] = str;

    // Entry 23 (special: uses RegisterStringEx with output pointer)
    const char* outPtr = nullptr;
    str = (const char*)0x011289b0;
    result = s_registerStringEx(g_engineObject, str, &outPtr);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[23] = str;

    // Entry 24 (zero)
    g_stringTable[24] = 0;

    // Entry 25 (last, also uses RegisterStringEx)
    str = (const char*)0x011289d0;
    result = s_registerStringEx(g_engineObject, str, &outPtr);
    if (result == -0x7789fe84) g_errorHandler(2);
    g_stringTable[25] = str;
}