// FUNC_NAME: PacketFragmenter::sendFragmentedPacket
class PacketFragmenter {
public:
    // Member offsets (relative to this):
    // +0x04: int m_outputOffset;      // current write offset in output buffer
    // +0x08: int m_outputLength;      // length or another offset
    // +0x38: int m_dataSize;          // total data size to send
    // +0x50: char* m_dataBuffer;      // data to fragment
    // +0x650: int m_sequence;         // sequence number (low byte)
    // +0x654: int m_fragmentCount;    // number of fragments (send in chunks)
    // +0x658: Fragment m_fragments[]; // array of packet headers (2 ints per entry)

    struct Fragment {
        int header1;
        int header2;
    };

    // Globals (from data refs)
    extern int DAT_01217d04;                   // default fragment count
    extern void* PTR_LAB_0110a3cc;            // some global context
    extern int DAT_0110a3d0;                  // another global

    // Helper functions (callees)
    void buildPacketFragment(int* outHeader1, int* outHeader2, int combinedSeqSize,
                             char* buffer, int offset, int length,
                             void* context1, int context2); // FUN_00495510
    void sendRawPacket(char* buffer, int sequence, int size); // FUN_004d2ba0

    void sendFragmentedPacket() {
        // Set default fragment count from global
        m_fragmentCount = DAT_01217d04;

        int totalSize = m_dataSize;
        if (totalSize <= 15 || m_fragmentCount == 0) {
            // No splitting needed: send entire buffer as one raw packet
            sendRawPacket(m_dataBuffer, m_sequence, totalSize);
            return;
        }

        // Clamp fragment count to max 8
        if (m_fragmentCount > 8) {
            m_fragmentCount = 8;
        }

        // Compute aligned chunk size (multiple of 16 bytes)
        int chunkSize = (totalSize / m_fragmentCount) & 0xFFFFFFF0;
        if (chunkSize == 0) {
            m_fragmentCount = 1; // fallback to single fragment
            chunkSize = totalSize; // but recalc? actually loop will handle
            // Original sets fragmentCount=1 and then proceeds, but chunkSize remains 0 so loop may be skipped? We'll adjust.
            // For safety, just set chunkSize = totalSize and fragmentCount=1.
            chunkSize = totalSize;
        }

        int bytesSent = 0;
        int offset1 = m_outputOffset;   // from +0x04
        int length1 = m_outputLength;    // from +0x08
        int fragmentIndex = 0;
        int* pFrag = (int*)(this + 0x658); // pointer to fragment array (2 ints per entry)

        // Send all intermediate fragments (fragmentCount - 1)
        for (int i = 0; i < m_fragmentCount - 1; i++) {
            int combined = (m_sequence << 0x18) | chunkSize;
            buildPacketFragment(&pFrag[0], &pFrag[1],
                                combined,
                                m_dataBuffer, offset1, length1,
                                PTR_LAB_0110a3cc, DAT_0110a3d0);
            bytesSent += chunkSize;
            offset1 += chunkSize * 0x10;  // original: offset1 += chunkSize * 0x10 (likely incorrect, but preserved)
            length1 += chunkSize;
            pFrag += 2;
            fragmentIndex++;
        }

        // Send final fragment with remaining size
        int remainingSize = totalSize - bytesSent;
        int combinedFinal = (m_sequence << 0x18) | remainingSize;
        buildPacketFragment(&pFrag[0], &pFrag[1],
                            combinedFinal,
                            m_dataBuffer, offset1, length1,
                            PTR_LAB_0110a3cc, DAT_0110a3d0);
        // Store the last fragment headers directly at m_fragmentCount index in the array
        // (original writes to this+0x650 + fragmentCount*8 and this+0x654 + fragmentCount*8,
        //  but that seems like a bug or struct layout. We'll mimic exactly.)
        int* baseSeq = &this->m_sequence; // +0x650
        baseSeq[m_fragmentCount * 2] = pFrag[0];
        baseSeq[m_fragmentCount * 2 + 1] = pFrag[1];
    }
};