// FUNC_NAME: triggerMoveUpAction
// Function address: 0x009236d0
// This function triggers the "MoveUp" action via the game's action system.

#include <cstddef>

// Forward declarations for callees (assumed engine functions)
void registerAction(const char* actionName, int param1, void* context, int param3);
void executeAction(void* actionData, int param);

// Global data references (assumed extern)
extern void* g_actionContext;        // DAT_00d87288
extern int    g_actionParameter;     // DAT_011302b0

void triggerMoveUpAction(void) {
    // Register the "MoveUp" action with a null context and a global object
    registerAction("MoveUp", 0, g_actionContext, 0);

    // Build the action data structure
    struct ActionData {
        int   parameter;  // +0x00
        int   reserved;   // +0x04
        char  flags;      // +0x08
    } actionData;

    actionData.parameter = g_actionParameter;
    actionData.reserved  = 0;
    actionData.flags     = 0;

    // Execute the action
    executeAction(&actionData, 0);
}