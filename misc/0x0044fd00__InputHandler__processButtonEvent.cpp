// FUNC_NAME: InputHandler::processButtonEvent
void __thiscall InputHandler::processButtonEvent(void* this_unknown)
{
    int tlsValue;
    uint* pFlagBits;
    int state;

    // Access thread-local storage or global data via FS:0x2C
    // Typical Windows: FS:0x2C points to TLS array or similar
    tlsValue = **(int**)(__readfsdword(0x2C));
    
    // Build pointer to some per-instance flag bits (offset 0x18 from this)
    // The pointer is derived from tlsValue+8 plus a constant offset 0x7c plus this->field_0x18
    pFlagBits = (uint*)(*(int*)(tlsValue + 8) + 0x7C + *(int*)((int)this_unknown + 0x18));
    
    if (((*pFlagBits & 0x8000) != 0) && ((*pFlagBits & 0x200) != 0))
    {
        // Clear bit 9 (0x200) – indicates "first press" consumed
        *pFlagBits = *pFlagBits & 0xFFFFFDFF;
        
        state = *(int*)((int)this_unknown + 0x20); // offset 0x20: current state/context
        if ((state == 2) || (state == 1 || (state == 0xF)))
        {
            FUN_0044fe80(this_unknown, (int)this_unknown); // handle specific states
        }
        else
        {
            if (state == 0x12)
            {
                char checkResult = FUN_0044d910((int)this_unknown);
                if (checkResult != '\0')
                    goto LAB_0044fd79;
            }
            if ((*(uint*)(*(int*)(tlsValue + 8) + 0x7C + *(int*)((int)this_unknown + 0x18)) & 0x100) == 0)
            {
                FUN_004500f0(this_unknown);
            }
            else
            {
                FUN_00450030(this_unknown);
            }
        }
    }
LAB_0044fd79:
    // Append 'this' to a global list (likely for deferred processing)
    // DAT_01206880 is a global pointer to some manager structure
    uint** listPtr = (uint**)(DAT_01206880 + 0x14);
    **(undefined4**)listPtr = &PTR_LAB_0110b8dc; // set vtable or next pointer?
    *listPtr = (uint*)((int)(*listPtr) + 4);
    int* alignedPtr = (int*)((int)(*listPtr) + 3 & 0xFFFFFFFC);
    *listPtr = (uint*)alignedPtr;
    *alignedPtr = (int)this_unknown;
    *listPtr = (uint*)((int)(*listPtr) + 4);
    return;
}