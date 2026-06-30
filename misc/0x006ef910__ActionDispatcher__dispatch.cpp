// FUNC_NAME: ActionDispatcher::dispatch
// Function address: 0x006ef910
// Role: Dispatches different actions based on type stored in first field of actionData struct.
// The actionData pointer points to a struct with fields: type, arg1, arg2, arg3 (all ints).
// The second parameter (context) is passed to the handler functions.
// Handlers: FUN_006eb840, FUN_006eb850, FUN_006eb860 (see their addresses).

struct ActionData {
    int type;    // +0x00
    int arg1;    // +0x04
    int arg2;    // +0x08
    int arg3;    // +0x0C
};

int __thiscall ActionDispatcher::dispatch(ActionData* actionData, int context) {
    int actionType = actionData->type;

    if (actionType == 0) {
        // Action type 0: calls handler with char cast on arg3
        FUN_006eb840(actionData->arg1, actionData->arg2, context, (char)actionData->arg3);
    }
    else if (actionType == 1) {
        // Action type 1: calls handler with full arg3
        FUN_006eb850(actionData->arg1, actionData->arg2, context, actionData->arg3);
    }
    else if (actionType == 2) {
        // Action type 2: calls handler with full arg3
        FUN_006eb860(actionData->arg1, actionData->arg2, context, actionData->arg3);
    }
    // Other types (if any) are ignored.
    return 0;
}