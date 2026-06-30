// FUNC_NAME: BaseManager::update
void __thiscall BaseManager::update(void) {
    void* pInnerObj = *(void**)((int)this + 4);        // +0x04: pointer to inner state object
    if (pInnerObj != NULL) {
        // Call virtual function at vtable+0x20 (e.g., update/preProcess)
        (*(void(__thiscall**)(void*))(*(int*)pInnerObj + 0x20))(pInnerObj);
        // Clear flag at offset 0x1F4 (500 decimal) in the inner object
        *(int*)((int)pInnerObj + 0x1F4) = 0;
        // If this inner object is the global singleton and has a pending task,
        // call the global cleanup function
        if ((g_pActiveManager == pInnerObj) && (*(int*)((int)pInnerObj + 0x1F0) != 0)) {
            FUN_006063b0();  // e.g., cleanupActiveManager()
        }
    }
}