// FUNC_NAME: Player::updateCommandInput
void __thiscall Player::updateCommandInput(int *this, undefined4 *inputCmd, undefined4 timeDelta) {
    int component;
    char isActive;
    undefined4 localStruct[4];
    undefined localBuffer[28];

    FUN_00470b80(inputCmd, timeDelta); // likely copyInput or preprocess
    component = this[0xba]; // +0x2E8 m_pComponent or similar
    isActive = (*(code **)(*this + 0x19c))(); // vtable +0x19c, e.g. isActive()
    if (isActive == '\0') {
        if (component != 0) {
            localStruct[0] = *inputCmd;
            localStruct[1] = inputCmd[1];
            localStruct[2] = inputCmd[2];
            localStruct[3] = DAT_00e2b1a4; // some global constant or state
            FUN_00aa36a0(localStruct, timeDelta); // e.g., applyCommandEffect
            FUN_009f4c70(localBuffer); // e.g., processBuffer
        }
    } else {
        FUN_0055db00(timeDelta); // e.g., handleActiveState
    }
    (*(code **)(*this + 600))(); // vtable +0x258, e.g., postUpdate
    return;
}