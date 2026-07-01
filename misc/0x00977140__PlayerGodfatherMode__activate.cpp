// FUNC_NAME: PlayerGodfatherMode::activate
void __thiscall PlayerGodfatherMode::activate(char param2) // param2 = 0 to release resources, 1 to keep
{
    uint* allocatorPtr;

    // Check if bit 13 (0x2000) is set in flags at this+0x60
    if ((*(uint*)(this + 0x60) >> 0xd & 1) != 0)
    {
        // Clear the bit
        *(uint*)(this + 0x60) &= 0xffffdfff;

        // Call memory manager function with -9 (0xfffffff7)
        MemoryManager::release(0xfffffff7);

        // Allocate a small block on a custom stack-like arena
        allocatorPtr = (uint*)(gArenaBase + 0x14);
        // Set vtable pointer to a new one
        *(undefined4**)(gArenaBase + 0x14) = &sNewVtable;
        // Increment pointer by 4
        *allocatorPtr += 4;
        // Write a null terminator (possibly for a string)
        *(undefined1*)*allocatorPtr = 0;
        // Align to 4 bytes
        *allocatorPtr = (*allocatorPtr + 4) & 0xfffffffc;

        // Set various global state flags
        GameState::setState(0);      // FUN_004e9cc0(0)
        RenderMode::setMode(1);      // FUN_00413950(1)
        UIMode::setFlag(1);          // FUN_009ceae0(1)

        if (param2 == '\0')
        {
            // Release two pointers if param2 is false
            ReleaseObject(*(void**)(this + 0x74));
            ReleaseObject(*(void**)(this + 0x78));
        }

        // Copy fields from this object to global variables
        gTargetX = *(float*)(this + 0x7c);   // DAT_011280f0
        gTargetY = *(float*)(this + 0x80);   // DAT_011280f4
        gTargetZ = *(float*)(this + 0x84);   // DAT_011280f8
        gTargetDir = *(float*)(this + 0x88); // DAT_0110ac8c
        gActivationFlag = 1;                // DAT_0110acc8 = 1
        gDuration = *(float*)(this + 0x8c); // DAT_0110ac34
    }
}