// FUNC_NAME: ActionHandler::processAction
void __thiscall ActionHandler::processAction(void* this, ActionData* actionData)
{
    // actionData->targetObject is a pointer at offset +8
    if (actionData->targetObject != 0) {
        // Stop the current action on the target object (offset +0x40 is some action handle)
        stopAction(*(int*)(actionData->targetObject + 0x40));
        
        int* typePtr = &actionData->type; // +4
        int param = 0;
        if (*typePtr == 1) {
            // Type 1: use player object from global game manager (offset +0x90)
            param = *(int*)(gGameManager + 0x90);
        }
        else if (*typePtr == 2) {
            // Type 2: use player vehicle from global game manager (offset +0x8c)
            param = *(int*)(gGameManager + 0x8c);
        }
        // Start a new action with the determined parameter
        startAction(*(int*)(this + 0x54), param);
    }
}