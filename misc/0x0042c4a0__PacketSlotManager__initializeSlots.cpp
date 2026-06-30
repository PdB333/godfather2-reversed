// FUNC_NAME: PacketSlotManager::initializeSlots
void PacketSlotManager::initializeSlots()
{
    undefined4 *puVar1;
    undefined4 unaff_EBP; // Uninitialized register artifact (likely EBP)
    undefined4 *puVar2;
    int iVar3;

    puVar1 = this;
    if (g_useMemoryManager) { // DAT_01205358: global flag for memory manager
        iVar3 = 0;
        puVar2 = this + 10; // start of slot array? +0x28
        do {
            this = (undefined4 *)0x0; // Reset this pointer (temporary)
            // Call memory manager allocate (type 9) via vtable
            (**(code **)(*g_memoryManager + 0x1d8))(g_memoryManager, 9, &this);
            puVar2[-9] = unaff_EBP; // Set slot +0x00? Actually this[1] = unaff_EBP (artifact)
            unaff_EBP = 0;
            // Second allocation for slot?
            (**(code **)(*g_memoryManager + 0x1d8))(g_memoryManager, 9, &stack0xfffffff8);
            *puVar2 = this; // Slot's field at offset +0x28?
            puVar2[-5] = 0xe1001; // Slot field +0x14 (0xE1001 magic)
            puVar2[4] = 0xe1001;  // Slot field +0x38 (0xE1001 magic)
            // Zero out byte in slot array at +0x48 (index 0-3)
            *(undefined1 *)(iVar3 + 0x48 + (int)this) = 0;
            iVar3 = iVar3 + 1;
            puVar2 = puVar2 + 1;
        } while (iVar3 < 4);
        this[9] = 0; // this+0x24 = 0
        *this = 0;   // this+0x00 = 0
        return;
    }
    // Non-memory manager path: zero out specific fields
    this[1] = 0;  // +0x04
    this[10] = 0; // +0x28
    this[2] = 0;  // +0x08
    this[11] = 0; // +0x2C
    this[3] = 0;  // +0x0C
    this[12] = 0; // +0x30
    this[4] = 0;  // +0x10
    this[13] = 0; // +0x34
    this[9] = 0;  // +0x24
    *this = 0;    // +0x00
    return;
}