// FUNC_NAME: NetConnection::buildAckStatusTable
int __fastcall NetConnection::buildAckStatusTable(
    NetConnection* this,
    BitMaskInfo* ackMask,          // param_2 (EDX) – bitmask with count
    int* outTotalCount,           // param_3
    int* outLastSpecialIdx,       // param_4
    int* outSpecialCount,         // param_5
    uint8_t* outStatus,           // param_6 – byte array of size ackMask->count
    void* remoteObj               // param_7 – some remote connection or session object
)
{
    int windowSize = *(int*)((uint32_t)this + 8);   // +0x8 – sequence window size
    int bitCount = ackMask->count;
    int effectiveCount = (bitCount < windowSize) ? bitCount : windowSize;

    // +0x10c in remoteObj points to a "packet window" structure
    int* pWindowInfo = *(int**)((uint32_t)remoteObj + 0x10c);

    int totalFound = 0;
    int specialCount = 0;
    int lastSpecialIdx = 0;

    // If no remote window info or invalid, process only the local ackMask
    if (pWindowInfo == nullptr || *pWindowInfo < 0 ||
        *(int*)(pWindowInfo[2] + *pWindowInfo * 4) == 0)
    {
        uint32_t* pAckBits = ackMask->bits;
        uint32_t bitMask = 1;
        // iterate bits
        for (int i = 0; i < effectiveCount; i++)
        {
            if (!(*pAckBits & bitMask))
            {
                outStatus[i] = 0;
            }
            else
            {
                totalFound++;
                // type array at this+0xc
                int packetType = *(int*)((uint32_t)this + 0xc + i * 4);
                if (packetType == 1)   // reliable
                {
                    specialCount++;
                    lastSpecialIdx = i + 1;
                    outStatus[i] = 2;   // special (reliable and acknowledged)
                }
                else
                {
                    outStatus[i] = 1;   // normal (unreliable)
                }
            }

            // advance bit mask and word pointer
            bitMask <<= 1;
            if (bitMask == 0)
            {
                pAckBits++;
                bitMask = 1;
            }
        }
    }
    else
    {
        // Remote window is valid: also compare with its bitmask for reliable packets
        int remoteIdx = *pWindowInfo;   // current index in remote window
        uint32_t* remoteBits;
        int remoteCount;
        // pWindowInfo[2] is an array of pointers; fetch entry at remoteIdx
        if (remoteIdx < 0)
        {
            remoteBits = nullptr;
            remoteCount = 0;
        }
        else
        {
            uint32_t* pEntry = *(uint32_t**)(pWindowInfo[2] + remoteIdx * 4);
            remoteBits = (uint32_t*)*pEntry;        // +0x0 bitmask
            remoteCount = *(int*)(pEntry + 1);      // +0x4 count
        }

        int effRemoteCount = (effectiveCount < remoteCount) ? effectiveCount : remoteCount;
        uint32_t* pAckBits = ackMask->bits;
        uint32_t localBitMask = 1;
        uint32_t* pRemoteBits = remoteBits;
        uint32_t remoteBitMask = 1;

        for (int i = 0; i < effRemoteCount; i++)
        {
            if (!(*pAckBits & localBitMask))
            {
                outStatus[i] = 0;
            }
            else
            {
                totalFound++;
                int packetType = *(int*)((uint32_t)this + 0xc + i * 4);
                // reliability = 1 AND also present in remote bitmask
                if (packetType == 1 && (*pRemoteBits & remoteBitMask))
                {
                    specialCount++;
                    lastSpecialIdx = i + 1;
                    outStatus[i] = 2;
                }
                else
                {
                    outStatus[i] = 1;
                }
            }

            // advance bit masks and word pointers
            localBitMask <<= 1;
            if (localBitMask == 0)
            {
                pAckBits++;
                localBitMask = 1;
            }
            remoteBitMask <<= 1;
            if (remoteBitMask == 0)
            {
                pRemoteBits++;
                remoteBitMask = 1;
            }
        }
    }

    *outTotalCount = totalFound;
    *outLastSpecialIdx = lastSpecialIdx;
    *outSpecialCount = specialCount;

    // Return value encodes whether all bits up to effectiveCount were accounted for.
    // Upper 24 bits: specialCount, lower 8 bits: flag (all accounted)
    // This mimics the CONCAT31 macro from Ghidra.
    return (specialCount & 0xFFFFFF) | ((specialCount == effectiveCount) << 24);
}