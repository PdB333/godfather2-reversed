// FUNC_NAME: SlotManager::activateSlot
uint SlotManager::activateSlot(SourceData* source) // this = slotArray (EDI), source (ESI)
{
    int iVar1;
    bool bVar2;
    float fVar3;
    uint in_EAX;
    uint uVar4;
    undefined3 uVar5;
    uint slotIndex;
    int iVar7;
    int* piVar8;
    int slotArray; // unaff_EDI
    int sourceData; // unaff_ESI
    float fVar9;
    float fVar10;

    slotIndex = 0;
    uVar4 = in_EAX & 0xffffff00; // Preserve high 24 bits of EAX for error return

    if (source->field_0x1c == 0) // source is active
    {
        // Start at first slot's key area (offset 0x18 from slot base, but keys stored at -0xC, -0x8, -0x4, 0, +4 relative)
        piVar8 = (int*)(slotArray + 0x18);
        while (true)
        {
            // Check if slot is unused (key0 == -1) or matches all keys from source
            if (piVar8[-3] != -1 && 
                piVar8[-2] == *(int*)(sourceData + 0x20) &&
                piVar8[-1] == *(int*)(sourceData + 0x24) &&
                *piVar8 == *(int*)(sourceData + 0x28) &&
                piVar8[1] == *(int*)(sourceData + 0x2c))
            {
                break; // Found matching slot
            }
            slotIndex++;
            piVar8 += 0x1a; // Advance to next slot (0x1a * 4 = 0x68 bytes)
            if (slotIndex > 4)
            {
                return uVar4; // No slot found, return error
            }
        }

        iVar7 = slotIndex * 0x68 + slotArray; // Base of found slot

        // Save original value at slot+0x4c
        iVar1 = *(int*)(iVar7 + 0x4c);

        // Initialize slot fields from source
        *(undefined4*)(iVar7 + 0x08) = *(undefined4*)(sourceData + 0x18);

        // Check if slot's initialized value exceeds threshold
        bVar2 = DAT_00e44598 <= *(float*)(iVar7 + 0x08);

        // Copy current position (0x38,0x3C) to previous position (0x28,0x2C)
        *(float*)(iVar7 + 0x28) = *(float*)(iVar7 + 0x38);
        *(float*)(iVar7 + 0x2c) = *(float*)(iVar7 + 0x3c);

        // Store the saved value at slot+0x40
        *(int*)(iVar7 + 0x40) = iVar1;

        // Clear counter at offset 0x24
        *(undefined4*)(iVar7 + 0x24) = 0;

        uVar5 = (undefined3)((uint)iVar7 >> 8); // For return value encoding

        if (bVar2) // If value >= threshold, compute interpolation
        {
            fVar10 = DAT_00e2b1a4 / *(float*)(iVar7 + 0x08);
            fVar9 = DAT_00e2b1a4 - *(float*)(iVar7 + 0x3c);
            fVar3 = (float)iVar1;
            *(float*)(iVar7 + 0x30) = (DAT_00e2b1a4 - *(float*)(iVar7 + 0x38)) * fVar10;
            *(float*)(iVar7 + 0x34) = fVar9 * fVar10;
            if (iVar1 < 0)
            {
                fVar3 = fVar3 + DAT_00e44578;
            }
            fVar3 = DAT_00e4459c - fVar3;
            *(undefined1*)(iVar7 + 0x23) = 0;
            *(undefined1*)(iVar7 + 0x22) = 1;
            *(float*)(iVar7 + 0x48) = fVar3 * fVar10;
            return CONCAT31(uVar5, 1); // Success with slot base encoded
        }
        // Otherwise, zero out interpolation
        *(undefined4*)(iVar7 + 0x30) = 0;
        *(undefined4*)(iVar7 + 0x34) = 0;
        *(undefined4*)(iVar7 + 0x48) = 0;
        *(undefined1*)(iVar7 + 0x23) = 0;
        *(undefined1*)(iVar7 + 0x22) = 1;
        uVar4 = CONCAT31(uVar5, 1);
    }
    return uVar4;
}