// FUNC_NAME: NetworkManager::initSlotArrays

void __fastcall NetworkManager::initSlotArrays(NetworkManager* this)
{
    // g_slotDefaultValue is a global constant (likely -1 or 0xFFFFFFFF) from _DAT_00d5780c
    extern int g_slotDefaultValue;

    // Initialize 26 slot blocks, each 48 bytes (12 ints), starting at offset 0x100.
    // Each block has a sentinel at offset +0x0C within the block.
    int* slotBase = (int*)((char*)this + 0x100);
    for (int i = 0; i < 26; i++)
    {
        // First group of 4 ints: bytes 0x00-0x0F of the slot
        slotBase[0] = 0;   // +0x00
        slotBase[1] = 0;   // +0x04
        slotBase[2] = 0;   // +0x08
        slotBase[3] = g_slotDefaultValue; // +0x0C sentinel

        // Second group of 4 ints: bytes 0x10-0x1F
        slotBase[4] = 0;   // +0x10
        slotBase[5] = 0;   // +0x14
        slotBase[6] = 0;   // +0x18
        slotBase[7] = 0;   // +0x1C

        // Third group of 4 ints: bytes 0x20-0x2F
        slotBase[8] = 0;   // +0x20
        slotBase[9] = 0;   // +0x24
        slotBase[10] = 0;  // +0x28
        slotBase[11] = 0;  // +0x2C

        slotBase += 12;    // Move to next slot (48 bytes forward)
    }

    // Initialize member at offset 0x28 (e.g., a counter or state flag)
    *(int*)((char*)this + 0x28) = 0;

    // Initialize 8 consecutive ints starting at offset 0xD4 (0xD4..0xF0)
    int* fieldD4 = (int*)((char*)this + 0xD4);
    for (int j = 0; j < 8; j++)
    {
        fieldD4[j] = 0;
    }

    // Additional setup (likely another init or virtual function call)
    FUN_007ef4d0();
}