// FUNC_NAME: FrontendStateMachine::enterFrontendMainLoop

void __thiscall FrontendStateMachine::enterFrontendMainLoop(FrontendStateMachine *this)
{
    int vtable = *(int *)this; // vtable pointer
    // Virtual function at vtable+0x14 - likely onEnter or startMainLoop
    void (*mainLoopFunc)(void *) = (void (*)(void *))(*(int *)(vtable + 0x14));
    void *param = FUN_00683280("FrontendMainLoop"); // returns some context or resource ID
    mainLoopFunc(param); // enter the main loop state

    this->field_0xA = 1; // +0xA: mark main loop active
    if (g_pFrontendManager != NULL) {
        FUN_00983190(); // cleanup or finalize previous state
        g_pFrontendManager->field_0x90 = 0; // +0x90: clear a flag
    }
    this->field_0x9 = 1; // +0x9: mark as initialized or ready
}