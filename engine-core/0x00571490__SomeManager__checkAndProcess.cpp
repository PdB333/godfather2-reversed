// FUNC_NAME: SomeManager::checkAndProcess
uint __thiscall SomeManager::checkAndProcess(int handle) {
    // handle must be non-zero and this pointer must not be the sentinel value -1
    if (handle != 0 && this != (SomeManager*)-1) {
        FUN_00586970();   // performs some initialization or update
        return FUN_005787f0(); // retrieves and returns a result
    }
    // On invalid input, return an error code that clears the low byte of whatever was in EAX (here we assume -256)
    return 0xFFFFFF00;
}