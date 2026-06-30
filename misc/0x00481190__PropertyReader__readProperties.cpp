// FUNC_NAME: PropertyReader::readProperties
void __thiscall PropertyReader::readProperties(void* thisObj, undefined4 streamHandle) {
    // 0x00481190
    // Deserializes a set of properties from a binary stream.
    // Uses two iteration modes: linked list (flag=0) or bit array (flag non-zero).
    // Calls FUN_0043aff0 (likely deserialization start) and FUN_0043b140 (advance).
    
    int* piVar1;
    undefined4* puVar2;
    undefined4** ppuVar3;
    undefined8* puVar4;
    uint uVar5;
    bool bVar6;
    char useBitArray; // local_64
    int bitArrayPtr; // local_60: pointer to bit mask array
    undefined4* dataArray; // local_5c: pointer to data entries (in bit mode)
    uint currentIndex; // local_58
    uint propertyCount; // local_54
    undefined4* currentEntry; // local_50
    undefined2 bitIndexShort; // local_4c: used for storing index in bit mode
    undefined4 entryHeader; // local_48: first 4 bytes of current entry
    undefined4** listIterator; // local_8: pointer to current node in linked list mode
    
    // Initialize deserialization with a magic cookie
    FUN_0043aff0(streamHandle, 0xc449d5d2);
    
    uVar5 = currentIndex; // initial index from some internal state? Actually assignment ambiguous due to missing init. Assume stack init.
    
    while (true) {
        // Check termination condition
        if (useBitArray == '\0') {
            bVar6 = *listIterator == (undefined4*)0x0; // linked list ends when current node is null
        } else {
            bVar6 = uVar5 == propertyCount; // bit array ends when index reaches count
        }
        if (bVar6) break;
        
        // Determine current property entry pointer
        ppuVar3 = &currentEntry; // default in bit mode
        if (useBitArray == '\0') {
            ppuVar3 = listIterator; // in linked list mode, use the node
        }
        
        // Extract property ID from the entry header
        if (*(short*)((int)ppuVar3 + 6) == 0x25e3) {
            // Magic number indicates property ID stored as a ushort at offset +4 (ppuVar3+1 is 4-byte aligned, treat as ushort)
            puVar2 = (undefined4*)(uint)*(ushort*)(ppuVar3 + 1); // Get 2-byte ID
        } else {
            puVar2 = ppuVar3[1]; // Get 4-byte ID
        }
        
        // Dispatch on property ID
        switch ((uint)puVar2) {
        case 0:
            ppuVar3 = &currentEntry;
            if (useBitArray == '\0') {
                ppuVar3 = listIterator;
            }
            *(undefined4**)((int)thisObj + 0x60) = ppuVar3[2]; // property 0 → field at +0x60
            break;
        case 1:
            ppuVar3 = &currentEntry;
            if (useBitArray == '\0') {
                ppuVar3 = listIterator;
            }
            *(undefined4**)((int)thisObj + 100) = ppuVar3[2]; // property 1 → field at +0x64 (100 dec)
            break;
        case 2:
            ppuVar3 = &currentEntry;
            if (useBitArray == '\0') {
                ppuVar3 = listIterator;
            }
            *(undefined4**)((int)thisObj + 0x68) = ppuVar3[2]; // property 2 → field at +0x68
            break;
        case 4:
            ppuVar3 = &currentEntry;
            if (useBitArray == '\0') {
                ppuVar3 = listIterator;
            }
            *(bool*)((int)thisObj + 0x70) = ppuVar3[2] != (undefined4*)0x0; // property 4 → bool at +0x70
            break;
        }
        
        // Advance to next property
        if (useBitArray == '\0') {
            // Linked list mode: node contains relative offset to next node
            if ((int)uVar5 < 0) {
                listIterator = (undefined4**)((int)listIterator + (int)*listIterator); // follow offset
                FUN_0043b140(); // advance stream
                uVar5 = currentIndex;
            } else if ((int)uVar5 < (int)(propertyCount - 1)) {
                listIterator = (undefined4**)((int)listIterator + (int)*listIterator);
                currentIndex = uVar5 + 1;
                uVar5 = currentIndex;
            } else {
                // Last element, reset iterator to a static sentinel (global)
                listIterator = (undefined4**)0x01163cf8; // DAT_01163cf8
                // second assignment is redundant
            }
        } else {
            // Bit array mode: advance index and fetch next entry if present
            currentIndex = uVar5 + 1;
            uVar5 = currentIndex;
            if (currentIndex != propertyCount) {
                bitIndexShort = (short)currentIndex;
                // Check if bit at currentIndex is set in bit array (byte-aligned)
                if ((*(byte*)((currentIndex >> 3) + bitArrayPtr) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
                    // Bit not set: this property is absent? Actually the entry is the data pointer itself.
                    currentEntry = dataArray;
                    entryHeader = *dataArray;
                    dataArray = dataArray + 1; // consume one entry
                } else {
                    // Bit set: property is marked as default/zero? Set entry to null.
                    currentEntry = (undefined4*)0x0;
                    entryHeader = 0;
                }
            }
        }
    }
    
    // After deserialization, if flag at +0x70 is true, allocate and copy two 8-byte values
    if (*(char*)((int)thisObj + 0x70) != '\0') {
        // At global DAT_01206880+0x14 there is an allocation pointer (stack-like)
        piVar1 = (int*)(DAT_01206880 + 0x14);
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_0110bb70; // set vtable?
        *piVar1 = *piVar1 + 4;
        puVar4 = (undefined8*)((*piVar1 + 0xfU) & 0xfffffff0); // align to 16 bytes
        *piVar1 = (int)puVar4;
        *puVar4 = *(undefined8*)((int)thisObj + 0x60); // copy field at +0x60 (8 bytes)
        puVar4[1] = *(undefined8*)((int)thisObj + 0x68); // copy field at +0x68 (8 bytes)
        *piVar1 = *piVar1 + 0x10; // advance allocation pointer by 16 bytes
    }
    return;
}