// FUNC_NAME: SystemInitializer::setupCallbacks
// Function address: 0x005f2da0
// Purpose: Initializes a function pointer table and registers a system with the engine.
// Called from main initialization sequence.

#include <cstdint>

// Global function pointer table (likely dispatch/vtable for a subsystem)
extern void (*g_systemFunctionTable[4])(void); // located at 0x011a0f14

// Prototypes for the handler functions
extern void handlerFunction0(void);  // 0x005f26f0
extern void handlerFunction1(void);  // 0x005f2830
extern void handlerFunction2(void);  // 0x005f29e0
extern void handlerFunction3(void);  // 0x005f2b40

// Function to register a system with its data block
extern void registerSystem(void* systemData); // 0x005dbc10

// Static data block for the system (size unknown)
extern uint8_t g_systemData[]; // at 0x00e3f4d0

bool setupSystemFunctionTable(void)
{
    // Assign function pointers to the global table
    g_systemFunctionTable[0] = handlerFunction0; // +0x00
    g_systemFunctionTable[1] = handlerFunction1; // +0x04
    g_systemFunctionTable[2] = handlerFunction2; // +0x08
    g_systemFunctionTable[3] = handlerFunction3; // +0x0C

    // Register the system with the engine, passing its static data block
    registerSystem(&g_systemData);

    return true; // success
}