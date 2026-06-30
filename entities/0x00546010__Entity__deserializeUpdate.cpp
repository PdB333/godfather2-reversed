// FUNC_NAME: Entity::deserializeUpdate
void Entity::deserializeUpdate()
{
    // Scope marker for profiling? (FUN_0043aff0 with magic 0x197c1972)
    FUN_0043aff0(__eax, 0x197c1972);

    bool bModified = false;
    uint32_t* ppvStream = m_pStreamCurrent;      // +0x??, local_1c
    uint32_t uOffset = m_uStreamOffset;           // local_6c
    uint32_t uBitmaskSize = m_uBitmaskSize;       // local_68
    uint8_t* pBitmask = m_pBitmask;               // local_74
    uint32_t* pCurrent = m_pCurrent;               // local_70
    uint32_t* pPlainCurrent = m_pPlain;             // local_64
    uint8_t bIsCompressed = m_bIsCompressed;       // local_78

    do {
        bool bContinue;
        if (bIsCompressed == 0) {
            // Plain mode: linked list of command headers
            bContinue = (*ppvStream != 0);
        } else {
            // Bitmask compressed mode: index-based
            bContinue = (uOffset != uBitmaskSize);
        }
        if (!bContinue) {
            if (bModified) {
                FUN_005467e0(); // Notify system of changes
            }
            return;
        }

        // Extract the command type
        uint32_t* pCmdBlock;
        if (bIsCompressed == 0) {
            pCmdBlock = ppvStream;
        } else {
            pCmdBlock = &pCurrent; // actually pCurrent points to block?
        }

        // Determine command opcode
        uint32_t* pOpcode;
        if (*(short*)((int)pCmdBlock + 6) == 0x25e3) {
            // Magic sentinel: inline short value
            pOpcode = (uint32_t*)(uint16_t)(pCmdBlock[1] & 0xFFFF);
        } else {
            pOpcode = pCmdBlock[1]; // Direct pointer/offset
        }

        switch((int)pOpcode) {
            case 0: // Modified flag
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                if (*(char*)(pBlock + 2) != 0) {
                    bModified = true;
                }
                break;
            }
            case 1: // No-op
                break;
            case 2: // Set field at objectA+0x84
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x2e8) + 0x84) = pBlock[2];
                goto setField84;
            }
            case 3: // Set field at objectA+0x88
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x2e8) + 0x88) = pBlock[2];
                break;
            }
            case 4: // Set field at objectB+0x80
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x368) + 0x80) = pBlock[2];
                break;
            }
            case 5: // Set field at objectB+0x60
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x368) + 0x60) = pBlock[2];
                break;
            }
            case 6: // Set field at objectB+0x64
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x368) + 0x64) = pBlock[2];
                break;
            }
            case 7: // Set field at objectB+0x68
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x368) + 0x68) = pBlock[2];
                break;
            }
            case 8: // Set field at objectB+0x6C
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x368) + 0x6C) = pBlock[2];
                break;
            }
            case 9: // Set field at objectB+0x70
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                *(uint32_t*)(*(int*)(this + 0x368) + 0x70) = pBlock[2];
                break;
            }
            case 0xa: // Set field at objectB+0x84 (shared label with case 2)
            {
                uint32_t* pBlock = (bIsCompressed == 0) ? ppvStream : &pCurrent;
                int iTemp = *(int*)(this + 0x368);
            setField84:
                *(uint32_t*)(iTemp + 0x84) = pBlock[2];
                break;
            }
        }

        // Move to next command
        if (bIsCompressed == 0) {
            // Plain mode: linked list, advance by header size
            if ((int)uOffset < 0) {
                // Negative offset means reset stream? (unlikely)
                ppvStream = (uint32_t*)((int)ppvStream + (int)*ppvStream);
                FUN_0043b140(); // Some helper to skip?
                ppvStream = m_pStreamCurrent; // local_1c
                uOffset = m_uStreamOffset;     // local_6c
            } else if ((int)uOffset < (int)(uBitmaskSize - 1)) {
                // Advance one header
                uOffset++;
                m_uStreamOffset = uOffset;
                ppvStream = (uint32_t*)((int)ppvStream + (int)*ppvStream);
                ppvStream = (uint32_t*)((int)ppvStream + (int)*ppvStream);
                uOffset = m_uStreamOffset;
            } else {
                // End of list
                ppvStream = (uint32_t*)0x01163cf8; // End marker global
                m_pStreamCurrent = ppvStream;
            }
        } else {
            // Compressed mode: index through bitmask
            uOffset++;
            m_uStreamOffset = uOffset;
            if (uOffset != uBitmaskSize) {
                uint16_t index = (uint16_t)uOffset;
                if ((*(uint8_t*)(pBitmask + (uOffset >> 3)) & (1 << (uOffset & 7))) == 0) {
                    // Bit clear: read actual data
                    pCurrent = *pPlainCurrent;
                    m_pCurrent = pCurrent;
                    pPlainCurrent++;
                } else {
                    // Bit set: data omitted (use default)
                    pCurrent = 0;
                    m_pCurrent = 0;
                }
            }
        }
    } while (true);
}