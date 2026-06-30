// FUNC_NAME: DataDeserializer::readPropertyArray
void DataDeserializer::readPropertyArray(uint32_t hash, DataStream* stream)
{
    // hash is a CRC or type identifier (0x1464034a)
    FUN_0043aff0(hash, 0x1464034a); // likely context setup

    while (true) {
        bool done;
        if (!isBitmaskEncoded) {
            done = (ppuStack_8 == nullptr);
        } else {
            done = (uStack_58 == uStack_54);
        }
        if (done) break;

        undefined4** elementPtr;
        if (isBitmaskEncoded) {
            elementPtr = &puStack_50;
        } else {
            elementPtr = ppuStack_8;
        }

        uint32_t type;
        if (*(short*)((int)elementPtr + 6) == 0x25e3) {
            type = (uint32_t)*(ushort*)(elementPtr + 1);
        } else {
            type = (uint32_t)elementPtr[1];
        }

        switch (type) {
        case 0: // write array of 4 consecutive pointers (offset 0)
        {
            uint32_t count = stream->getCount(0);
            uint32_t processed = 0;
            if (count > 3) {
                int i = 0;
                int iterations = ((count - 4) >> 2) + 1;
                processed = iterations * 4;
                do {
                    // write 4 pointers at offsets 0, 0xc, 0x18, 0x24 relative to base
                    *(uint32_t*)(basePtr + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0xc + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x18 + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x24 + i) = getElement(elementPtr);
                    i += 0x30;
                    iterations--;
                } while (iterations != 0);
            }
            if (processed < count) {
                int i = processed * 0xc;
                int remaining = count - processed;
                do {
                    *(uint32_t*)(basePtr + i) = getElement(elementPtr);
                    i += 0xc;
                    remaining--;
                } while (remaining != 0);
            }
            break;
        }
        case 1: // write array of 4 consecutive pointers (offset 0, with range)
        {
            uint32_t start = stream->getCount(0);
            uint32_t end = stream->getTotal(0);
            if ((end - start) > 3) {
                int i = start * 0xc;
                int iterations = ((end - start - 4) >> 2) + 1;
                uint32_t newStart = start + iterations * 4;
                do {
                    *(uint32_t*)(basePtr + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0xc + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x18 + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x24 + i) = getElement(elementPtr);
                    i += 0x30;
                    iterations--;
                } while (iterations != 0);
                start = newStart;
            }
            if (start < end) {
                int i = start * 0xc;
                int remaining = end - start;
                do {
                    *(uint32_t*)(basePtr + i) = getElement(elementPtr);
                    i += 0xc;
                    remaining--;
                } while (remaining != 0);
            }
            break;
        }
        case 2: // write array of 4 consecutive pointers (offset 4)
        {
            uint32_t count = stream->getCount(0);
            uint32_t processed = 0;
            if (count > 3) {
                int i = 0;
                int iterations = ((count - 4) >> 2) + 1;
                processed = iterations * 4;
                do {
                    *(uint32_t*)(basePtr + 4 + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x10 + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x1c + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x28 + i) = getElement(elementPtr);
                    i += 0x30;
                    iterations--;
                } while (iterations != 0);
            }
            if (processed < count) {
                int i = processed * 0xc;
                int remaining = count - processed;
                do {
                    *(uint32_t*)(basePtr + 4 + i) = getElement(elementPtr);
                    i += 0xc;
                    remaining--;
                } while (remaining != 0);
            }
            break;
        }
        case 3: // write array of 4 consecutive pointers (offset 4, with range)
        {
            uint32_t start = stream->getCount(0);
            uint32_t end = stream->getTotal(0);
            if ((end - start) > 3) {
                int i = start * 0xc;
                int iterations = ((end - start - 4) >> 2) + 1;
                uint32_t newStart = start + iterations * 4;
                do {
                    *(uint32_t*)(basePtr + 4 + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x10 + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x1c + i) = getElement(elementPtr);
                    *(uint32_t*)(basePtr + 0x28 + i) = getElement(elementPtr);
                    i += 0x30;
                    iterations--;
                } while (iterations != 0);
                start = newStart;
            }
            if (start < end) {
                int i = start * 0xc;
                int remaining = end - start;
                do {
                    *(uint32_t*)(basePtr + 4 + i) = getElement(elementPtr);
                    i += 0xc;
                    remaining--;
                } while (remaining != 0);
            }
            break;
        }
        case 4: // single pointer at offset 0x14
        {
            *(uint32_t*)(destObj + 0x14) = getElement(elementPtr);
            break;
        }
        case 5: // set bool array (offset +8 from base)
        {
            uint32_t value = (uint32_t)getElement(elementPtr);
            uint32_t count = stream->getCount(0);
            if (count != 0) {
                int i = 0;
                do {
                    *(bool*)(basePtr + 8 + i) = (value != 0);
                    i += 0xc;
                    count--;
                } while (count != 0);
            }
            break;
        }
        case 6: // set bool array over range (offset +8 from base)
        {
            uint32_t value = (uint32_t)getElement(elementPtr);
            uint32_t start = stream->getCount(0);
            uint32_t end = stream->getTotal(0);
            if (start < end) {
                int i = start * 0xc;
                int remaining = end - start;
                do {
                    *(bool*)(basePtr + 8 + i) = (value != 0);
                    i += 0xc;
                    remaining--;
                } while (remaining != 0);
            }
            break;
        }
        } // end switch

        // Advance the iterator
        if (isBitmaskEncoded) {
            // Bitmask encoded: decode next index from bitmask
            currentIndex++;
            if (currentIndex != totalCount) {
                bitmaskIndex = (short)currentIndex;
                // Check if this index is present in bitmask
                if ((bitmask[(currentIndex >> 3)] & (1 << (currentIndex & 7))) == 0) {
                    // Index not present, skip data
                    currentData = dataPointer; // data is zero
                    dataPointer++; // but not used
                } else {
                    currentData = nullptr;
                    // Actually data is present, keep currentData from earlier assignment
                }
            }
        } else {
            // Flat list: handle skip if index < 0?
            if ((int)currentIndex < 0) {
                ppuStack_8 = (undefined4**)((int)ppuStack_8 + (int)*ppuStack_8);
                FUN_0043b140(); // likely error or skip
            } else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentIndex++;
                ppuStack_8 = (undefined4**)((int)ppuStack_8 + (int)*ppuStack_8);
            } else {
                ppuStack_8 = (undefined4**)0x01163cf8; // sentinel end marker
            }
        }
    }
}