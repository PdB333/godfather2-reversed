// FUNC_NAME: Entity::updateVisuals
int __thiscall Entity::updateVisuals(int *this)
{
    uint *flagsPtr;
    int result;
    char isNull;
    int tempInt;
    int *meshBase;
    int stackLocal_24;
    int stackLocal_20;
    int *stackLocal_1c;
    undefined4 *stackLocal_18;
    undefined4 local_8;
    undefined4 local_4;

    // Check if mesh pointer is invalid (0) or a special marker (0x48)
    if ((this[0x14] == 0) || (this[0x14] == 0x48))
    {
        stackLocal_18 = (undefined4 *)0x884127;
        FUN_00624d00(); // assertion failure
    }

    local_4 = 0;
    local_8 = 0;

    // Compute base of mesh object (subtract offset 0x48 to get the containing object)
    if (this[0x14] == 0)
    {
        meshBase = (int *)0x0;
    }
    else
    {
        meshBase = (int *)(this[0x14] + -0x48);
    }

    // Set up stack variables for sending to virtual functions
    stackLocal_18 = &local_8;
    stackLocal_1c = this + 0x17;                     // pointer to some structure at +0x17
    stackLocal_20 = CONCAT31((int3)((uint)stackLocal_1c >> 8), this[0x1b] == 0); // packed bool and pointer
    stackLocal_24 = this[0x16];                       // sim object pointer

    // Virtual call at meshBase vtable +0x200: check if skeleton is ready
    isNull = (**(code **)(*meshBase + 0x200))();
    if (isNull == '\0')
    {
        tempInt = FUN_00624d00();
        return tempInt;
    }

    // Compute base again for mesh
    if (this[0x14] == 0)
    {
        tempInt = 0;
    }
    else
    {
        tempInt = this[0x14] + -0x48;
    }

    // Virtual call on sim object (this[0x16]) vtable +0x1ac: update skeleton bones
    (**(code **)(*(int *)this[0x16] + 0x1ac))();

    // Only if mesh is valid and not the special marker
    if ((this[0x14] != 0) && (this[0x14] != 0x48))
    {
        // Recompute mesh base
        if (this[0x14] == 0)
        {
            meshBase = (int *)0x0;
        }
        else
        {
            meshBase = (int *)(this[0x14] + -0x48);
        }

        // Virtual call +0x274: update mesh (e.g., transform)
        (**(code **)(*meshBase + 0x274))();

        // Recompute mesh base again
        if (this[0x14] == 0)
        {
            meshBase = (int *)0x0;
        }
        else
        {
            meshBase = (int *)(this[0x14] + -0x48);
        }

        // Virtual call +0x280: get bone matrix (or something) using stackLocal_1c as output
        undefined4 boneMatrix = (**(code **)(*meshBase + 0x280))(&stackLocal_1c);

        // Process the bone matrix through some function
        undefined4 processed = FUN_00875af0(this[0x16], boneMatrix);

        // Virtual call on 'this' vtable +0x2c: render/draw with parameters
        (**(code **)(*this + 0x2c))(processed, 0, 1, 1, this[0x1e], 0x3f800000);
    }

    // Check bit 2 of flags (0x4)
    if (((uint)this[0x1d] >> 2 & 1) != 0)
    {
        FUN_0072d290(); // some additional update (e.g., particle effects)
    }

    // Clear bit 19 (0x40000) in flags at sim object +0x1b94
    int simObject = this[0x16];
    flagsPtr = (uint *)(simObject + 0x1b94);
    *flagsPtr = *flagsPtr & 0xfff7ffff;
    // Clear bit 0 of local flags
    this[0x1d] = this[0x1d] & 0xfffffffe;

    // Check bit 1 of flags (0x2)
    if (((uint)this[0x1d] >> 1 & 1) != 0)
    {
        stackLocal_20 = 0;
        stackLocal_24 = 0;

        // Get position reference from mesh? Virtual call +0x1cc
        if (this[0x14] == 0)
        {
            meshBase = (int *)0x0;
        }
        else
        {
            meshBase = (int *)(this[0x14] + -0x48);
        }
        result = (**(code **)(*meshBase + 0x1cc))(&stackLocal_24);

        // Store position into sim object at offsets 0x860 and 0x864
        int simObj = this[0x16];
        *(int *)(simObj + 0x860) = tempInt;   // tempInt = meshBase (or 0)
        *(int *)(simObj + 0x864) = stackLocal_24; // returned value
    }

    return result;
}