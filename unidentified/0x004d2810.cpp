// FUN_004d2810: GameObject::destroy
char GameObject::destroy(int** childrenArray, int childrenCount) // __thiscall: this in ESI, parameters on stack
{
    // this+0x14: pointer to data block
    uint* dataBlock = *(uint**)(this + 0x14);
    dataBlock[1] = 0;                    // +0x04 in data block (clear reference)
    FUN_009c8f10(dataBlock[0]);          // free memory at dataBlock[0] (likely allocation)
    dataBlock[0] = 0;                    // null the pointer
    dataBlock[2] = 0;                    // +0x08 in data block (clear count?)

    // Call something on sub-object at this+0x04
    FUN_00497c00(*(undefined4*)(this + 4));

    // Indicate destruction is in progress (0 = not destroyed yet? but it's being destroyed now)
    *(byte*)(this + 0x18) = 0;           // +0x18: destroyed flag (0 = active, 1 = destroyed?)

    // If there's a manager/flags at this+0x08, process children
    if (*(int*)(this + 8) != 0)
    {
        uint idx = 0;
        if (childrenCount != 0)
        {
            do {
                int* child = childrenArray[idx];
                if (child != (int*)0x0)
                {
                    // Call virtual function at vtable+0x34 on each non-null child
                    (*(code**)(*child + 0x34))();
                }
                idx = idx + 1;
            } while (idx < (uint)childrenCount);
        }
    }

    char result = '\0';
    // Check destroyed flag (always 0 here, but kept for logic)
    if (*(char*)(this + 0x18) == '\0')
    {
        result = '\x01'; // success: 1
    }
    else if (*(int*)(*(int*)(this + 0x14) + 4) != 0) // alternative path (likely unreachable)
    {
        char alt = FUN_004d29e0(this); // some other cleanup
        result = (alt != '\0') + '\x02'; // returns 2 or 3
    }

    // Free the children array if it was provided
    if (childrenArray != (int**)0x0)
    {
        FUN_009c8f10(childrenArray); // deallocate
    }

    return result;
}