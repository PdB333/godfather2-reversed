// FUNC_NAME: Container::clear
void __fastcall Container::clear(int thisPtr)
{
    uint32_t i;
    
    // Save current size to global debug context at offset 0xEC
    *(int*)(DAT_01130044 + 0xEC) = *(int*)(thisPtr + 0x50); // +0x50: m_size
    
    // Debug log "ClearList"
    FUN_005a04a0("ClearList", 0, &DAT_00d8510c, 0);
    
    i = 0;
    if (*(int*)(thisPtr + 0x50) != 0) {
        do {
            // Release each element (destructor/cleanup)
            FUN_009c8eb0(*(int*)(*(int*)(thisPtr + 0x4C) + i * 4)); // +0x4C: m_items
            i++;
        } while (i < *(uint*)(thisPtr + 0x50));
    }
    
    // Reset size
    *(int*)(thisPtr + 0x50) = 0;
    
    // Free the items array memory
    FUN_009c8f10(*(int*)(thisPtr + 0x4C)); // m_items
    
    // Nullify pointers
    *(int*)(thisPtr + 0x4C) = 0; // m_items = nullptr
    *(int*)(thisPtr + 0x54) = 0; // +0x54: m_capacity or m_flag
}