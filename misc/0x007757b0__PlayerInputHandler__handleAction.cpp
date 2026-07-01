// FUNC_NAME: PlayerInputHandler::handleAction
void __thiscall PlayerInputHandler::handleAction(PlayerInputHandler* this, int actionId) {
    // +0x48: pointer to some component (e.g., state machine or action provider)
    // +0x5c: current action state (0 = inactive, 0x48 = invalid/sentinel)
    // *piVar2: vtable pointer of the component (derived from pointer at +0x48 minus 0x48)
    int* componentPtr = this->field_0x48;
    int* componentBase;
    if (componentPtr == 0) {
        componentBase = 0;
    } else {
        componentBase = (int*)(componentPtr - 0x48);
    }

    bool actionValid = true;
    if (this->field_0x5c != 0 && this->field_0x5c != 0x48) {
        actionValid = FUN_00724c40(actionId) != 0; // check if action can be performed
    }

    if (actionValid) {
        // Begin/process action with parameters (4,1) - likely "start/activate"
        (*(void (__thiscall**)(int, int, int))(*componentBase + 0x234))(4, 1);
    } else {
        // End/cancel action with parameters (0,1) - likely "stop/deactivate"
        (*(void (__thiscall**)(int, int, int))(*componentBase + 0x234))(0, 1);
    }
}