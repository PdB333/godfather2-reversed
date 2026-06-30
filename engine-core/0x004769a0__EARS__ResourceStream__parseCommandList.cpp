// FUNC_NAME: EARS::ResourceStream::parseCommandList
void __thiscall EARS::ResourceStream::parseCommandList(int thisObj, int streamData)
{
    // streamData is a pointer to a data block; FUN_0043aff0 copies it with a checksum hash? 
    // 0x5ee8ce40 is likely a magic hash for the resource format.
    FUN_0043aff0(streamData, 0x5ee8ce40);

    // Iterator state: ppuVar4 is a pointer to current node in a linked list
    // local_64 indicates whether we are skipping nodes (1) or not (0)
    // local_54 and local_58 are bounds for a bitmask skip table
    // local_60 is a bitmask pointer
    // local_5c is a pointer to data array
    // local_50 is current node pointer
    // local_4c is current index (short)
    // local_48 is a value from the data array
    // local_8 is the base iterator pointer (ppuVar4)

    undefined4** ppuVar4 = local_8; // starting point from local variable (probably initialized elsewhere)
    // Actually local_8 is used as ppuVar4 in the decompiled code, so we'll treat it as the iterator.

    // The loop is structured as a do-while(true) with a break condition at the top.
    // We'll reimplement with a while(true) and early return.

    while (true) {
        bool bVar7;
        if (local_64 == 0) {
            bVar7 = (*ppuVar4 == (undefined4*)0x0);
        } else {
            bVar7 = (local_58 == local_54);
        }
        if (bVar7) {
            // Termination condition: either we hit a null pointer (non-skip mode) or index == length (skip mode)
            // Before returning, check a global flag and possibly increment a counter
            if ( (*(int*)(thisObj + 0x60) == -1) &&
                 ((**(code**)(*(int*)(thisObj + 0x3c) + 8))(), DAT_012067c4 != 0) &&
                 (FUN_00402080(&DAT_012067c4) == 0) ) {
                _DAT_012067c8++; // global counter
                FUN_004084d0(&DAT_012067c4, 0x8000); // realloc or reset something
            }
            return;
        }

        // Determine current node pointer: local_50 or ppuVar4 depending on skip mode
        undefined4** ppuVar6;
        if (local_64 == 0) {
            ppuVar6 = ppuVar4;
        } else {
            ppuVar6 = &local_50;
        }

        // Read "tag" or "command id" from the node (at offset 6 if short == 0x25e3, else from second dword)
        undefined4* puVar2;
        if (*(short*)((int)ppuVar6 + 6) == 0x25e3) {
            puVar2 = (undefined4*)(uint)*(ushort*)(ppuVar6 + 1);
        } else {
            puVar2 = ppuVar6[1];
        }

        // Switch based on command id (0..4)
        switch ((int)puVar2) {
        case 0:
        {
            // Re-evaluate ppuVar6 pointer (same logic as above)
            if (local_64 == 0) {
                ppuVar6 = ppuVar4;
            } else {
                ppuVar6 = &local_50;
            }
            if (*(short*)((int)ppuVar6 + 6) == 0x25e3) {
                if (*ppuVar6 == (undefined4*)0x0) {
                    ppuVar6 = (undefined4**)&DAT_00e2a89b;
                } else {
                    ppuVar6 = (undefined4**)((int)ppuVar6[2] + (int)*ppuVar6);
                }
            } else {
                ppuVar6 = ppuVar6 + 2;
            }
            int* listPtr = (int*)(thisObj + 0x50);
            // Fall through to case 1's handling? No, it's separate.
            // Actually after setting ppuVar6 and listPtr, it goes to a common block at LAB_00476a44. 
            // We'll replicate that.
            // (Case 0 and case 1 both jump to LAB_00476a44)
            // So we'll combine the common part.
            // But case 0 sets listPtr to thisObj+0x50, case 1 sets to thisObj+0x58.
            // So we need to separate.
            // Actually the decompiled code shows both cases fall through to the same label.
            // We'll implement with a goto for clarity in reconstruction.
            goto LAB_00476a44;
        }
        case 1:
        {
            if (local_64 == 0) {
                ppuVar6 = ppuVar4;
            } else {
                ppuVar6 = &local_50;
            }
            if (*(short*)((int)ppuVar6 + 6) == 0x25e3) {
                if (*ppuVar6 == (undefined4*)0x0) {
                    ppuVar6 = (undefined4**)&DAT_00e2a89b;
                } else {
                    ppuVar6 = (undefined4**)((int)ppuVar6[2] + (int)*ppuVar6);
                }
                int* listPtr = (int*)(thisObj + 0x58);
            } else {
                ppuVar6 = ppuVar6 + 2;
                int* listPtr = (int*)(thisObj + 0x58);
            }
            // Fall through to LAB_00476a44
            // However listPtr is declared inside the if blocks, but it's used outside. 
            // The decompiler shows a single assignment before the label for case 0, but for case 1 it's inside conditionals. 
            // We'll restructure to set listPtr properly.
            // Actually in original, for case 1, listPtr = this+0x58 regardless. So we can set it.
            int* listPtr = (int*)(thisObj + 0x58);
            goto LAB_00476a44;
        }
        case 2:
        {
            if (local_64 == 0) {
                ppuVar6 = ppuVar4;
            } else {
                ppuVar6 = &local_50;
            }
            unsigned int val = FUN_00442170(ppuVar6[2]); // probably string to int
            *(int*)(thisObj + 0x60) = val;
            break;
        }
        case 3:
        {
            if (local_64 == 0) {
                ppuVar6 = ppuVar4;
            } else {
                ppuVar6 = &local_50;
            }
            *(undefined4**)(thisObj + 0x64) = ppuVar6[2];
            break;
        }
        case 4:
        {
            if (local_64 == 0) {
                ppuVar6 = ppuVar4;
            } else {
                ppuVar6 = &local_50;
            }
            *(undefined4**)(thisObj + 0x68) = ppuVar6[2];
            break;
        }
        }

        // Common code for cases 0 and 1 (LAB_00476a44)
        {
            // The label is after the switch, but for case 0 and 1 we jump here.
            // We'll handle via the goto.

            int* listPtr; // needs to be set before jumping
        LAB_00476a44:
            // Call two functions on the list (likely clear and then free)
            FUN_004086d0(listPtr);
            FUN_00408310(listPtr);

            // If the adjusted ppuVar6 is not null and its first byte is non-zero
            if ( (ppuVar6 != (undefined4**)0x0) && (*(char*)ppuVar6 != '\0') ) {
                unsigned int strVal = FUN_004dafd0(ppuVar6); // possibly string to hash or struct
                FUN_00408260(listPtr, strVal); // insert into list
                if (*listPtr != 0) {
                    FUN_00407e60(thisObj + 0x3c, listPtr); // notify handler
                }
            }
            break; // after processing case 0/1, break out of switch
        }
        // After switch, advance the iterator
        if (local_64 == 0) {
            // Non-skip mode: advance ppuVar4 by current node's size (stored at the beginning)
            int advance = (int)*ppuVar4;
            if ((int)local_58 < 0) {
                local_8 = (undefined4**)((int)ppuVar4 + advance);
                FUN_0043b140(); // probably reset something
                ppuVar4 = local_8;
            } else if ((int)local_58 < (int)(local_54 - 1)) {
                local_58++;
                local_8 = (undefined4**)((int)ppuVar4 + advance);
                ppuVar4 = (undefined4**)((int)ppuVar4 + advance);
            } else {
                local_8 = (undefined4**)&DAT_01163cf8;
                ppuVar4 = (undefined4**)&DAT_01163cf8;
            }
        } else {
            // Skip mode: increment index and check bitmask
            local_58++;
            if (local_58 != local_54) {
                local_4c = (short)local_58;
                if ( (*(byte*)( (local_58 >> 3) + local_60 ) & (1 << (local_58 & 7))) == 0) {
                    local_48 = *local_5c;
                    local_50 = local_5c;
                    local_5c++;
                } else {
                    local_50 = (undefined4*)0x0;
                    local_48 = 0;
                }
            }
        }
    } // end while(true)
}