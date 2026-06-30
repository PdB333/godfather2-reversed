// FUNC_NAME: InputManager::pumpInputBuffer
void __thiscall InputManager::pumpInputBuffer(InputManager* this) {
    int prevInputCode = *(int*)((char*)this + 4); // +0x4: current input buffer state (e.g., pending key code)
    if (prevInputCode != 0) {
        do {
            // Process a predefined sequence of debug/utility key codes:
            //  0x20 = Space, 9 = Tab, 0xD = Enter, 10 = Line Feed
            processKey(0x20);
            processKey(9);
            processKey(0xD);
            processKey(10);
            bool changed = prevInputCode != *(int*)((char*)this + 4);
            prevInputCode = *(int*)((char*)this + 4);
        } while (changed);
    }
}