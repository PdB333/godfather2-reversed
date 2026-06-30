// FUNC_NAME: GhostSlotAllocator::allocateGhostSlot
void __thiscall GhostSlotAllocator::allocateGhostSlot(int iSlotId, int* pAdjacencyData, bool bMarkBit)
{
    // Store the last allocated slot ID (this->lastAllocatedSlot at +0x00)
    this->lastAllocatedSlot = iSlotId;

    // Check if slot is valid and currently free (this->slotPointers at +0x08)
    if (iSlotId >= 0 && this->slotPointers[iSlotId] == nullptr)
    {
        // Allocate a new ghost object for this slot (function at 0x00582470)
        GhostObject* pGhost = GhostSlotAllocator::createGhost(this->maxSlots);
        this->slotPointers[iSlotId] = pGhost;

        if (bMarkBit)
        {
            // Mark the bit for this slot in the ghost's own bitmap
            // Ghost object's bitmap pointer is its first field (offset +0x00)
            uint* pBitmapWord = (uint*)(pGhost->bitmap + (iSlotId >> 5) * 4);
            *pBitmapWord |= (1 << (iSlotId & 0x1f));
        }

        // Propagate marks to all dependent slots (iSlotId .. maxSlots-1)
        if (iSlotId < this->maxSlots)
        {
            int iCurSlot = iSlotId;
            int iCurOffset = iSlotId * 0x10; // each slot uses 16 bytes of adjacency data

            do
            {
                int iNeighborId;

                // Retrieve neighbor index from adjacency graph
                // pAdjacencyData structure:
                //   +0x70 : pointer to graph info
                //   +0x74 : short current list index
                short currentListIdx = *(short*)(pAdjacencyData + 0x74);
                if (currentListIdx < 0)
                {
                    iNeighborId = -1;
                }
                else
                {
                    int listIdx = (int)currentListIdx;
                    // graph info structure (pointed by pAdjacencyData[0x70]):
                    //   +0x18 : number of neighbor lists
                    //   +0x1c : pointer to array of list descriptors (each 0x18 bytes)
                    int* graphInfo = *(int**)(pAdjacencyData + 0x70);
                    int listCount = *(int*)(graphInfo + 0x18 / 4); // +0x18
                    int* listArray = *(int**)(graphInfo + 0x1c / 4); // +0x1c

                    // Check bounds
                    if (listIdx >= listCount || iCurSlot < 0 ||
                        *(int*)(listArray + (listIdx * 0x18 + 0x8) / 4) <= iCurSlot)
                    {
                        iNeighborId = -1;
                    }
                    else
                    {
                        // Each list descriptor at offset +0x0c holds an offset into a flattened neighbor ID array
                        int neighborOffset = *(int*)(listArray + (listIdx * 0x18 + 0xc) / 4);
                        iNeighborId = *(int*)(iCurOffset + neighborOffset);
                    }
                }

                // If the neighbor's bit is already set, or neighbor is the original slot, mark the current slot
                if (((*(uint*)(pGhost->bitmap + (iNeighborId >> 5) * 4) & (1 << (iNeighborId & 0x1f))) != 0) ||
                    (iNeighborId == iSlotId))
                {
                    uint* pBitmapWord = (uint*)(pGhost->bitmap + (iCurSlot >> 5) * 4);
                    *pBitmapWord |= (1 << (iCurSlot & 0x1f));
                }

                iCurSlot++;
                iCurOffset += 0x10;
            } while (iCurSlot < this->maxSlots);
        }
    }
}