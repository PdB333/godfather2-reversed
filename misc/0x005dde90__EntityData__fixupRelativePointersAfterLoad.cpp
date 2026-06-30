// FUNC_NAME: EntityData::fixupRelativePointersAfterLoad
// Address: 0x005dde90
// Role: After loading from data file, converts self-relative offsets to absolute pointers 
// for two linked lists (probably children/siblings). Uses EAX as modifier, returns it with low byte set to 1.

uint __fastcall EntityData::fixupRelativePointersAfterLoad(EntityData* thisPtr)
{
    uint inputEAX; // passed in EAX before call
    uint result;

    // Preserve upper 24 bits of EAX
    result = inputEAX & 0xFFFFFF00;

    // Check type identifier at offset 0x20 (0xF = EntityData? )
    if (thisPtr->typeId == 0xF) 
    {
        // If the "resolved" flag is not set yet (bit 0 of flags at +0x24)
        if ((thisPtr->flags & 1) == 0) 
        {
            // Convert first list head pointer (offset +0x2C) to absolute
            if (thisPtr->list1Head_offset != 0) 
            {
                thisPtr->list1Head_absolute = thisPtr->list1Head_offset + (int)thisPtr;
            }
            // Convert second list head pointer (offset +0x34) to absolute
            if (thisPtr->list2Head_offset != 0) 
            {
                thisPtr->list2Head_absolute = thisPtr->list2Head_offset + (int)thisPtr;
            }

            // Traverse list 1 (linked via next at +0x28 in each node)
            int node1 = (int)thisPtr->list1Head_absolute;
            if ((node1 != 0) && (thisPtr->list1Count != 0)) 
            {
                uint count = 0;
                do 
                {
                    // Convert next pointer in node (at node+0x28) from relative to absolute
                    int* nextRel = (int*)(node1 + 0x28);
                    if (*nextRel != 0) 
                    {
                        *nextRel = *nextRel + node1;
                    }
                    node1 = *nextRel;
                    count++;
                } while (count < thisPtr->list1Count);
            }

            // Traverse list 2 (linked via next at +0x1C in each node)
            uint node2 = (uint)thisPtr->list2Head_absolute;
            if ((node2 != 0) && (thisPtr->list2Count != 0)) 
            {
                uint count = 0;
                do 
                {
                    // Convert next pointer in node (at node+0x1C) from relative to absolute
                    int* nextRel = (int*)(node2 + 0x1C);
                    if (*nextRel != 0) 
                    {
                        *nextRel = *nextRel + node2;
                    }
                    node2 = *nextRel;
                    count++;
                } while (count < thisPtr->list2Count);
            }

            // Mark flags as resolved
            thisPtr->flags |= 1;
        }

        // Return value: preserve high 24 bits of input EAX, set low byte to 1
        result = (inputEAX & 0xFFFFFF00) | 1;
    }

    return result;
}