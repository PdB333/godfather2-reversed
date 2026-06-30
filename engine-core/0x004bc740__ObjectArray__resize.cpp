// FUNC_NAME: ObjectArray::resize
void __thiscall ObjectArray::resize(uint32_t newCount)
{
    uint32_t oldCount = this->count;  // +0x04

    if (oldCount < newCount)
    {
        // Ensure capacity for at least newCount elements (each 0x10 bytes)
        growArray(newCount);  // calls FUN_00407880
        oldCount = this->count;  // reload after potential reallocation (count unchanged by grow)

        if (oldCount < newCount)
        {
            // Zero-initialize the new elements (index oldCount .. newCount-1)
            uint32_t elemOffset = oldCount * 0x10;     // byte offset of first new element
            int32_t numNew = newCount - oldCount;

            do
            {
                uint8_t* pElem = (uint8_t*)(this->data) + elemOffset;  // +0x00
                if (pElem)
                {
                    // Clear all 16 bytes (4 dwords)
                    *(uint32_t*)pElem = 0;
                    *(uint32_t*)(pElem + 4) = 0;
                    *(uint32_t*)(pElem + 8) = 0;
                    *(uint32_t*)(pElem + 12) = 0;
                }
                elemOffset += 0x10;
                numNew--;
            } while (numNew != 0);
        }
    }
    else if (oldCount > newCount)
    {
        // Destroy elements from index newCount to oldCount-1
        int32_t lastIdx = oldCount - 1;
        if ((int32_t)newCount <= lastIdx)
        {
            int32_t elemOffset = lastIdx * 0x10;       // start from last element
            int32_t numToRemove = (lastIdx - newCount) + 1;

            do
            {
                uint8_t* pElem = (uint8_t*)(this->data) + elemOffset;
                // Element structure:
                // +0x00: pointer to an object (to be released)
                // +0x0C: function pointer (destructor/release method)
                void* pObj = *(void**)pElem;           // +0x00
                if (pObj)
                {
                    // Call release function stored at offset 0x0C
                    typedef void (__thiscall *ReleaseFunc)(void*);
                    ReleaseFunc release = *(ReleaseFunc*)(pElem + 0x0C);
                    release(pObj);
                }
                elemOffset -= 0x10;
                numToRemove--;
            } while (numToRemove != 0);
        }
    }
    else
    {
        // same count, nothing to do
        return;
    }

    this->count = newCount;  // +0x04
}