// FUNC_NAME: Entity::readPropertiesFromStream
void __thiscall Entity::readPropertiesFromStream(int thisPtr, undefined4 stream)
{
    undefined4 *puVar1;
    undefined4 **ppuVar2;
    uint uVar3;
    bool bVar4;
    undefined4 uVar5;
    char local_f0[4];                // isCompact (boolean)
    int local_ec;                    // bitmask pointer
    undefined4 *local_e8;            // current data pointer in compact mode
    uint local_e4;                   // index
    uint local_e0;                   // count
    undefined4 *local_dc;            // current item (pointer format)
    undefined2 local_d8;             // short index (compact)
    undefined4 local_d4;             // data value?
    undefined4 local_d0;             // float component 1
    undefined4 local_cc;             // float component 2
    undefined4 local_c8;             // float component 3
    undefined4 local_c4;             // unused?
    undefined4 local_b4;             // some constant from DAT_00e2b1a4
    undefined4 **local_94;           // current node pointer in pointer mode
    char local_78;                   // temp for bool?
    int local_6c;                    // count (compact) ?
    int local_68;                    // index limit (compact) ?
    int *local_1c;                   // list head pointer?

    // Read beginning-of-object marker (hash 0xb390b11a)
    FUN_0043aff0(stream, 0xb390b11a);
    FUN_0043af00(1);                 // set read bit order to little-endian?

    // Determine iteration mode: compact (bitfield) or pointer (linked list)
    if (local_78 == '\0') {
        bVar4 = *local_1c == 0;     // pointer list: check if head is null
    } else {
        bVar4 = local_6c == local_68; // compact list: check if indices exhausted
    }

    if (!bVar4) {
        // Read initial 4-float vector (presumably position or orientation)
        uVar5 = 0;
        local_e4 = 0;
        local_d4 = 0;
        local_c4 = 0;
        local_b4 = DAT_00e2b1a4;     // some constant, maybe default value
        FUN_0043ac60(local_f0);      // read compact flag and initialize iteration state
        thisPtr[0x50/4] = local_d0;  // +0x50
        thisPtr[0x54/4] = local_cc;  // +0x54
        thisPtr[0x58/4] = local_c8;  // +0x58
        thisPtr[0x5c/4] = uVar5;     // +0x5c (probably w component)
    }

    thisPtr[0x68/4] = thisPtr[0x68/4] & 0x7fffffff; // Clear sign bit on pointer

    // Read end-of-object marker (hash 0x531ded0)
    FUN_0043aff0(stream, 0x531ded0);

    uVar3 = local_e4;                // start index from where we left off

    // Iterate over properties in the list
    while(true) {
        // Check if we've reached the end of the list
        if (local_f0[0] == '\0') {
            bVar4 = *local_94 == (undefined4 *)0x0; // null terminator in pointer list
        } else {
            bVar4 = uVar3 == local_e0;              // index out of range in compact list
        }
        if (bVar4) break;

        // Determine current item structure: pointer vs compact
        ppuVar2 = &local_dc;
        if (local_f0[0] == '\0') {
            ppuVar2 = local_94;        // pointer mode: item node address
        }

        // Read property type ID: check offset 6 of the item header
        if (*(short *)((int)ppuVar2 + 6) == 0x25e3) {
            // Tag matches 0x25e3; read value as a 16-bit offset?
            puVar1 = (undefined4 *)(uint)*(ushort *)(ppuVar2 + 1);
        } else {
            puVar1 = ppuVar2[1];        // otherwise next field is the value pointer
        }

        // Assign based on property type ID
        if (puVar1 == (undefined4 *)0x0) {
            // Type 0: set pointer at offset +0x60
            ppuVar2 = &local_dc;
            if (local_f0[0] == '\0') {
                ppuVar2 = local_94;
            }
            thisPtr[0x60/4] = ppuVar2[2];
        }
        else if (puVar1 == (undefined4 *)0x1) {
            // Type 1: set pointer at offset +0x64 (100 = 0x64)
            ppuVar2 = &local_dc;
            if (local_f0[0] == '\0') {
                ppuVar2 = local_94;
            }
            thisPtr[0x64/4] = ppuVar2[2];
        }
        else if (puVar1 == (undefined4 *)0x2) {
            // Type 2: set pointer at offset +0x68
            ppuVar2 = &local_dc;
            if (local_f0[0] == '\0') {
                ppuVar2 = local_94;
            }
            thisPtr[0x68/4] = ppuVar2[2];
        }

        // Advance to the next item in the list
        if (local_f0[0] == '\0') {
            // Pointer mode: follow the linked list
            if ((int)uVar3 < 0) {
                local_94 = (undefined4 **)((int)local_94 + (int)*local_94); // skip nodes?
                FUN_0043b140();
                uVar3 = local_e4;
            }
            else if ((int)uVar3 < (int)(local_e0 - 1)) {
                local_94 = (undefined4 **)((int)local_94 + (int)*local_94);
                local_e4 = uVar3 + 1;
                uVar3 = local_e4;
            }
            else {
                local_94 = (undefined4 **)&DAT_01163cf8; // sentinel address
                local_94 = (undefined4 **)&DAT_01163cf8;
            }
        }
        else {
            // Compact mode: advance index and read next item from bitmask
            local_e4 = uVar3 + 1;
            uVar3 = local_e4;
            if (local_e4 != local_e0) {
                local_d8 = (short)local_e4;
                // Check bit in bitmask to see if property exists
                if ((*(byte *)((local_e4 >> 3) + local_ec) & (byte)(1 << ((byte)local_e4 & 7))) == 0) {
                    // Bit not set: read actual data from the packed stream
                    local_dc = local_e8;
                    local_d4 = *local_e8;
                    local_e8 = local_e8 + 1;
                } else {
                    // Bit set: property is absent, set null
                    local_dc = (undefined4 *)0x0;
                    local_d4 = 0;
                }
            }
        }
    }
    return;
}