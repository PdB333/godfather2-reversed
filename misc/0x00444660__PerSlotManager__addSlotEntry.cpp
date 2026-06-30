// FUNC_NAME: PerSlotManager::addSlotEntry  
void __thiscall PerSlotManager::addSlotEntry(void* this, uint slotIndex, int param3)  
{  
    // Check if the parameter is valid and slot index is within range (0-15)  
    if ((param3 != 0) && (slotIndex < 0x10))  
    {  
        // Compute pointer to the slot structure (array of size 0x18 starting at offset 0x14)  
        // Slot structure layout:  
        //   +0x00: unknown? (not used here)  
        //   +0x08: flags (uint)  
        //   +0x0c: pointer to linked list head  
        //   +0x10: unknown? (not used here)  
        int* slotPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x14 + slotIndex * 0x18);  
        if (slotPtr != nullptr)  
        {  
            // Allocate some data (returned as int?)  
            int nodeData = allocateNodeData();  
            if (nodeData != 0)  
            {  
                // Allocate a node structure  
                int* node = reinterpret_cast<int*>(allocateNode());  
                if (node != nullptr)  
                {  
                    // Set the flag bit 0 in the slot  
                    *(reinterpret_cast<uint*>(slotPtr + 2)) |= 1; // +0x08 (since slotPtr is int*, +2 gives offset 8 bytes)  

                    // Link the node into the slot's linked list  
                    // Old head stored at slot+0x0c  
                    *node = *(slotPtr + 3);                     // node[0] = old head pointer  
                    *(slotPtr + 3) = reinterpret_cast<int>(node); // new head = node  

                    // Store the allocated data index  
                    *(node + 4) = nodeData;                     // node[4] = index  

                    // Store a global value  
                    *(node + 2) = g_someGlobalValue;            // node[2] = DAT_01205224  
                }  
            }  
        }  
    }  
}