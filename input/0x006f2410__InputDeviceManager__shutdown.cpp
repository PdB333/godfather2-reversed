// FUNC_NAME: InputDeviceManager::shutdown
void InputDeviceManager::shutdown() {
    // Clear flags: bits 0,2,3 are cleared (0xF2 = 0b11110010)
    *(byte *)(this + 0x8c) = *(byte *)(this + 0x8c) & 0xf2;
    *(byte *)(this + 0x8d) = 0;
    *(int *)(this + 0x78) = 0;

    // Release global input device singleton reference
    releaseGlobalInputDevice(&g_inputDeviceSingleton);

    // Clear bit 1 in flags (0xFD = 0b11111101)
    *(byte *)(this + 0x8c) = *(byte *)(this + 0x8c) & 0xfd;

    // Free two dynamically allocated pointer members
    if (*(int *)(this + 0x7c) != 0) {
        deallocateMemory((undefined4 *)(this + 0x7c));
        *(int *)(this + 0x7c) = 0;
    }
    if (*(int *)(this + 0x84) != 0) {
        deallocateMemory((undefined4 *)(this + 0x84));
        *(int *)(this + 0x84) = 0;
    }
}