// FUNC_NAME: SystemManager::resetState
void __fastcall SystemManager::resetState() {
    // Clear the initialized flag at offset 0x61
    *(byte*)(this + 0x61) = 0;

    // Register a callback function (LAB_00842ec0) with the system
    registerCallback(&callbackFunction); // FUN_004464d0
}