// FUNC_NAME: ActiveSlotManager::getActiveSlotData
undefined4 __thiscall ActiveSlotManager::getActiveSlotData(void *this) {
    int iVar1;
    
    // Check if any of the four slot pointers (+0x10, +0x14, +0x18, +0x1c) are non-null
    if ((*(int *)((char *)this + 0x10) != 0) || 
        (*(int *)((char *)this + 0x14) != 0) || 
        (*(int *)((char *)this + 0x18) != 0) || 
        (*(int *)((char *)this + 0x1c) != 0)) {
        // Find which slot is active; returns index >=0 on success, -1 otherwise
        iVar1 = FUN_006ea7b0((char *)this + 0x10);
        if (iVar1 >= 0) {
            // Return the corresponding entry from the array at +0x30
            return *(undefined4 *)(*(int *)((char *)this + 0x30) + iVar1 * 4);
        }
    }
    return 0;
}