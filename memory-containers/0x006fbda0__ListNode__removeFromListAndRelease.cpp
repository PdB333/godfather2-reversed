// FUNC_NAME: ListNode::removeFromListAndRelease

// Function at 0x006fbda0 – removes this node from a doubly linked list and releases associated resources.
// Class fields: +0x08 = prevPtr, +0x0C = nextPtr, +0x10 = pResource, +0x18 = pData
void __fastcall ListNode::removeFromListAndRelease(int thisPtr)
{
    // Local buffer for GUID or identifier (12 bytes)
    char guidBuffer[12];
    
    // Release data object if present
    if (*(int*)(thisPtr + 0x18) != 0)
    {
        FUN_005e3260();           // Pre‑release step 1
        FUN_005e3280();           // Pre‑release step 2
        guidBuffer[0] = 1;        // Some flag for release
        FUN_005e2ad0(*(int*)(thisPtr + 0x18), guidBuffer);  // Release data, may fill guidBuffer
    }
    
    // Release resource object if present
    if (*(int*)(thisPtr + 0x10) != 0)
    {
        FUN_004daf90(thisPtr + 0x10);  // Release resource (e.g. decrement ref count)
    }
    
    // Unlink from doubly linked list
    if (*(int*)(thisPtr + 0x08) != 0)
    {
        // Set nxt of prev node to our nxt
        *(int*)(*(int*)(thisPtr + 0x08) + 0x0C) = *(int*)(thisPtr + 0x0C);
    }
    if (*(int*)(thisPtr + 0x0C) != 0)
    {
        // Set prev of next node to our prev
        *(int*)(*(int*)(thisPtr + 0x0C) + 0x08) = *(int*)(thisPtr + 0x08);
    }
    
    // Update global list head if we were the head
    if (DAT_0112aaa8 == thisPtr)
    {
        DAT_0112aaa8 = *(int*)(thisPtr + 0x0C);
    }
    
    return;
}