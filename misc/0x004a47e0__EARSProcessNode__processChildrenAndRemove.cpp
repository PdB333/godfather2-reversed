// FUNC_NAME: EARSProcessNode::processChildrenAndRemove
void __fastcall EARSProcessNode::processChildrenAndRemove(EARSProcessNode* this)
{
    // Process 8-byte children (e.g., simple sub-objects)
    if ((this->m_processControlFlags & 0x10) != 0 && this->m_8byteChildCount != 0)
    {
        uint32_t index = 0;
        do {
            // Each 8-byte child: first 4 bytes = pointer, next 4 bytes = flags
            uint32_t childFlags = *(uint32_t*)(this->m_8byteChildArray + 4 + index * 8);
            if ((childFlags & 0x10) != 0)
            {
                // Call virtual method at vtable+0x30 on the child object
                ObjectBase* child = *(ObjectBase**)(this->m_8byteChildArray + index * 8);
                child->vtable->method_0x30(child);
            }
            index++;
        } while (index < this->m_8byteChildCount);
    }

    // Process 16-byte children (e.g., more complex sub-objects)
    if ((this->m_processControlFlags & 0x80) != 0)
    {
        // Get some manager/state via virtual call
        void* manager = this->m_pSomeManager->vtable->method_0x20(this->m_pSomeManager);
        int8_t managerState = *(int8_t (__fastcall**)(void*))(*(void**)manager + 0x4c)(manager);

        uint32_t index = 0;
        if (this->m_16byteChildCount != 0)
        {
            int32_t offset = 0;
            do {
                uint16_t childFlags = *(uint16_t*)(this->m_16byteChildArray + 4 + offset);
                // Condition: child active (flag 0x10) AND (manager state set OR flag 0x02 in extra byte OR child not flagged 0x20)
                bool condition = (childFlags & 0x10) != 0 &&
                    (managerState != 0 || (this->m_extraControlFlags & 0x02) != 0 || (childFlags & 0x20) == 0);
                if (condition)
                {
                    ObjectBase* child = *(ObjectBase**)(this->m_16byteChildArray + offset);
                    child->vtable->method_0x30(child);
                }
                index++;
                offset += 0x10;
            } while (index < this->m_16byteChildCount);
        }
    }

    // Process bitmask-indexed children (e.g., special objects with dedicated slots)
    if ((this->m_processControlFlags & 0x40) != 0)
    {
        uint32_t maskLow = this->m_childBitmaskLow;
        uint32_t maskHigh = this->m_childBitmaskHigh;
        if (maskLow != 0 || maskHigh != 0)
        {
            do {
                uint64_t mask = ((uint64_t)maskHigh << 32) | maskLow;
                // Isolate lowest set bit using De Bruijn multiplication
                uint64_t isolated = mask & -mask;  // mask & (~mask + 1)
                // De Bruijn sequence for 64-bit: constant 0x3f79d71b4cb0a89UL
                // But the code uses 32-bit decomposition; replicate original logic:
                // Actually the code: __allmul(-low & low, -(high + (low!=0)) & high, 0xb4cb0a89, 0x3f79d71)
                // This yields a 64-bit value whose high bits contain the bit index after shifting.
                // For clarity, we use standard approach:
                int bitIndex = __builtin_ctzll(mask);  // or use De Bruijn lookup
                // Access child pointer via lookup table
                ObjectBase* child = this->m_bitmaskChildrenArray[bitIndex];
                child->vtable->method_0x30(child);
                // Clear the lowest set bit
                uint64_t cleared = mask & (mask - 1);
                maskLow = (uint32_t)cleared;
                maskHigh = (uint32_t)(cleared >> 32);
            } while (maskLow != 0 || maskHigh != 0);
        }
    }

    // Unlink this node from the global doubly-linked list
    if (this->m_prev != nullptr)
    {
        this->m_prev->m_next = this->m_next;
    }
    if (this->m_next != nullptr)
    {
        this->m_next->m_prev = this->m_prev;
    }

    // Update global head/tail if necessary
    if (g_activeListHead == this)
    {
        g_activeListHead = this->m_next;
    }
    bool wasTail = (g_activeListTail == this);
    this->m_next = nullptr;
    if (wasTail)
    {
        g_activeListTail = this->m_prev;
    }
    this->m_prev = nullptr;
}