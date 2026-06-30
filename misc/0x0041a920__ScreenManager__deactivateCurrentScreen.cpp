// FUNC_NAME: ScreenManager::deactivateCurrentScreen
void __thiscall ScreenManager::deactivateCurrentScreen(ScreenManager* this) {
    // Get the active screen pointer at this+0x4
    Screen* screen = *(Screen**)((char*)this + 4);
    // Call virtual function at vtable offset 0x20 (likely Screen::onHide or deactivate)
    screen->vtable->onHide();
    // Set screen's static flag to 0 indicating it is no longer active
    *(int*)((char*)screen + 0x274) = 0;
    // If this screen is the globally tracked active screen and has a pending transition flag,
    // invoke the global transition handler
    if (g_pCurrentScreen == screen && *(int*)((char*)screen + 0x270) != 0) {
        __globalScreenTransitionHandler();
    }
}