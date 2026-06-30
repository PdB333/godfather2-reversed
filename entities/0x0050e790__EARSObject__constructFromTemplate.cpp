// FUNC_NAME: EARSObject::constructFromTemplate
void __thiscall EARSObject::constructFromTemplate(int thisPtr, int param1, int param2)
{
    int* thisInt = (int*)thisPtr;
    int* templatePtr = (int*)in_EAX; // passed in EAX, points to template/class descriptor
    int defaultVal = DAT_00e2b1a4; // some global default value (maybe 0)
    int* allocator;
    int subObj;
    int i, count;
    short loopCount;
    byte flagByte;

    // Set vtable pointer at offset 0
    thisInt[0] = (int)&PTR_FUN_00e380ec; // vtable pointer

    // Copy template's first pointer (base object?) into offset 4
    thisInt[1] = *templatePtr;

    // Store parameters
    thisInt[2] = param1;
    thisInt[3] = param2;

    // Initialize many fields to default value
    thisInt[0xd] = defaultVal;
    thisInt[0xe] = defaultVal;
    thisInt[0xf] = defaultVal;
    thisInt[0x10] = defaultVal;
    thisInt[0x13] = defaultVal;

    // Copy from template at offset 0x20 (relative to the pointer at template[0]?)
    thisInt[0x11] = *(int*)(*templatePtr + 0x20);
    thisInt[0x12] = 0;

    // Initialize more fields
    thisInt[0x14] = 0; // will be set later if type == 6
    thisInt[0x15] = 0;
    thisInt[0x16] = 0; // sub object
    thisInt[0x17] = templatePtr[3];
    thisInt[0x18] = templatePtr[4];
    thisInt[0x19] = templatePtr[5];
    thisInt[0x1a] = templatePtr[6];

    // Copy short at template offset 0x1e (bytes)
    *(short*)(thisInt + 0x1b) = *(short*)((int)templatePtr + 0x1e);

    // Copy short at template offset 0x1c? Actually in_EAX[7] is int, but cast to short
    *(short*)((int)thisInt + 0x6e) = (short)templatePtr[7]; // offset 0x6e

    // Copy char at template offset 0x20? Actually in_EAX[8] -> byte at this+0x70
    *(char*)(thisInt + 0x1c) = (char)templatePtr[8]; // offset 0x70? Actually thisInt is int*, so +0x1c gives offset 0x70 bytes? Wait: thisInt + 0x1c is pointer arithmetic by int size, so byte offset 0x70. But earlier we have *(int*)(thisInt+0x1c) or char? Let's assume it's a char field at offset 0x70.

    // Copy two more fields from template
    thisInt[4] = templatePtr[1];
    thisInt[5] = templatePtr[2];

    // Initialize more fields to default
    thisInt[8] = defaultVal;
    thisInt[9] = defaultVal;
    thisInt[10] = defaultVal;
    thisInt[0xb] = defaultVal;

    // Zero out two shorts
    *(short*)((int)thisInt + 0x32) = 0; // offset 0x32
    *(short*)(thisInt + 0xc) = 0; // offset 0x30? Actually thisInt + 0xc is offset 0x30 bytes.

    // Check flag at field4+0x10f (byte)
    flagByte = *(byte*)(thisInt[4] + 0x10f);

    if (*(char*)(thisInt + 0x1c) == 0x06) // char field equals 6
    {
        // Create game manager reference
        thisInt[0x14] = (int)FUN_0050a580(); // likely getGameManager()
        if (thisInt[0x14] != 0)
        {
            if (*(int*)(*(int*)(thisInt[0x14] + 0x90) + 0x24) != 0)
            {
                // Set a flag on the field object
                *(int*)(thisInt[4] + 0x10c) |= 0x1000000;
                goto LAB_0050e914; // skip subobject creation?
            }
            else
            {
                if ((*(int*)(thisInt[4] + 0x10c) & 0x1000000) != 0)
                    goto LAB_0050e914;
                goto LAB_0050e887; // continue to subobject creation
            }
        }
    }
    else
    {
LAB_0050e887:
        if ((flagByte & 1) == 0)
            goto LAB_0050e914;
    }

    // Create a sub-object (e.g., renderable or physical component)
    allocator = (int*)FUN_009c8f80(); // get memory allocator
    {
        int local_c[3] = { 2, 0x10, 0 }; // some initialization structure
        // Call allocator's allocation function: size 0xb0, with local_c as second param
        subObj = (*(int(__thiscall*)(int,int*))(*allocator))(0xb0, local_c);
        if (subObj != 0)
            subObj = FUN_0044daa0(0); // construct the sub-object
    }
    thisInt[0x16] = subObj;
    *(int*)(subObj + 0x94) |= 1; // set flag bit0

    if ((*(byte*)(thisInt[4] + 0x104) & 0x20) != 0)
        *(int*)(subObj + 0x94) |= 0x20;

    if (*(char*)(thisInt[1] + 0x1d) == 0x02)
        *(int*)(subObj + 0x94) |= 0x80;
    else if (*(char*)(thisInt[1] + 0x1d) == 0x01)
        *(int*)(subObj + 0x94) |= 0x10;

LAB_0050e914:
    // Initialize an array of pairs starting at offset 0x80 (thisInt + 0x20)
    loopCount = *(short*)(thisInt + 0x1b); // number of elements
    for (i = 0; i < loopCount; i++)
    {
        int* pairPtr = thisInt + i * 2 + 0x20;
        if (pairPtr != NULL)
        {
            pairPtr[0] = 0;
            pairPtr[1] = 0;
        }
    }

    // If type is 6 and we have both game manager and sub object, set a field in manager
    if (*(char*)(thisInt + 0x1c) == 0x06)
    {
        if ((thisInt[0x14] != 0) && (subObj = thisInt[0x16], subObj != 0))
        {
            int managerStruct = *(int*)(thisInt[0x14] + 0x90);
            int numEntries = *(int*)(managerStruct + 0x34);
            if (numEntries != 0)
            {
                int basePtr = *(int*)(managerStruct + 0x50);
                for (i = 0; i < numEntries; i++)
                {
                    *(int*)(i * 0xb0 + basePtr + 0x58) = subObj;
                }
                return;
            }
        }
    }
    else
    {
        thisInt[0x14] = 0;
    }
}