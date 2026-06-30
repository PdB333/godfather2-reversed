// FUNC_NAME: StreamManager::setCurrentBuffer
void __thiscall StreamManager::setCurrentBuffer(int bufferId)
{
    int oldBuffer;
    int *listPtr;
    int temp;
    int originalBufferId = bufferId;

    // Clear flag at +0x1C if set
    if (*(int *)(this + 0x1C) != 0) {
        *(int *)(this + 0x1C) = 0;
    }

    // If there is an active buffer and it's not the requested one
    if (*(int *)(this + 0x14) != 0 && *(int *)(this + 0x10) != bufferId) {
        oldBuffer = *(int *)(this + 0x14);
        if (oldBuffer != 0) {
            // Add old buffer to the global free list (DAT_01206880 + 0x14)
            listPtr = (int *)(gMemoryPool + 0x14);
            **(int **)(gMemoryPool + 0x14) = &PTR_LAB_01123be8;  // vtable for free list node
            *listPtr = *listPtr + 4;
            *(int *)*listPtr = oldBuffer;
            *listPtr = *listPtr + 4;
            *(int *)(this + 0x14) = 0;
            *(int *)(this + 0x18) = 0;
        }
        *(int *)(this + 0x14) = 0;
        *(int *)(this + 0x18) = 0;
    }

    // If no active buffer, allocate a new one
    if (*(int *)(this + 0x14) == 0) {
        if (originalBufferId == 0) {
            bufferId = 0;
            temp = 0;
        } else {
            allocateBuffer(&bufferId);  // FUN_00485650
            temp = originalBufferId;
        }
        *(int *)(this + 0x14) = bufferId;
        *(int *)(this + 0x18) = temp;
        if (bufferId == 0) {
            *(int *)(this + 0x10) = 0;
            return;
        }
    }

    // Update current buffer ID
    *(int *)(this + 0x10) = originalBufferId;

    // Compute thread-local offset and call virtual method at vtable+0x14
    int arg1 = 0;
    if (*(int *)(this + 0x14) != 0) {
        arg1 = *(int *)(**(int **)(gThreadContext + 0x2C) + 8) + *(int *)(this + 0x14);
    }
    (*(void (**)(int, int))(**(int **)(this + 0x24) + 0x14))(arg1, originalBufferId);
}