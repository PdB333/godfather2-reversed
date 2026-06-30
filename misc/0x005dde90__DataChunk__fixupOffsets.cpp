// FUNC_NAME: DataChunk::fixupOffsets
uint __fastcall DataChunk::fixupOffsets(uint baseAddr)
{
    uint result = baseAddr & 0xffffff00;  // Preserve high 24 bits of input
    // +0x20: type/signature (must be 0xf to indicate relocatable data)
    if (*(int*)(this + 0x20) == 0xf)
    {
        // +0x24: flags; bit0 == 0 means offsets have not been fixed up yet
        if ((*(byte*)(this + 0x24) & 1) == 0)
        {
            // +0x2c: pointer to first reloc table (relative offsets)
            if (*(int*)(this + 0x2c) != 0)
            {
                *(int*)(this + 0x2c) += (int)this;  // Convert relative -> absolute
            }
            // +0x34: pointer to second reloc table
            if (*(int*)(this + 0x34) != 0)
            {
                *(int*)(this + 0x34) += (int)this;  // Convert relative -> absolute
            }
            // Fix up first table: each element contains a relative pointer at offset +0x28
            // +0x28 holds the count of elements in this table
            int* cur = *(int**)(this + 0x2c);
            if (cur != 0 && *(int*)(this + 0x28) != 0)
            {
                uint cnt = 0;
                do
                {
                    if (*(int*)(cur + 0x28) != 0)          // +0x28: relative pointer field within each element
                    {
                        *(int*)(cur + 0x28) += (int)cur;  // Convert relative -> absolute
                    }
                    cur = *(int**)(cur + 0x28);            // Move to next element (linked list)
                    cnt++;
                } while (cnt < *(uint*)(this + 0x28));
            }
            // Fix up second table: each element uses relative pointer at offset +0x1c
            // +0x30 holds the count of elements
            int* cur2 = *(int**)(this + 0x34);
            if (cur2 != 0 && *(int*)(this + 0x30) != 0)
            {
                uint cnt2 = 0;
                do
                {
                    if (*(int*)(cur2 + 0x1c) != 0)          // +0x1c: relative pointer field within each element
                    {
                        *(int*)(cur2 + 0x1c) += (int)cur2; // Convert relative -> absolute
                    }
                    cur2 = *(int**)(cur2 + 0x1c);           // Move to next element
                    cnt2++;
                } while (cnt2 < *(uint*)(this + 0x30));
            }
            // Mark as fixed up (bit0 = 1)
            *(uint*)(this + 0x24) |= 1;
        }
        // Return input base with low byte set to 1 indicating relocation succeeded
        result = (baseAddr & 0xffffff00) | 1;
    }
    return result;
}