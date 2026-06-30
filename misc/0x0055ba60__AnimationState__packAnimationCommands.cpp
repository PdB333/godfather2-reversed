// FUNC_NAME: AnimationState::packAnimationCommands
void __fastcall AnimationState::packAnimationCommands()
{
    // +0x484: Flag indicating command list needs to be rebuilt
    *(int*)((char*)this + 0x484) = 1;

    // Four command pointers stored sequentially starting at +0x710
    int* cmd0 = *(int**)((char*)this + 0x710);
    int* cmd1 = *(int**)((char*)this + 0x714);
    int* cmd2 = *(int**)((char*)this + 0x718);
    int* cmd3 = *(int**)((char*)this + 0x71C);

    // Process each non-null command pointer
    if (cmd0 != nullptr)
    {
        // Get current write pointer from global buffer manager
        uint* bufferPtr = (uint*)(DAT_01206880 + 0x14); // +0x14: current buffer offset
        // Write a vtable pointer for the command object
        *(void**)(*bufferPtr) = &PTR_LAB_01124690;
        *bufferPtr += 4;
        // Write the command pointer itself
        *(int*)(*bufferPtr) = (int)cmd0;
        *bufferPtr += 4;
        // Write offset to animation state data (+0x54)
        *(int*)(*bufferPtr) = (int)this + 0x54;
        *bufferPtr += 4;
        // Write null terminator byte
        *(char*)(*bufferPtr) = 0;
        // Align to 4 bytes
        *bufferPtr = (*bufferPtr + 4) & 0xFFFFFFFC;
    }

    if (cmd1 != nullptr)
    {
        uint* bufferPtr = (uint*)(DAT_01206880 + 0x14);
        *(void**)(*bufferPtr) = &PTR_LAB_01124690;
        *bufferPtr += 4;
        *(int*)(*bufferPtr) = (int)cmd1;
        *bufferPtr += 4;
        *(int*)(*bufferPtr) = (int)this + 0x54;
        *bufferPtr += 4;
        *(char*)(*bufferPtr) = 0;
        *bufferPtr = (*bufferPtr + 4) & 0xFFFFFFFC;
    }

    if (cmd2 != nullptr)
    {
        uint* bufferPtr = (uint*)(DAT_01206880 + 0x14);
        *(void**)(*bufferPtr) = &PTR_LAB_01124690;
        *bufferPtr += 4;
        *(int*)(*bufferPtr) = (int)cmd2;
        *bufferPtr += 4;
        *(int*)(*bufferPtr) = (int)this + 0x54;
        *bufferPtr += 4;
        *(char*)(*bufferPtr) = 0;
        *bufferPtr = (*bufferPtr + 4) & 0xFFFFFFFC;
    }

    if (cmd3 != nullptr)
    {
        uint* bufferPtr = (uint*)(DAT_01206880 + 0x14);
        *(void**)(*bufferPtr) = &PTR_LAB_01124690;
        *bufferPtr += 4;
        *(int*)(*bufferPtr) = (int)cmd3;
        *bufferPtr += 4;
        *(int*)(*bufferPtr) = (int)this + 0x54;
        *bufferPtr += 4;
        *(char*)(*bufferPtr) = 0;
        *bufferPtr = (*bufferPtr + 4) & 0xFFFFFFFC;
    }
}