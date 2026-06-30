// FUNC_NAME: ActionDispatcher::dispatchAction

// Address: 0x006efe00
// Dispatches an action based on a type code stored in the action data structure.
// The action data structure (ActionData) is at least 4 integers long.
// Offset 0: actionType (int) - 0, 1, or 2
// Offset 4: arg1 (int) - first parameter for the action
// Offset 8: arg2 (int) - second parameter for the action
// Offset 12: arg3 (int or char) - third parameter, used as char in type 0

// The second parameter to this function (param_2) is passed along as an extra argument.

struct ActionData {
    int actionType;          // +0x00
    int arg1;                // +0x04
    int arg2;                // +0x08
    int arg3;                // +0x0C (used as char in type 0)
};

int __cdecl ActionDispatcher::dispatchAction(const ActionData* actionData, int extraParam)
{
    switch (actionData->actionType) {
    case 0:
        // type 0: calls a function with arg1, arg2, extraParam, and arg3 cast to char
        FUN_006eb980(actionData->arg1, actionData->arg2, extraParam, (char)actionData->arg3);
        break;
    case 1:
        // type 1: calls another function with arg1, arg2, extraParam, arg3
        FUN_006ebdd0(actionData->arg1, actionData->arg2, extraParam, actionData->arg3);
        break;
    case 2:
        // type 2: calls a third function with arg1, arg2, extraParam, arg3
        FUN_006eb800(actionData->arg1, actionData->arg2, extraParam, actionData->arg3);
        break;
    // default: no action
    }
    return 0;
}