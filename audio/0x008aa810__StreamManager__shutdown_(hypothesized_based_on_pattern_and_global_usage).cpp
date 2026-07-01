// FUNC_NAME: StreamManager::shutdown (hypothesized based on pattern and global usage)
void StreamManager::shutdown() {
    // Check if initialized (flag at +0xD8)
    if (!_isInitialized) // *(_int *)(this + 0xD8) != 0
        return;

    // If the primary stream pointer is non-null
    if (_primaryStream) { // *(_int *)(this + 0x60)
        // Reset global singleton state (DAT_0112a838 is likely g_someManager)
        g_someManager->someField = 0;             // *(undefined4 *)(DAT_0112a838 + 100)
        g_someManager->anotherField = -1;         // *(undefined4 *)(DAT_0112a838 + 0x68)

        // Call release on the stream object (vtable call with arg 1)
        _primaryStream->release(1); // (**(code **)(*(_DWORD **)(this+0x60))[0])(1)
        _primaryStream = nullptr;
    }

    // Release secondary pointer
    if (_secondaryStream) { // *(_int *)(this + 0xDC)
        _secondaryStream->release(1);
        _secondaryStream = nullptr;
    }

    // Destroy global static objects (likely managers or resources)
    destroyGlobalObject(&DAT_01218068);
    destroyGlobalObject(&DAT_0112edf4);
    destroyGlobalObject(&DAT_0112ef7c);
    destroyGlobalObject(&DAT_012069c4);
    destroyGlobalObject(&DAT_0112ecfc);

    // Subsystem cleanup
    cleanupSubsystem(); // FUN_008afc00(this)

    // Finalize a handle/string associated with this
    // (uStack_c/uStack_8/uStack_4 is a temporary constructed from +0xB8)
    MyHandleType tempHandle = _someHandle; // *(undefined4 *)(param_1 + 0xb8)
    tempHandle.zero = 0;
    tempHandle.someByte = 0;
    finalizeHandle(&tempHandle, 0); // FUN_00408a00(&tempHandle, 0)

    // Mark as uninitialized
    _isInitialized = false; // *(undefined4 *)(param_1 + 0xd8) = 0
}