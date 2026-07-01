// FUNC_NAME: SomeManager::releaseAllSlots
void __thiscall SomeManager::releaseAllSlots() {
    int** slotArray = reinterpret_cast<int**>(this + 0x148); // array of 8 pointers (e.g., slots, streams, controllers)
    for (int i = 0; i < 8; ++i) {
        if (slotArray[i] != nullptr) {
            releaseObject(slotArray[i]); // FUN_009f01a0 - releases the object (likely a member function taking this in ECX)
            slotArray[i] = nullptr;
        }
    }
    *reinterpret_cast<int*>(this + 0x124) = 0; // reset count or flag (e.g., active slot count)
}