// FUNC_NAME: ControllerManager::deserializeBindings
void __thiscall ControllerManager::deserializeBindings(int this, void* streamReader)
{
    // +0x84: flags bitmask (bit0: something1, bit1: something2, bit2: something3)
    // +0xB8: array of 12-byte structs (up to 10 entries)
    // Each struct at +0xB8 + i*12:  [int field0 (offset 0), int/string field1 (offset 4), unknown field2 (offset 8)]

    BeginStreamRead(streamReader);
    SetStreamId(streamReader, 0xb965931c); // possibly a CRC or stream identifier

    bool isDone = IsStreamFinished(streamReader);
    while (!isDone)
    {
        ReadNextToken(streamReader); // advances token pointer
        uint commandType = ReadCommandType(streamReader);

        switch (commandType)
        {
        case 0:
        {
            int* pData = ReadDataPointer(streamReader);
            if (*(int*)(pData + 8) == 0) // check if value at +0x8 is zero
            {
                *(uint*)(this + 0x84) &= 0xfffffffe; // clear bit0
            }
            else
            {
                *(uint*)(this + 0x84) |= 1; // set bit0
            }
            break;
        }
        case 1:
        {
            int* pData = ReadDataPointer(streamReader);
            if (*(int*)(pData + 8) == 0)
            {
                *(uint*)(this + 0x84) &= 0xfffffffd; // clear bit1
            }
            else
            {
                *(uint*)(this + 0x84) |= 2; // set bit1
            }
            break;
        }
        case 2:
        {
            int* pData = ReadDataPointer(streamReader);
            if (*(int*)(pData + 8) == 0)
            {
                *(uint*)(this + 0x84) &= 0xfffffffb; // clear bit2
            }
            else
            {
                *(uint*)(this + 0x84) |= 4; // set bit2
            }
            break;
        }
        case 3:
        {
            int* pData = ReadDataPointer(streamReader);
            *(uint*)(this + 0x84) |= *(uint*)(pData + 8); // OR with value
            break;
        }
        default:
        {
            if (commandType > 3)
            {
                uint index = (commandType - 4) >> 1;
                if (index < 10) // max array size at +0xB8
                {
                    int* pEntry = (int*)(this + 0xB8 + index * 12);
                    if ((commandType & 1) == 0)
                    {
                        int* pData = ReadDataPointer(streamReader);
                        *pEntry = *(int*)(pData + 8); // store integer value
                    }
                    else if ((commandType & 1) == 1)
                    {
                        int* pData = ReadDataPointer(streamReader);
                        uint uVar4 = ReadSomething(streamReader); // possibly a string or float
                        CopyBuffer(pEntry + 1, uVar4); // fill second field (offset 4) with data
                    }
                }
            }
            break;
        }
        }
        AdvanceStream(streamReader);
        isDone = IsStreamFinished(streamReader);
    }
    return;
}