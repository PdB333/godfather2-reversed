// FUNC_NAME: PacketBuffer::trimAcknowledgedEntries
// Function at 0x006289a0: Removes acknowledged or processed entries from a packet buffer based on accumulated sequence numbers.
// This appears to be part of the TNL reliable packet delivery system, trimming the send window when ACKs are received.

void PacketBuffer::trimAcknowledgedEntries(int* buffer) // buffer is a struct (PacketBuffer*) with fields at offsets 0x04 (count) and 0x08 (pointer to array descriptor)
{
    int iVar1;
    int* piVar2;
    int iVar3;
    uint uVar4;
    int iVar5;
    int iVar6;
    uint local_c;
    int local_8;
    int local_4;

    iVar6 = 1; // number of entries to keep (start with 1, incremented as we process)

    if (1 < *(int*)(buffer + 4)) { // if count > 1
        iVar1 = *(int*)(buffer + 8); // pointer to array descriptor (e.g., some kind of circular buffer)
        iVar5 = *(int*)(iVar1 + 8); // pointer to first element? or maybe to data block

        // Determine if the first element is an "acknowledged" type
        if ((int*)(iVar5 + -8) == (int*)0x0) {
            local_c = 0;
        }
        else if (*(int*)(iVar5 - 8) == 4) { // check type field? (4 might indicate a specific packet type)
            local_c = *(uint*)(*(int*)(iVar5 - 4) + 0xc); // get sequence number or timestamp from element
        }
        else {
            iVar3 = FUN_00633990(iVar1); // some validation function
            if (iVar3 == 0) {
                local_c = 0;
            }
            else {
                local_c = *(uint*)(*(int*)(iVar5 - 4) + 0xc);
            }
        }

        iVar5 = -2;                  // start index for backward iteration?
        local_4 = -9999;            // some threshold
        local_8 = -0x13878;         // -79992? window size offset?

        do {
            if (iVar5 < 1) {
                if (iVar5 < -9999) {
                    if (iVar5 == -0x2711) {           // -10001
                        piVar2 = (int*)(iVar1 + 0x40); // special pointer
                    }
                    else if (iVar5 == -10000) {
                        piVar2 = (int*)(*(int*)(iVar1 + 0x10) + 0x2c); // another special
                    }
                    else {
                        iVar3 = *(int*)(*(int*)(iVar1 + 0xc) + -4);
                        if ((int)(uint)*(byte*)(iVar3 + 7) < local_4) {
                            piVar2 = (int*)0x0;
                        }
                        else {
                            piVar2 = (int*)(local_8 + 8 + iVar3);
                        }
                    }
                }
                else {
                    piVar2 = (int*)(*(int*)(iVar1 + 8) + iVar5 * 8); // index into array
                }
LAB_00628ac4:
                if (piVar2 == (int*)0x0) goto LAB_00628a24;
                if (*piVar2 == 4) {
                    uVar4 = *(uint*)(piVar2[1] + 0xc);
                }
                else {
                    iVar3 = FUN_00633990(iVar1);
                    if (iVar3 == 0) goto LAB_00628a24;
                    uVar4 = *(uint*)(piVar2[1] + 0xc);
                }
            }
            else {
                piVar2 = (int*)(*(int*)(iVar1 + 0xc) + -8 + iVar5 * 8);
                if (piVar2 < *(int**)(iVar1 + 8)) goto LAB_00628ac4;
LAB_00628a24:
                uVar4 = 0;
            }

            // if too few remaining entries and current value is <= accumulated, stop
            if (((*(int*)(buffer + 4) - iVar6) + 1 < 10) && (local_c <= uVar4)) break;

            local_c = local_c + uVar4;       // accumulate
            local_8 = local_8 + 8;           // move to next slot
            local_4 = local_4 + 1;           // increment index offset
            iVar6 = iVar6 + 1;               // count the entry we're keeping
            iVar5 = iVar5 + -1;               // move backwards
        } while (iVar6 < *(int*)(buffer + 4));

        FUN_00626460(); // presumably a memory move or list compaction
        *(int*)(buffer + 4) = *(int*)(buffer + 4) + (1 - iVar6); // reduce count by number of removed entries
    }
    return;
}