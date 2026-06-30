// FUNC_NAME: GhostConnection::processGhostAck
// Address: 0x00579690
// This function appears to process ghost acknowledgements in the TNL layer.
// It searches for a specific ghost ID (targetId) across network slots and updates the local ghost array.
// The function returns 1 if the ack was processed, 0 if not found.

int GhostConnection::processGhostAck(int *someManager, int targetId)
{
    int maxSlots = getSlotCount();  // FUN_00579170() - returns number of slots (e.g., 32 for packet window)
    int currentIndex = 0;
    int foundSlot = -1;

    // First pass: search for the targetId in incoming slots
    if (maxSlots > 0)
    {
        // Initial hash/index using manager fields (round-robin)
        int hashIndex = *(int *)(someManager + 0x2E8) + *(int *)(someManager + 0x2E4);

        do
        {
            // Compute slot offset: 0xE0 = 224 bytes per slot
            int slotOffset = (hashIndex % *(int *)(someManager + 0x2E4)) * 0xE0;
            int *slotPtr = (int *)(slotOffset + 0x84 + *(int *)(someManager + 0x2EC));

            // Check slot validity: must have flag 0x20 set at +0xB0, count at +0x84 >= 3, and non-null list at +0xC0
            if (((*(byte *)(slotOffset + 0xB0 + *(int *)(someManager + 0x2EC)) & 0x20) == 0) ||
                (*slotPtr < 3) ||
                (*(int **)(slotPtr + 0xF) == (int *)0x0))
            {
                break; // Invalid slot, stop scanning
            }

            // slotPtr now points to the list header; grab the pointer at +0xC0 -> +0xF*4
            int *listHeader = *(int **)(slotPtr + 0xF);
            int entryCount = *listHeader;
            int *entryArray = (int *)listHeader[1]; // Each entry is 12 bytes (3 ints)

            // Search entries for the targetId (stored at offset 8 in entry)
            int entryIndex = 0;
            if (entryCount > 0)
            {
                do
                {
                    if (*(int *)(entryArray + 2) == targetId) // entry->id at offset 8
                    {
                        // Compute local slot from this->fields (+0xB9, +0xBA, +0xBB)
                        int localSlot = (((this->field_0xBA - currentIndex) + this->field_0xB9) % this->field_0xB9) * 0xE0 + this->field_0xBB;

                        // Check if local slot is free (byte at +0x70 == 0) or has different id (+0x14)
                        if (*(char *)(localSlot + 0x70) == '\0' ||
                            *(int *)(localSlot + 0x14) != *(int *)(entryArray + 2))
                        {
                            // Found a slot to replace
                            targetId = *(int *)(entryArray + 1); // Use entry->value at offset 4
                            this->someVirtualMethod(targetId); // vtable+4: probably callback
                            foundSlot = currentIndex;
                            goto endSearch;
                        }
                        break; // Slot already occupied with same id? skip
                    }
                    entryIndex++;
                    entryArray += 3; // Advance 12 bytes
                } while (entryIndex < entryCount);
            }

            if (foundSlot == currentIndex)
                break; // Already found? actually condition is "if (local_c != iVar5) break;"

endSearch:
            hashIndex--;
            currentIndex++;
        } while (currentIndex < maxSlots);
    }

    // If we found a matching slot, process reverse updates
    if (foundSlot != -1)
    {
        // Second pass: update all slots from foundSlot down to 0 in reverse order
        int reverseIndex = foundSlot; // Use foundSlot as starting point (likely unaff_EBP)
        if (reverseIndex >= 0)
        {
            do
            {
                // Compute slot offset (reverse order)
                int slotOffset = (((*(int *)(someManager + 0x2E4) - reverseIndex) + *(int *)(someManager + 0x2E8)) %
                                  *(int *)(someManager + 0x2E4)) * 0xE0 + *(int *)(someManager + 0x2EC);

                // Recheck slot validity
                int *slotPtr;
                if (((*(byte *)(slotOffset + 0xB0) & 0x20) == 0) || (*(int *)(slotOffset + 0x84) < 3))
                {
                    slotPtr = (int *)0x0;
                }
                else
                {
                    slotPtr = *(int **)(slotOffset + 0xC0);
                }

                // Search for an entry in the slot's list (maybe using some condition)
                int entryIndex = 0;
                if (slotPtr && *slotPtr > 0)
                {
                    int *entryArray = (int *)slotPtr[1];
                    do
                    {
                        // Compare entry+4 with someManager? This part is unclear.
                        // The decompiled code shows `if (*(int *)(iVar4 + 4) == local_4)` - local_4 is maxSlots? Possibly a different id.
                        // For reconstruction, we replicate the logic.
                        if (*(int *)(entryArray + 1) == maxSlots) // entry->value at offset 4
                        {
                            // Call another function to update the slot
                            FUN_00586c90(this, (int *)(slotOffset + 0x84));

                            // Copy data from incoming slot to local slot
                            int localSlot = ((this->field_0xBA + this->field_0xB9) % this->field_0xB9) * 0xE0 + this->field_0xBB;
                            *(int *)(localSlot + 0x74) = *(int *)(slotOffset + 0x74);
                            *(int *)(localSlot + 0x78) = *(int *)(slotOffset + 0x78);
                            *(int *)(localSlot + 0x7C) = *(int *)(slotOffset + 0x7C);
                            maxSlots = *(int *)(entryArray + 2); // Update maxSlots? Actually overwritten.
                            break;
                        }
                        entryIndex++;
                        entryArray += 3;
                    } while (entryIndex < *slotPtr);
                }
                reverseIndex--;
            } while (reverseIndex >= 0);
        }
        return 1;
    }
    return 0;
}