// FUNC_NAME: Application::updateMainLoop

void __thiscall Application::updateMainLoop(int *this)
{
    int currentState;
    int frontendStateId;
    int gameStateId;
    int frontendResult;

    currentState = getCurrentState(*(int *)(g_stateManager + 4));
    frontendStateId = getStateIdFromString("FrontendMainLoop");
    gameStateId = getStateIdFromString("GameMainLoop");

    if (currentState == frontendStateId) {
        // Frontend main loop
        frontendResult = (**(code **)(*(int *)(g_frontendManager + 0x10) + 4))(); // vtable call
        updateFrontendAudio(); // FUN_005c3960
        processFrontendInput(frontendResult); // FUN_005c26d0
        *(byte *)(g_frontendManager + 0x3a3) = 0; // clear some flag
        (**(code **)(*g_renderer + 0x28))(); // renderer update
        (**(code **)(*this + 0xc))(); // this->vtable+0xc (likely update logic)
        endFrame(); // FUN_00993170
        return;
    }

    if (currentState == gameStateId) {
        // Game main loop
        (**(code **)(*g_gameManager + 0x28))(); // game manager update
    }

    endFrame(); // FUN_00993170
}