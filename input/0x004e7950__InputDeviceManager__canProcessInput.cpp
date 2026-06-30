// FUNC_NAME: InputDeviceManager::canProcessInput
uint __fastcall InputDeviceManager::canProcessInput(void* thisPtr)
{
    byte slotIndex;
    bool isPaused;
    int unknownObject;
    
    // Check if bit 0x40 (INPUT_FLAG_40) is set in state flags at +0x14
    if ((*(byte*)(*(int*)((char*)thisPtr + 0x24) + 0x14) & 0x40) != 0) {
        // Retrieve object pointer from thisPtr+4 then offset 0x20 (e.g., controller device)
        unknownObject = *(int*)(*(int*)((char*)thisPtr + 4) + 0x20);
        if (unknownObject != 0) {
            // Increment reference count at offset +4 of that object
            *(int*)(unknownObject + 4) = *(int*)(unknownObject + 4) + 1;
        }
        // Validate object via FUN_004e8550 (possibly getActiveDevice or similar)
        unknownObject = FUN_004e8550(unknownObject);
        if ((unknownObject != 0) && (isPaused = FUN_004e4230(), isPaused == false)) {
            // If validation succeeded but game is not paused, block input
            return 0;
        }
    }
    
    // Second condition: check bit 0x200 (INPUT_FLAG_200) and controller slot byte at +0x11
    if ((((*(uint*)(*(int*)((char*)thisPtr + 0x24) + 0x14) & 0x200) != 0) &&
         (slotIndex = *(byte*)(*(int*)((char*)thisPtr + 0x24) + 0x11), slotIndex != 0)) &&
        (DAT_011947e4 != 0) &&
        (((byte)DAT_011947e4 & slotIndex) == 0)) {
        // If slot is not enabled in the global mask, block input
        return 0;
    }
    return 1;
}