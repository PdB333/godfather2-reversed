// FUNC_NAME: ActiveSlotManager::deactivateFirstActiveSlot

void __fastcall ActiveSlotManager::deactivateFirstActiveSlot(void* thisPtr) {
    uint32_t slotIndex = 0;
    // +0x78: start of array of 30 slots, each 0x38 bytes. First byte is active flag.
    char* slotStart = reinterpret_cast<char*>(thisPtr) + 0x78;
    do {
        if (*slotStart != '\0') {
            // Clear the first active slot's flag to mark it inactive.
            *reinterpret_cast<char*>(reinterpret_cast<uint8_t*>(thisPtr) + slotIndex * 0x38 + 0x78) = '\0';
            return;
        }
        slotIndex++;
        slotStart += 0x38;
    } while (slotIndex < 30);
}