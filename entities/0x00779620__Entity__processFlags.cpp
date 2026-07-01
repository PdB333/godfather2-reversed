// FUNC_NAME: Entity::processFlags
void __thiscall Entity::processFlags(Entity* thisPtr)
{
    uint flags;
    int* basePtr;

    // Set bit 3 (0x8) in flags at +0x90
    *(uint *)(thisPtr + 0x90) |= 8;

    // Check bit 4 (0x10)
    if ((*(uint *)(thisPtr + 0x90) >> 4 & 1) == 0) {
        // If bit 4 is clear, set bit 5 (0x20) and return
        *(uint *)(thisPtr + 0x90) |= 0x20;
        return;
    }

    // Bit 4 is set, check member at +0x88 (either an ID or pointer)
    int val = *(int *)(thisPtr + 0x88);
    if (val != 0 && val != 0x48) {
        // Compute base pointer by subtracting 0x48 from the stored value
        // (val is treated as a pointer into a base structure)
        basePtr = (int *)(val - 0x48);
        // Call virtual function at vtable offset 0x1a8 (likely a getter)
        float condition = (***(code ***)basePtr)(basePtr); // vtable[0x1a8/4]()
        if ((float)_DAT_00d6835c < condition) {
            char randomResult = FUN_00778fd0(); // random or boolean check
            if (randomResult != 0) {
                uint index = DAT_010c2678 & DAT_012054b4;
                DAT_012054b4 = DAT_012054b4 + 1;
                float dataVal = *(float *)(&DAT_010c2680 + index * 4);
                if (dataVal <= DAT_00d68364 && DAT_00d68364 != dataVal) {
                    // Set bit 6 (0x40) and return
                    *(uint *)(thisPtr + 0x90) |= 0x40;
                    return;
                }
            }
        }
    }

    // Recompute basePtr (same logic) and call another virtual function (0x298)
    int val2 = *(int *)(thisPtr + 0x88);
    if (val2 == 0) {
        basePtr = (int *)0;
    } else {
        basePtr = (int *)(val2 - 0x48);
    }
    // Call virtual function at vtable offset 0x298 (likely the main action)
    (**(code **)(*basePtr + 0x298))();
}