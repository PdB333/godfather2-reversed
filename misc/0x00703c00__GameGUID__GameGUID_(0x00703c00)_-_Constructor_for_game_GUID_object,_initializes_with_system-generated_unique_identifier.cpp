// FUNC_NAME: GameGUID::GameGUID (0x00703c00) - Constructor for game GUID object, initializes with system-generated unique identifier
// Base init call likely sets up base class (e.g., NetGUID base) with parameter param2
void __thiscall GameGUID::GameGUID(void* thisPtr, unsigned int param2)
{
    // +0x00: vtable for main class (PTR_FUN_00d60fdc)
    // +0x3C: vtable for base class 1 (PTR_LAB_00d60fcc)
    // +0x48: vtable for base class 2 (PTR_LAB_00d60fc8)
    // +0x50: vtable for base class 3 (PTR_LAB_00d60fc4)
    // +0x54: GUID data (16 bytes, 4 dwords)
    // +0x68-0x77: Additional zero-initialized fields (2 dwords + 4 shorts)

    // Initialize base with param2 (likely a family or network session ID)
    guidBaseInit(param2);

    // Set up vtable pointers (some overwritten to final values)
    *(void**)((char*)thisPtr + 0x50) = (void*)&PTR_LAB_00e32854; // temporary vtable
    *(void**)thisPtr = (void*)&PTR_FUN_00d60fdc;                 // main vtable
    *(void**)((char*)thisPtr + 0x3C) = (void*)&PTR_LAB_00d60fcc; // base1 vtable
    *(void**)((char*)thisPtr + 0x48) = (void*)&PTR_LAB_00d60fc8; // base2 vtable
    *(void**)((char*)thisPtr + 0x50) = (void*)&PTR_LAB_00d60fc4; // final base3 vtable

    // Placeholder GUID (will be replaced by system-generated GUID)
    *(unsigned int*)((char*)thisPtr + 0x54) = 0xbadbadba;
    *(unsigned int*)((char*)thisPtr + 0x58) = 0xbeefbeef;
    *(unsigned int*)((char*)thisPtr + 0x5C) = 0xeac15a55;
    *(unsigned int*)((char*)thisPtr + 0x60) = 0x91100911;

    // Zero-initialize remaining fields
    *(unsigned int*)((char*)thisPtr + 0x68) = 0;
    *(unsigned short*)((char*)thisPtr + 0x6C) = 0;
    *(unsigned short*)((char*)thisPtr + 0x6E) = 0;
    *(unsigned int*)((char*)thisPtr + 0x70) = 0;
    *(unsigned short*)((char*)thisPtr + 0x74) = 0;
    *(unsigned short*)((char*)thisPtr + 0x76) = 0;

    // Generate a unique 128-bit GUID from the system and overwrite placeholder
    unsigned int* sysGUID = generateSystemGUID();
    *(unsigned int*)((char*)thisPtr + 0x54) = sysGUID[0];
    *(unsigned int*)((char*)thisPtr + 0x58) = sysGUID[1];
    *(unsigned int*)((char*)thisPtr + 0x5C) = sysGUID[2];
    *(unsigned int*)((char*)thisPtr + 0x60) = sysGUID[3];
}