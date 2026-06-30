// FUNC_NAME: SoundControlNode::patchSIDsAndRelink
void __fastcall SoundControlNode::patchSIDsAndRelink(int unused, int startIndex, int* pControlData, int targetIndexA, uint sidB, int targetIndexB, uint sidA, int targetElse)
{
    int currentIndex = startIndex;
    if (currentIndex == -1)
        return;

    do
    {
        int baseControlData = *pControlData;               // base pointer
        int dataOffset = currentIndex * 4;
        uint* pNode = (uint*)(*(int*)(baseControlData + 0xc) + dataOffset); // +0xc: data array pointer
        uint nodeWord = *pNode;

        // Extract the 'next' field (bits 6-23) which stores relative index
        uint storedNext = nodeWord >> 6 & 0x3ffff; // 18 bits
        int nextIndex;
        if (storedNext == 0x1fffe)
        {
            nextIndex = -1;
        }
        else
        {
            // Reconstruct absolute next index via relative offset
            nextIndex = (storedNext - 0x1fffe) + currentIndex;
        }

        // Determine actual node pointer for reading/writing (handle special prefix?)
        uint* pWriteNode;
        if (currentIndex >= 1)
        {
            uint prevNodeWord = pNode[-1];
            // Check a flag in lower 6 bits (type field) of previous node: "$a $ a4A"[prevNodeWord & 0x3f] & 0x80
            // This seems to test whether the previous node's type has the high bit set? Simplification below.
            if ((("$a $ a4A"[prevNodeWord & 0x3f] & 0x80U) == 0))
            {
                pWriteNode = pNode;
            }
            else
            {
                pWriteNode = pNode - 1;
            }
        }
        else
        {
            pWriteNode = pNode;
        }

        uint writeWord = *pWriteNode;
        uint nodeType = writeWord & 0x3f; // bits 0-5

        if (nodeType == 0x18) // 24
        {
            if ((writeWord & 0x7fc0) == 0) // bits 6-12 all zero
            {
                // Use sidA if not 0xff, else extract current sid from bits 15-23
                uint sid = sidA;
                if (sidA == 0xff)
                {
                    sid = (writeWord >> 0xf) & 0x1ff; // 9-bit sid
                }
                // Set upper byte (bits 24-31) to new sid
                *pWriteNode = (writeWord & 0xffffff) | (sid << 0x18);
                int dataArray = *(int*)(*pControlData + 0xc);
                int newNext = targetIndexA;
                // Write new relative next index: (newNext - currentIndex + 0x1fffe) into bits 6-23
                uint relative = (newNext - currentIndex) + 0x1fffe;
                if (relative > 0x1ffff)
                {
                    FUN_00638b80("control structure too long");
                    // trigger debug break
                    ((void(*)(void))0xdead)(); // placeholder for swi(3)
                    return;
                }
                *pNode = (*pNode & 0xffffc0) | (relative << 6);
            }
            else
            {
                // Use sidB if not 0xff, else current sid
                uint sid = sidB;
                if (sidB == 0xff)
                {
                    sid = (writeWord >> 0xf) & 0x1ff;
                }
                *pWriteNode = (writeWord & 0xffffff) | (sid << 0x18);
                int dataArray = *(int*)(*pControlData + 0xc);
                int newNext = targetIndexB;
                uint relative = (newNext - currentIndex) + 0x1fffe;
                if (relative > 0x1ffff)
                {
                    FUN_00638b80("control structure too long");
                    ((void(*)(void))0xdead)();
                    return;
                }
                *pNode = (*pNode & 0xffffc0) | (relative << 6);
            }
        }
        else
        {
            // Non-type-0x18 node: just relink using targetElse
            int newNext = targetElse;
            uint relative = (newNext - currentIndex) + 0x1fffe;
            if (relative > 0x1ffff)
            {
                FUN_00638b80("control structure too long");
                ((void(*)(void))0xdead)();
                return;
            }
            *pNode = (*pNode & 0xffffc0) | (relative << 6);
        }

        currentIndex = nextIndex;
    } while (currentIndex != -1);
}