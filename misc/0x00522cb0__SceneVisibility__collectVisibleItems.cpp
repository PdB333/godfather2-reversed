// FUNC_NAME: SceneVisibility::collectVisibleItems
int* SceneVisibility::collectVisibleItems(int* thisPtr, int* object, bool useStepArray, int param4, float fadeFactor)
{
    float fVar7;
    bool bHasStep;
    int* piVar3;
    int itemCount;
    int validCount = 0;
    int stepCounter;
    int idxLocal78;
    float* stepArray;
    int iVar6;
    float fVar8;
    int local_60[3]; // 12 bytes
    int local_20, iStack_1c, iStack_18, iStack_14;
    // +0x0: transform matrix? 
    // +0x10: additional data
    // +0x14: more data

    // Assume this pointer: param_1
    // Structure offsets for this:
    // +0x0: pointer to some system? (piVar3 = *thisPtr)
    // +0x4: (short) thisPtr[4] used as count/3
    // +0x8: ptr to array of items (stride 0x60)
    // +0xc: ptr to step array (floats)
    // +0x18-0x1a: something stored (local_60, iStack_5c, iStack_58)
    // These are used only when param_3 != 0

    // Global state:
    // DAT_01125388: current view index (used as index into table of 0x38 byte entries)
    // DAT_011252e8: pointer to debug/console system
    // DAT_00e2b04c, DAT_00e2b1a4, DAT_00e2af44: constants (likely fade/dist thresholds)
    // DAT_01218e00: format string for debug output

    if ((*thisPtr != 0) && (piVar3 = (*thisPtr) - 1, piVar3 != 0)) // some check on pointer
    {
        piVar3 = (int*)FUN_0049f870(); // get frustum or similar
        fVar7 = in_XMM0_Da * DAT_00e2b04c - DAT_00e2b1a4;
        if (fVar7 < 0.0f) fVar7 = 0.0f;
        fVar7 *= fadeFactor;

        if (fVar7 <= DAT_00e2af44) // if fadeFactor below threshold, early exit
        {
            return piVar3;
        }

        // Print debug message if current view's debug context exists
        int* viewDebugCtx = *(int**)(&DAT_011253f4 + (uint)DAT_01125388 * 0x38);
        if (viewDebugCtx != 0)
        {
            debugPrint(DAT_011252e8, viewDebugCtx, &DAT_01218e00); // print culling info
        }

        // Handle special debug toggles based on object flags (bit 0x20 at +0x44)
        if ((*(byte*)(object + 0x44) & 0x20) != 0)
        {
            toggleDebugDraw1(DAT_01163840 != 0);
        }

        // If using step array or debug flag set, toggle debug draw 2
        if (useStepArray || ((*(byte*)(object + 0x44) & 0x20) != 0))
        {
            toggleDebugDraw2();
        }

        fVar8 = DAT_00e2b1a4;
        if (*(char*)(object + 0x48) == 1) // camera type?
        {
            fVar8 = 0.0f;
        }
        setCameraProjection(param4, fVar8); // set projection matrix or fov
        prepareTransform();

        // Compute number of items from this->array count (short at +8)
        itemCount = (int)(short)thisPtr[4] / 3; // thisPtr[4] is a short, divided by 3
        int maxItems = itemCount;

        // First pass: count valid items (visible or marked)
        for (int i = 0; i < itemCount; i++)
        {
            int* itemPtr = (int*)(thisPtr[2] + 0x0c + i * 0x60); // actually stride 0x60, offset 0x0c? Wait, the code uses param_1[2] + 0xc as starting point? Actually: piVar3 = (int*)(param_1[2] + 0xc); and then piVar3[4] etc.
            // Let's reinterpret: The loop uses piVar3 as pointer to a structure at thisPtr[2] + 0xc, and increments by 0x18? Actually it increments by 0x18 (size 0x60/4? No, 0x60 bytes = 0x18 ints). So the structure at index j is at thisPtr[2] + 0xc + j*0x60? No, the initial piVar3 = thisPtr[2] + 0xc, then piVar3 += 0x18 each iteration. So the stride in ints is 0x18 (96 bytes) but item stride is 0x60? Wait, 0x60 = 96, yes. So offset 0xc is the first field of the item? Actually the initial piVar3 = thisPtr[2] + 0xc; if item stride is 0x60, then after adding 0x18 * 4? No, 0x18 ints = 0x60 bytes. So each piVar3 advances by 0x18 ints = 0x60 bytes. So the starting address is thisPtr[2] + 0xc, which may be an offset within each item? Possibly the item structure has base at thisPtr[2] and each item is 0x60 bytes, starting with fields at +0x0, +0x4,... but the code accesses piVar3[4] which corresponds to offset 0x10? Wait, piVar3[4] meaning piVar3+4*4 = piVar3+16 bytes. If piVar3 starts at +0xc, then piVar3[4] is at +0xc+0x10 = +0x1c. That matches the field we saw later at offset 0x1c. So piVar3 points to offset 0xc within the item? Actually the item fields: at +0xc is a pointer? Later we see *(int*)(iVar4+0xc) where iVar4 = thisPtr[2] + local_70, and local_70 increments by 0x60. So the field at +0xc is used. So piVar3 pointing to +0xc means it's the middle of the item? That seems odd. Perhaps the item structure is 0x60 bytes and the fields are:
            // +0x00: unknown
            // +0x0c: pointer to some object (with flags at +8)
            // +0x10: int
            // +0x14: int
            // +0x18: int (used as uVar1)
            // +0x1c: entity pointer (with flag at +0xb2)
            // +0x20: start of second transform? (used later)
            // +0x40: start of third transform?
            // So the code iterates items by taking piVar3 = &item->field_C (offset 0xc). Then piVar3[4] is field_C + 0x10 = offset 0x1c (entity pointer). So the check: if piVar3[4] == 0 || (*(byte*)(piVar3[4] + 0xb2) & 1) != 0) && (*piVar3 != 0) && ((*(byte*)(*piVar3 + 8) & 2) != 0)
            // This checks if entity is valid or has certain flag, and the object at +0xc has bit 1 set at +8.
        }
        itemCount = maxItems; // first loop just counts valid items

        // Second pass: build output buffer
        if (useStepArray)
        {
            // Save some data from thisPtr for later use
            local_60[0] = thisPtr[0x18];
            local_60[1] = thisPtr[0x19];
            local_60[2] = thisPtr[0x1a];
            int* someCtx = *(int**)(&DAT_01125410 + (uint)DAT_01125388 * 0x38);
            int* param4Ptr = *(int**)(object + 0x40); // something from object
            if (someCtx != 0)
            {
                handleSpecialCase(DAT_011252e8, someCtx, &local_60);
            }
        }

        if (validCount > 0)
        {
            // Allocate buffer: 3 sets per valid item (each set 6 ints? actually 8 ints? See below)
            // Each item writes 3 * 8 ints = 24 ints per item? The allocation is (4, iVar6*3, 0, 1, 0) where iVar6 = validCount? Actually iVar6=validCount, then 4 * iVar6*3 = 12 iVar6 bytes? No, first param is unknown meaning. The buffer pointer returned is piVar3, and we use piVar3 and piVar5 = piVar3+4. So piVar3 is likely an array of 8-int structures? We'll model as two interleaved sets.
            int* buffer = (int*)allocateMemory(4, validCount * 3, 0, 1, 0);
            if (buffer != 0)
            {
                // Initialize accumulation variables
                int accX = 0, accY = 0, accZ = 0; // for local_30, iStack_2c, iStack_28
                int accW = 0; // for local_20, etc?
                // Actually the code uses local_30, iStack_2c, iStack_28 as accumulation? They are set to 0 initially, then later assigned to the buffer. But they are also used in the inner loop? They appear to be constant (all zero). So they represent a zero vector/quaternion.
                int zero0 = 0, zero1 = 0, zero2 = 0;
                float stepVal = fVar7; // stored as int (float bits)

                stepCounter = (useStepArray ? 0 : -1) - 1; // local_7c initialization: (param_3 != 0) - 1
                bHasStep = false;

                // Iterate over all items using index local_70 = 0, stride 0x60
                for (int i = 0; i < itemCount; i++)
                {
                    int* itemBase = (int*)(thisPtr[2] + local_70); // local_70 increments by 0x60 each loop
                    // When stepCounter reaches 0, load next step value from step array
                    if (stepCounter == 0)
                    {
                        // stepArray = thisPtr[3] (pointer to floats)
                        stepArray = (float*)thisPtr[3];
                        stepCounter = (int)*(float*)(stepArray + 3 + local_78); // reading from stepArray + 0xc? Actually local_78 is offset in bytes? Let's simplify: we read a float at thisPtr[3] + 0xc + local_78, where local_78 starts at -0x10 and increments by 0x10 each time. So local_78 is offset in bytes. After reading, we reset stepCounter to that float as int.
                        stepCounter = (int)*(float*)((int*)thisPtr[3] + 0x3 + local_78/4); // approximate
                        bHasStep = true;
                    }
                    stepCounter -= 3; // decrement by 3 each iteration

                    // Compute current item pointer
                    int* item = itemBase; // thisPtr[2] + local_70
                    // Check if valid
                    int entityPtr = *(int*)(item + 0x1c/4); // +0x1c
                    int objPtr = *(int*)(item + 0x0c/4); // +0x0c
                    if (((entityPtr == 0) || ((*(byte*)(entityPtr + 0xb2) & 1) != 0)) &&
                        (objPtr != 0 && ((*(byte*)(objPtr + 8) & 2) != 0)))
                    {
                        uVar1 = *(int*)(item + 0x18/4); // +0x18: some id or matrix
                        if (bHasStep)
                        {
                            // Transform from step array into local_60
                            vectorTransform(uVar1, thisPtr[3] + local_78, (int*)&local_60);
                            iStack_14 = computeVisibilityFlags();
                            bHasStep = false;
                        }

                        // First set of data: from item base +0x0? Actually first copy: FUN_0056b480(uVar1, item, &local_60);
                        copyTransformedData(uVar1, item, &local_60);
                        computeAABB(); // dummy name
                        // Read local_20, iStack_1c from item+0x10 and item+0x14
                        local_20 = *(int*)(item + 0x10/4);
                        iStack_1c = *(int*)(item + 0x14/4);

                        // Write first batch into buffer
                        *buffer = zero0;
                        buffer[1] = zero1;
                        buffer[2] = zero2;
                        buffer[3] = *(int*)&stepVal; // store fVar7 as int
                        buffer[4] = local_20;
                        buffer[5] = iStack_1c;
                        buffer[6] = iStack_18; // still 0
                        buffer[7] = iStack_14;

                        // Second set: from item+0x20
                        int* secondSrc = (int*)((int)item + 0x20);
                        copyTransformedData(uVar1, secondSrc, &local_60);
                        computeAABB();
                        local_20 = *(int*)(secondSrc + 0x10/4);
                        iStack_1c = *(int*)(secondSrc + 0x14/4);
                        buffer[8] = zero0;
                        buffer[9] = zero1;
                        buffer[10] = zero2;
                        buffer[11] = *(int*)&stepVal;
                        buffer[12] = local_20;
                        buffer[13] = iStack_1c;
                        buffer[14] = iStack_18;
                        buffer[15] = iStack_14;

                        // Third set: from item+0x40
                        int* thirdSrc = (int*)((int)item + 0x40);
                        copyTransformedData(uVar1, thirdSrc, &local_60);
                        computeAABB();
                        local_20 = *(int*)(thirdSrc + 0x10/4);
                        iStack_1c = *(int*)(thirdSrc + 0x14/4);
                        buffer[16] = zero0;
                        buffer[17] = zero1;
                        buffer[18] = zero2;
                        buffer[19] = *(int*)&stepVal;
                        buffer[20] = local_20;
                        buffer[21] = iStack_1c;
                        buffer[22] = iStack_18;
                        buffer[23] = iStack_14;

                        // Each item writes 24 ints (3 sets * 8 ints)
                        buffer += 24;
                    }
                    local_70 += 0x60;
                    itemCount--; // decrement loop counter
                }
                piVar3 = (int*)finalizeAllocation();
            }
        }
    }
    return piVar3;
}