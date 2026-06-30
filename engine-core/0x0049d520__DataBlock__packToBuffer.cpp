// FUNC_NAME: DataBlock::packToBuffer
void __thiscall DataBlock::packToBuffer(OutputBuffer* outBuffer, int destBase, uint16 param3, void* optionalCopyDest, uint16 param5)
{
    ushort uVar1;
    bool validSlot;
    char slotValid;
    void* srcData;
    int iVar4;
    int iVar5;
    int iVar6;
    undefined4* puVar7;
    ushort* puVar8;
    byte* pbVar9;
    byte* pbVar10;
    int* piVar11;
    int* local_3c;
    ushort* local_30;
    uint uStack_2c;
    int slotCount;

    // Copy header fields from this to output buffer
    // +0x14, +0x18: some vector/position fields
    outBuffer->field_00 = *(undefined4*)((char*)this + 0x14);
    outBuffer->field_04 = *(undefined4*)((char*)this + 0x18);
    // +0x08, +0x0C: another pair
    outBuffer->field_30 = *(undefined4*)((char*)this + 8);
    outBuffer->field_34 = *(undefined4*)((char*)this + 0xC);
    // +0x10: a byte flag
    *(byte*)((int)outBuffer + 0x38) = *(byte*)((char*)this + 0x10);
    // Store parameters
    outBuffer->field_4C = destBase;
    *(uint16*)((int)outBuffer + 0x3C) = param5;
    *(uint16*)((int)outBuffer + 0x3A) = param3;
    outBuffer->field_50 = optionalCopyDest;

    uVar1 = *(ushort*)((char*)this + 0x48); // offset to sub-item array
    // Calculate source data pointer: (this + 0x4c) holds a 16-bit relative offset
    srcData = (void*)((uint)*(ushort*)((char*)this + 0x4C) + (int)this);
    if (optionalCopyDest != (void*)0x0) {
        _memcpy(optionalCopyDest, srcData, (uint)*(ushort*)((char*)this + 0x4E));
        srcData = optionalCopyDest;
    }
    optionalCopyDest = srcData;
    outBuffer->field_48 = (uint)*(ushort*)((char*)this + 0x46); // item count

    // Initialize pointers for the 5-slot loop
    pbVar9 = (byte*)((int)outBuffer + 0x43); // pointer into output buffer for per-slot data
    pbVar10 = (byte*)((char*)this + 0x20);   // source slots start at this+0x20
    puVar7 = outBuffer + 3;                  // output pointer for slot descriptors
    iVar4 = (int)outBuffer + (0x3E - (int)pbVar9); // offset for slot-related byte
    local_30 = (ushort*)0x0;
    slotCount = 5;

    do {
        local_3c = (int*)0x0;
        // Global linked list of type nodes (DAT_012058ec)
        int* currentNode = DAT_012058ec;
        // Look up the slot's type ID (from 4 bytes before current slot start)
        int slotTypeId = *(int*)(pbVar10 - 4);
        if (slotTypeId != 0) {
            while (local_3c = currentNode, local_3c != (int*)0x0) {
                if (slotTypeId == local_3c[2]) goto LAB_0049d5fc; // found
                currentNode = (int*)local_3c[1]; // linked list next
            }
            local_3c = (int*)0x0;
        }
LAB_0049d5fc:
        // Store pointer to found type node (or null)
        puVar7[-1] = local_3c;
        puVar7[0] = 0; // initialize counter
        // Slot header: stored count from source bytes
        pbVar9[iVar4] = *pbVar10;               // first byte: low count?
        *pbVar9 = pbVar10[1] + *pbVar10;        // sum of two bytes => total items for this slot?
        if (local_3c == (int*)0x0) {
LAB_0049d62b:
            validSlot = false;
        } else {
            // Virtual call to validate the slot type (vtable +0x2c)
            slotValid = (**(code**)(*local_3c + 0x2C))();
            validSlot = true;
            if (slotValid == '\\0') goto LAB_0049d62b;
        }

        uStack_2c = (uint)pbVar9[iVar4]; // start index for inner loop
        // Only process if inner count is within range
        if (uStack_2c < *pbVar9) {
            // Point to the sub-item array inside this object: base + uVar1 + 6 + index*12
            puVar8 = (ushort*)((uint)uVar1 + (int)this + 6 + uStack_2c * 0xC);
            // Point to the output destination slot (destBase + index*0x20 + 4)
            piVar11 = (int*)(uStack_2c * 0x20 + 4 + destBase);
            do {
                // Guard against overwriting previous data
                if (local_30 < puVar8 + -3) {
                    local_30 = puVar8 + -3; // cache pointer
                    iVar6 = *(int*)local_30; // read 4-byte ID from sub-item
                    // Write to output entry: 4-byte ID, then zeros, then type byte
                    piVar11[-1] = iVar6;
                    *piVar11 = 0;
                    piVar11[1] = 0;
                    *(char*)(piVar11 + 2) = (char)puVar8[-1]; // type from sub-item
                    // Resolve resource handles if type node exists
                    if (local_3c != (int*)0x0) {
                        // First try lookup from local_3c[4]
                        iVar5 = FUN_0060a630(local_3c[4], iVar6); // resource lookup
                        piVar11[1] = iVar5;
                        if (iVar5 == 0) {
                            // Fallback to local_3c[5]
                            if (local_3c[5] != 0) {
                                iVar6 = FUN_0060a630(local_3c[5], iVar6);
                                piVar11[1] = iVar6;
                                *piVar11 = local_3c[5];
                            }
                        } else {
                            *piVar11 = local_3c[4];
                        }
                    }
                    // Interpret the type byte to write the value pointer
                    switch ((char)piVar11[2]) {
                    case '\0':
                        // Direct value: read word from optionalCopyDest at offset puVar8[0]
                        piVar11[3] = *(int*)((uint)*puVar8 + (int)optionalCopyDest);
                        break;
                    case '\x01':
                    case '\x02':
                    case '\x03':
                    case '\x04':
                        // Relative offset: puVar8[0] is offset into data
                        piVar11[3] = (uint)*puVar8 + (int)optionalCopyDest;
                        break;
                    case '\x05':
                        // Special case: call helper function
                        FUN_0049d3d0();
                    }
                    if (validSlot) {
                        // Notify type node about the packed entry (vtable +0x28)
                        (**(code**)(*local_3c + 0x28))(piVar11 + -1);
                    }
                }
                uStack_2c = uStack_2c + 1;
                puVar8 = puVar8 + 6; // next sub-item (12 bytes)
                piVar11 = piVar11 + 8; // next output entry (0x20 bytes)
            } while ((int)uStack_2c < (int)(uint)*pbVar9);
        }
        // Advance to next slot
        puVar7 = puVar7 + 2;
        pbVar10 = pbVar10 + 8;
        pbVar9 = pbVar9 + 1;
        slotCount = slotCount + -1;
        if (slotCount == 0) {
            return;
        }
    } while (true);
}