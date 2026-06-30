// FUNC_NAME: InputDeviceManager::updateDeviceStates
void __thiscall InputDeviceManager::updateDeviceStates() {
    // +0x78: dirty flag indicating the device list needs updating
    // +0x1c: head of intrusive linked list of Device objects (each has next at +0x1c)
    if (this->dirty != 0 && this->head != nullptr) {
        Device* current = this->head;
        // +0x7c: array of bool flags (one per device slot, sequential)
        char* flagPtr = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(this) + 0x7c);
        do {
            // FUN_00624ca0 likely sets the device's active state to match the flag
            FUN_00624ca0(*flagPtr != '\0');
            current = current->next; // next pointer at +0x1c
            ++flagPtr; // advance to next flag
        } while (current != nullptr);
    }
    this->dirty = 0; // clear dirty flag after processing
}