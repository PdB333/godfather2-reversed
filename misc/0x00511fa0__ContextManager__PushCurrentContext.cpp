// FUNC_NAME: ContextManager::PushCurrentContext

#include <cstdint>

// Forward declaration for the called function (converts a value to an identifier)
extern uint32_t __stdcall FUN_0060d740(uint32_t value);

// Structure representing a context object (vtable at +0x00, data at +0x04, +0x08, +0x0C)
// The global instance at 0x0121a380 controls the current game state.
struct AppContext {
    void** vtable;          // +0x00 pointer to virtual method table
    void* previousContext;  // +0x04 saved previous stack pointer (DAT_012058ec)
    uint32_t someId;        // +0x08 result from FUN_0060d740
    int32_t index;          // +0x0C stack index (from DAT_012058f8)
};

// Global singleton context instance (address 0x0121a380)
static AppContext g_appContext;

// External globals used for context stack management
extern AppContext* g_pContextStackTop;  // DAT_012058ec – points to the current top of stack
extern int32_t g_contextStackCounter;   // DAT_012058f8 – number of pushes performed

// -----------------------------------------------------------------------------
// Pushes the global context onto the application's context stack.
// - Calls two virtual methods on the context (initialization/transition steps).
// - Links the previous stack top into the context's back-reference.
// - Updates the stack top to point to the context, and records the stack index.
// -----------------------------------------------------------------------------
void ContextManager::PushCurrentContext(void)
{
    // Call the second virtual method (vtable offset 0x04) – e.g., "GetIdentifier"
    uint32_t retVal = (*(uint32_t (__thiscall **)(AppContext*))(*g_appContext.vtable + 4))(&g_appContext);

    // Convert the returned value to an internal ID and store it in the context
    g_appContext.someId = FUN_0060d740(retVal);

    // Call the fifth virtual method (vtable offset 0x10) – e.g., "OnPushed"
    (*(void (__thiscall **)(AppContext*))(*g_appContext.vtable + 0x10))(&g_appContext);

    // Save the previous stack top as the context's back-link
    g_appContext.previousContext = (void*)g_pContextStackTop;

    // Increment the global push counter
    g_contextStackCounter++;

    // Make the stack top point to this context (the top is now &g_appContext)
    g_pContextStackTop = &g_appContext;

    // Store the new counter value into the context
    g_appContext.index = g_contextStackCounter;
}