// FUNC_NAME: TNLConnection::processAckAndClassifySlots
class TNLConnection {
public:
    // Fields assumed based on offsets:
    // +0x08: int mPacketCount;
    // +0x0C: SomeStruct* mPacketInfo; // structure with array at +0x0C
    // +0x0C->+0x0C: int* mReliabilityFlags; // array of ints per packet slot

    // Structure for ack mask info (param_2)
    struct AckMaskInfo {
        uint* mask;   // bitmask array
        int   count; // number of bits
    };

    // Structure for sent packet data (from connection object at param_7+0x10C)
    struct SentPacketData {
        int   baseIndex; // some index, negative if invalid
        int   field_4;   // unused?
        uint* maskArray; // pointer to bitmask array (size unknown)
    };

    /**
     * Process acknowledgment bitmask and classify each slot.
     * 
     * @param ackMask    The remote ack mask structure.
     * @param outTotalNew   Output: total number of new packets.
     * @param outLastNewIndex Output: 1-based index of last new packet (0 if none).
     * @param outDupCount   Output: count of duplicate (reliable already sent) packets.
     * @param outSlotStatus Output: array of bytes, one per slot: 0=not acked, 1=acked new, 2=acked duplicate.
     * @param conn         Connection object containing sent packet data at +0x10C.
     * 
     * @return Packed result: low byte=1 if all processed slots are duplicates, high 24 bits=0.
     */
    uint __fastcall processAckAndClassifySlots(AckMaskInfo* ackMask, int* outTotalNew, int* outLastNewIndex, int* outDupCount, char* outSlotStatus, TNLConnection* conn) {
        int maxSlots = this->mPacketCount;
        if (ackMask->count < maxSlots) {
            maxSlots = ackMask->count;
        }

        SentPacketData* sentData = *reinterpret_cast<SentPacketData**>(reinterpret_cast<char*>(conn) + 0x10C);
        int totalNew = 0;
        int lastNewIndex = 0;
        int dupCount = 0;
        int processed = maxSlots; // actual number of slots processed (may differ in duplicate check)

        if (sentData == nullptr || sentData->baseIndex < 0 || sentData->maskArray[sentData->baseIndex] == 0) {
            // No sent packet data available -> no duplicate detection possible
            uint* ackMaskPtr = ackMask->mask;
            uint maskBit = 1;
            for (int slot = 0; slot < maxSlots; ++slot) {
                if (!((*ackMaskPtr) & maskBit)) {
                    outSlotStatus[slot] = 0;
                } else {
                    ++totalNew;
                    if (this->mPacketInfo->reliabilityFlags[slot] == 1) {
                        ++dupCount; // treat as "new reliable" for counting
                        lastNewIndex = slot + 1;
                        outSlotStatus[slot] = 2; // treat as duplicate? Actually no dup check -> mark as 2? In original it marks 2 when reliability==1
                    } else {
                        outSlotStatus[slot] = 1;
                    }
                }
                maskBit <<= 1;
                if (maskBit == 0) {
                    maskBit = 1;
                    ++ackMaskPtr;
                }
            }
        } else {
            if (sentData->baseIndex < 0) {
                // invalid index, treat as no mask
            }
            uint* sentMaskPtr = sentData->maskArray[sentData->baseIndex]; // Actually need to dereference correctly
            uint* ackMaskPtr = ackMask->mask;
            uint maskBit = 1;
            uint sentBit = 1;
            processed = min(maxSlots, static_cast<int>(sentData->field_4)); // from puVar1[1]
            int slot = 0;
            while (slot < processed) {
                if (!((*ackMaskPtr) & maskBit)) {
                    outSlotStatus[slot] = 0;
                } else {
                    ++totalNew;
                    if ((this->mPacketInfo->reliabilityFlags[slot] == 1) && ((*sentMaskPtr) & sentBit)) {
                        ++dupCount;
                        lastNewIndex = slot + 1;
                        outSlotStatus[slot] = 2;
                    } else {
                        outSlotStatus[slot] = 1;
                    }
                }
                ++slot;
                maskBit <<= 1;
                if (maskBit == 0) {
                    maskBit = 1;
                    ++ackMaskPtr;
                }
                sentBit <<= 1;
                if (sentBit == 0) {
                    sentBit = 1;
                    ++sentMaskPtr;
                }
            }
        }

        *outTotalNew = totalNew;
        *outLastNewIndex = lastNewIndex;
        *outDupCount = dupCount;

        // Return packed value: low byte = (dupCount == processed) ? 1 : 0
        return static_cast<uint>(dupCount == processed) | (static_cast<uint>(dupCount) >> 8) << 24;
    }
};