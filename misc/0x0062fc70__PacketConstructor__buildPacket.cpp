// FUNC_NAME: PacketConstructor::buildPacket
// Function at 0x0062fc70: Constructs a data packet by reading header, copying data from a fixed input buffer location, and appending sequence numbers and timestamps.

#include <cstdint>

class PacketConstructor {
public:
    // Internal buffer pointers: write pointer at +0x8, read pointer at +0xC
    int* m_writeBuffer;  // +0x8
    int* m_readBuffer;   // +0xC

    // Built-in error reporting
    void reportError(const char* msg);  // FUN_00627ac0

    // Reads header count from the input stream (advances read pointer)
    int readHeaderCount(int param);  // FUN_00628820

    // Returns an 8-byte timestamp (two ints)
    uint64_t getTimestamp();  // FUN_00637f10

    // Applies checksum/encryption to a 0x18-byte block at the given offset
    void finalizeBlock(int* baseOffset, int flag);  // FUN_006362d0

    // Checks whether the operation should be cancelled (e.g., connection lost)
    int isCancelled();  // FUN_00625740

    // Builds the packet content
    int buildPacket() {
        int* readPtr = m_readBuffer;  // +0xC

        // Validate header: first int must be 5
        if (m_writeBuffer <= readPtr || readPtr == nullptr || *readPtr != 5) {
            reportError("table");  // PTR_s_table_00e2a8b0
            return 0;
        }

        // Read the number of items to process
        int itemCount = readHeaderCount(1);  // Reads count from buffer, advances read pointer

        // Validate header continuation: next int must be 6 (at offset 8 from original read)
        if (m_writeBuffer <= (int*)((int)readPtr + 8) || (int*)((int)readPtr + 8) == nullptr ||
            *(int*)((int)readPtr + 8) != 6) {
            reportError("function");  // PTR_s_function_00e2a8b4
            return 0;
        }

        if (itemCount < 1) {
            return 0;
        }

        int sequenceNumber = 1;
        // Loop processes each item
        while (true) {
            // Step 1: Copy 8 bytes from the fixed input buffer location (offset 8 from read start)
            int* src = (int*)((int)readPtr + 8);  // Fixed position: original read pointer + 8
            int* dst = (int*)m_writeBuffer;
            dst[0] = src[0];
            dst[1] = src[1];
            m_writeBuffer += 2;  // Advance by 8 bytes (2 ints)

            // Step 2: Write a type tag (3) and the sequence number as float
            int* tagPos = (int*)m_writeBuffer;
            tagPos[0] = 3;
            *(float*)(tagPos + 1) = (float)sequenceNumber;
            m_writeBuffer += 2;  // Advance by 8 bytes

            // Step 3: Write the current timestamp (8 bytes)
            uint64_t timestamp = getTimestamp();  // Returns two ints
            int* timePos = (int*)m_writeBuffer;
            timePos[0] = (int)(timestamp & 0xFFFFFFFF);
            timePos[1] = (int)(timestamp >> 32);
            m_writeBuffer += 2;  // Advance by 8 bytes

            // Step 4: Finalize the 0x18-byte block we just wrote (start at current position - 0x18)
            finalizeBlock((int*)((int)m_writeBuffer - 0x18), 1);

            // Step 5: Check for cancellation
            if (isCancelled() != 0) {
                return 1;  // Abort, packet incomplete
            }

            // Step 6: Rewind write pointer by 8 bytes (undo the timestamp write?  
            // This suggests the timestamp is used temporarily and then overwritten later.
            m_writeBuffer -= 2;

            // Next sequence number
            sequenceNumber++;
            if (itemCount < sequenceNumber) {
                break;
            }
        }

        return 0;  // Success
    }
};