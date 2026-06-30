// FUNC_NAME: ActionController::processActionEvent
void __thiscall ActionController::processActionEvent(ActionController* this, int eventType)
{
    int* actionEntry;
    char actionResult;
    int* defaultAction;
    typedef void (__thiscall *ActionCallback)(int, int, int);
    ActionCallback callback;
    int callbackArg;

    actionEntry = nullptr; // local_14[0] initially 0

    if (*(int*)((char*)this + 0x28) != 0xff) {
        // retrieve action entry from index at this+0x28
        actionEntry = (int*)getActionFromIndex(*(int*)((char*)this + 0x28));
    }

    if (eventType == 2) {
        if (actionEntry == nullptr) {
            return;
        }
        // Check action type: 0 or 0x48 (72) are valid for processing
        if (actionEntry[1] == 0 || actionEntry[1] == 0x48) {
            // If this has a callback, call it with eventType=0 (likely start/continue)
            if (*(int*)((char*)this + 0x14) != 0) {
                callback = *(ActionCallback*)(*(int*)((char*)this + 0x14));
                if (callback != nullptr) {
                    callbackArg = *(int*)((char*)this + 0x18);
                    callback(0, 0, callbackArg); // eventType 0? maybe a different meaning
                    goto LAB_006f75e4;
                }
            }
            goto LAB_006f75b9;
        }

        // Copy action's callback and arg from actionEntry to this
        if ((int*)((char*)this + 0x14) != (int*)((char*)actionEntry + 0x14)) {
            *(int*)((char*)this + 0x14) = *(int*)((char*)actionEntry + 0x14);
            *(int*)((char*)this + 0x18) = *(int*)((char*)actionEntry + 0x18);
        }

        // Attempt to execute the action
        actionResult = executeAction((int)(actionEntry + 1), *(int*)((char*)actionEntry + 0xc),
                                     *(int*)((char*)actionEntry + 0x10),
                                     *(int*)((char*)actionEntry + 0x24),
                                     *(char*)((char*)actionEntry + 0x28), 1);
        if (actionResult != 0) {
            *(int*)((char*)this + 0x2c) = 2;
            goto LAB_006f75e4;
        }

        // If current callback pointer is non-null (maybe an active callback?), cancel it
        if (*(int*)((char*)this + 0x14) != 0) {
            cancelAction(0, 0);
        }

        defaultAction = (int*)getDefaultAction(0, 0);
        if ((int*)((char*)this + 0x14) != defaultAction) {
            *(int*)((char*)this + 0x14) = *defaultAction;
            *(int*)((char*)this + 0x18) = defaultAction[1];
        }
    }
    else {
        if (eventType != 4 && eventType != 3) {
            return;
        }

        // For eventType 3 or 4, call callback with event type (4? seems like 4 is used)
        if (*(int*)((char*)this + 0x14) != 0) {
            callback = *(ActionCallback*)(*(int*)((char*)this + 0x14));
            if (callback != nullptr) {
                callbackArg = *(int*)((char*)this + 0x18);
                callback(0, 4, callbackArg); // 4 presumably means stop/cancel
            }
        }
LAB_006f75b9:
        defaultAction = (int*)getDefaultAction(0, 0);
        if ((int*)((char*)this + 0x14) != defaultAction) {
            *(int*)((char*)this + 0x14) = *defaultAction;
            *(int*)((char*)this + 0x18) = defaultAction[1];
        }
    }

    resetActionState(); // likely resets internal state
    *(int*)((char*)this + 0x2c) = 0;

LAB_006f75e4:
    if (*(int*)((char*)this + 0x28) != 0xff) {
        releaseActionIndex(*(int*)((char*)this + 0x28));
        *(int*)((char*)this + 0x28) = 0xff;
    }
    return;
}