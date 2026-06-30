// FUNC_NAME: DebugConsole::processCommand
// Address: 0x0068f910
// Purpose: Processes a debug console command, handles color-coded formatting and output buffering.

#include <cstring>

// Global pointer to debug state (DAT_012233b4)
extern char* g_debugState;

// Table of command processor objects (PTR_FUN_00d5c878)
extern void* g_commandProcessorsTable;

// Forward declarations of helper functions
static int getConsoleContext(void* obj);          // FUN_0068f700
static void beginIterator();                      // FUN_00495960
static int hasNextIterator();                     // FUN_00495980
static void* getNextIterator();                    // FUN_004959c0
static int outputFormattedText(int cmdId, int clearFlag, void* buffer); // FUN_0068e3b0
static void freeStringBuffer(void** strPtr);      // FUN_004d3b50
static void printColoredString(const char* str);  // FUN_0068e0a0

// Structure for output buffer
struct OutputBuffer {
    char* data;
    int size;
};

// Known values from debug state: offset 0x568 is some flag
const int DEBUG_STATE_FLAG_OFFSET = 0x568;

// Constants for command type (local_2c == 4 => special close command)
const int CMD_TYPE_CLOSE = 4;

int DebugConsole::processCommand(int param_2, OutputBuffer* param_3)
{
    int* contextPtr;          // iVar3
    int flags;                // local_24
    int formatMode;           // local_28 (7 or 3)
    int commandType;          // local_2c
    void** processorArray;    // local_30 (points to g_commandProcessorsTable)
    char hasCustomFormat;     // local_20
    int reserved1;            // local_1c (unused)
    void* stringBuffer;       // local_18
    int reserved2;            // local_14 (unused)
    int reserved3;            // local_10 (unused)
    void (*freeFunc)(void*);  // local_c (callback to free stringBuffer)
    // Additional stack variables for colored output
    void* colorStringPtr;     // puStack_40
    void (*colorFreeFunc)(void*); // pcStack_34
    int colorFlag;            // iStack_3c

    // Get internal console context (pointer)
    contextPtr = (int*)getConsoleContext(this);
    if (contextPtr == 0) {
        return 0;
    }

    flags = *(int*)(contextPtr + 4);        // +0x04: flags field
    formatMode = 7;

    // Check if console is in "simple" mode (global flag or no active command)
    if ( (*(char*)(g_debugState + DEBUG_STATE_FLAG_OFFSET) == 0x12) ||
         (*(int*)(contextPtr + 0xc) == 0) ) {
        formatMode = 3;
    }

    commandType = 0;
    processorArray = &g_commandProcessorsTable;
    hasCustomFormat = 0;
    reserved1 = -1;
    stringBuffer = 0;
    reserved2 = 0;
    reserved3 = 0;
    freeFunc = 0;

    // Begin iteration over command processors
    beginIterator();
    while ( hasNextIterator() ) {
        void* processor = getNextIterator();
        // Each processor's vtable+0x14 is called with reference to the processor array
        (*(void (**)(void***))(*(int*)processor + 0x14))(&processorArray);
    }

    if (commandType != CMD_TYPE_CLOSE) {
        // Process normal command using context+0x08
        if ( outputFormattedText(*(int*)(contextPtr + 8), param_2, param_3) == 0 ) {
            if (hasCustomFormat == 0) {
                if (stringBuffer == 0) {
                    return 0;
                }
                freeFunc(stringBuffer);
                return 0;
            }
            // Custom format branch: possibly clear buffer and print colored text
            if (param_2 != 0) {
                memset(param_3->data, 0, param_3->size);
            }
            freeStringBuffer(&stringBuffer);
            if (colorStringPtr != 0) {
                colorFreeFunc(colorStringPtr);
            }
            if (colorFlag != 0) {
                printColoredString("[c=CUSTOM1]");
                freeStringBuffer(&stringBuffer);
                const char* str = (colorStringPtr != 0) ? (const char*)colorStringPtr : &g_debugState[0x46E]; // default empty string
                printColoredString(str);
                if (colorStringPtr != 0) {
                    colorFreeFunc(colorStringPtr);
                }
                printColoredString("[c=RESET]");
            }
        }
        if (stringBuffer != 0) {
            freeFunc(stringBuffer);
        }
        return 1;
    }
    else {
        // Command type is CMD_TYPE_CLOSE: process with context+0x0C
        int ret = outputFormattedText(*(int*)(contextPtr + 0xc), param_2, param_3);
        if (stringBuffer != 0) {
            freeFunc(stringBuffer);
        }
        return ret;
    }
}