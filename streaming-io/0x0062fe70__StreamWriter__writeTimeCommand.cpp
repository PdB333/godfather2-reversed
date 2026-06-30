// FUNC_NAME: StreamWriter::writeTimeCommand

// Address: 0x0062fe70
// This function writes a timestamp command (type 3) into a command stream buffer.
// The buffer is assumed to have a header with magic value 5 at the start.
// The offsets correspond to a class with two pointers:
//   +0x08 - current write pointer (points to next free slot)
//   +0x0C - header pointer (points to the first int of buffer, must be 5)

class StreamWriter {
    int* m_writePtr;  // +0x08
    int* m_headerPtr; // +0x0C (points to buffer start, *m_headerPtr should be 5)

public:
    // Write a timestamp command into the stream.
    // Returns 1 on success.
    int writeTimeCommand() {
        // Validate buffer state: header must be valid and write pointer must have advanced past the header
        if ((m_writePtr <= m_headerPtr) || (m_headerPtr == nullptr) || (*m_headerPtr != 5)) {
            assert("table"); // Error: buffer format violated (expected table marker)
        }

        // Get current time in seconds (parameter 1 indicates default time source)
        float currentTime = getTime(1);  // FUN_00628820

        // Write command type 3 (timestamp)
        *m_writePtr = 3;
        // Write the time as raw float bits
        *(m_writePtr + 1) = *reinterpret_cast<int*>(&currentTime);

        // Advance write pointer by two ints (8 bytes)
        m_writePtr += 2;

        return 1;
    }

private:
    static float getTime(int source); // External function returning time in seconds
};