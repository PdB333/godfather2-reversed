// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __thiscall GodfatherGameManager::GodfatherGameManager(void *this) {
    // Call base class constructor (likely some EARS engine base)
    FUN_00bf0bc0(this);
    
    // Set vtable pointer (class-specific table)
    *(void **)this = &PTR_FUN_00e3a3e4;
    
    // Initialize flags field at offset 0x110 (0x44 * 4)
    int *flags = (int *)((char *)this + 0x110);
    *flags = 0;
    
    // Copy configuration data from global memory to object fields
    // Offsets 0xF0, 0xF4, 0xF8, 0xFC, 0x100, 0x104 (0x3c to 0x41 * 4)
    ((int *)this)[0x3c] = DAT_00e2e714;         // +0xF0
    ((int *)this)[0x3d] = DAT_00e39f98;         // +0xF4
    ((int *)this)[0x3e] = DAT_00e445f8;         // +0xF8
    ((int *)this)[0x3f] = DAT_00e2afb8;         // +0xFC
    ((int *)this)[0x40] = DAT_00e2afb8;         // +0x100 (duplicate)
    
    // Retrieve current system time via a virtual call (presumably into a timer service)
    // The object at this+0x18 (0x6 * 4) has a vtable; call function at its vtable+0x1c(offset 0x1c) with parameters
    int (*getTime)(void *param1, int param2, void *param3);
    getTime = (int (*)(void *, int, void *))(*(*(int **)((int *)this + 6)) + 0x1c);
    char buffer[12];  // Local buffer for time (maybe SYSTEMTIME or similar)
    int *stackTime = (int *)&buffer;
    getTime(&DAT_011397d0, 0, buffer); // DAT_011397d0 is likely a time source object
    ((int *)this)[0x41] = *stackTime;   // +0x104
    
    // Copy 4 consecutive ints from global data (maybe a default vector or quaternion)
    // Offsets 0xE0, 0xE4, 0xE8, 0xEC (0x38 to 0x3b * 4)
    ((int *)this)[0x38] = DAT_01126060;  // +0xE0
    ((int *)this)[0x39] = DAT_01126064;  // +0xE4
    ((int *)this)[0x3a] = DAT_01126068;  // +0xE8
    ((int *)this)[0x3b] = DAT_0112606c;  // +0xEC
    
    // Set field at offset 0x10C (0x43 * 4) to 2
    ((int *)this)[0x43] = 2;
    
    // OR flags with bit 2 (value 4)
    *flags |= 4;
    
    // Conditional bit manipulation: if bit 3 is set (0x8), set bit 4 (0x10); else clear bit 4
    if ((*flags & 8) != 0) {
        *flags |= 0x10;   // Set bit 4
    } else {
        *flags &= ~0x10;  // Clear bit 4
    }
    // Clear bit 3
    *flags &= ~8;
    
    // Initialize field at offset 0xD4 (0x35 * 4) to 0
    ((int *)this)[0x35] = 0;
    
    // Clear four consecutive fields at offsets 0x118, 0x11C, 0x120, 0x124 (0x46,0x47,0x48,0x49 * 4)
    ((int *)this)[0x46] = 0;
    ((int *)this)[0x47] = 0;
    ((int *)this)[0x48] = 0;
    ((int *)this)[0x49] = 0;
    
    // Set field at offset 0x114 (0x45 * 4) to 5
    ((int *)this)[0x45] = 5;
}