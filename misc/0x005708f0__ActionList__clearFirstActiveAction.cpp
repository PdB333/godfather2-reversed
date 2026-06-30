// FUNC_NAME: ActionList::clearFirstActiveAction
void __fastcall clearFirstActiveAction(void* /* unused */, ActionList* actionList) {
    int count = actionList->count; // +0x2c
    if (count <= 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        Action* action = actionList->actions[i]; // +0x30, array of pointers
        uint8_t type = action->type & 0xFF; // +0x4

        if (type < 10) {
            // Low-priority action: clear pointer at +0x24
            if (action->lowPriorityAction == nullptr) { // +0x24
                return;
            }
            action->lowPriorityAction = nullptr;
        } else {
            // High-priority action: clear pointer at +0x2c
            if (action->highPriorityAction == nullptr) { // +0x2c
                return;
            }
            action->highPriorityAction = nullptr;
        }
    }
}