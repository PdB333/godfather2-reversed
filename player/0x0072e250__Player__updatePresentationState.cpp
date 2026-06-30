// FUNC_NAME: Player::updatePresentationState
void __fastcall Player::updatePresentationState(Player* thisPtr)
{
    char bReady;
    char localBuffer[16]; // buffer for temporary object
    char localFlag;
    void** vtablePtr;

    bReady = GameState::isReady(); // FUN_007f4800
    if (bReady) {
        thisPtr->resetTimers(); // FUN_0072de20
        localFlag = 1; // set flag
        vtablePtr = (void**)&PTR_LAB_00e51890; // vtable for some temporary object
        ConstructLocal(localBuffer); // FUN_0081dab0, placement new or copy
        ProcessReadyState(); // FUN_0072c130
    }
}