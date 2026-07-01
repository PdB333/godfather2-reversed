// FUNC_NAME: EventManager::invokeCallbacks
void __thiscall EventManager::invokeCallbacks(int thisPtr) {
    uint i = 0;
    if (*(int *)(thisPtr + 0xdc) != 0) { // count of callbacks at +0xDC
        do {
            // call each function pointer stored at array offset +0xD8
            (**(code **)(*(int *)(thisPtr + 0xd8) + i * 4))();
            i = i + 1;
        } while (i < *(uint *)(thisPtr + 0xdc));
    }
    return;
}