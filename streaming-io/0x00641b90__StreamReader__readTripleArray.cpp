// FUNC_NAME: StreamReader::readTripleArray
// Address: 0x00641b90
// Role: Reads an array of 3-int structures from a binary stream into a dynamic buffer.
// The buffer object (param_1) stores the array pointer at +0x18 and count at +0x38.
// The stream object (in_EAX) contains allocator (+0x00), endian flag (+0x0C), and error string (+0x10).

struct StreamReader {
    void*   m_allocator;       // +0x00
    int     m_byteOrder;       // +0x0C  (0 = little-endian direct, non-zero = big-endian byte-by-byte)
    char*   m_errorString;     // +0x10  for error messages
};

struct TripleArray {
    int*    m_data;            // +0x18
    int     m_count;           // +0x38
};

// Error logging function (likely EARSEngine::logError)
void EARSEngine::logError(void* context, const char* fmt, ...);

// Memory allocation function (global, likely from EARS heap)
extern void* (*g_allocFunc)(int, unsigned int);

void StreamReader::readTripleArray(TripleArray* outArray) {
    StreamReader* stream = this; // in_EAX
    int count = stream->readInt32(); // FUN_00641940 -> returns count

    // Validate count
    if (count < 0) {
        EARSEngine::logError(stream->m_allocator, "bad integer in %s", stream->m_errorString);
    }

    // Allocate memory for count * sizeof(Triple)
    unsigned int allocSize = count * 12;
    int* data = nullptr;
    if (allocSize != 0) {
        if (allocSize > 0xFFFFFFFC) {
            EARSEngine::logError(stream->m_allocator, "memory allocation error: block too big");
        }
        data = (int*)(*g_allocFunc)(0, allocSize);
        if (data == nullptr) {
            if (stream->m_allocator != nullptr) {
                stream->handleAllocFailure(); // FUN_00635a80
                return;
            }
        } else {
            if (stream->m_allocator != nullptr) {
                // Update memory tracking
                int* tracking = *(int**)((char*)stream->m_allocator + 0x10);
                tracking[0] += allocSize; // +0x24 relative to some structure
            }
        }
    }
    outArray->m_data = data;
    outArray->m_count = count;

    // Read each triple
    for (int i = 0; i < count; i++) {
        int* triple = &data[i * 3];
        // Read first int (always via stream->readInt32)
        triple[0] = stream->readInt32(); // FUN_00641a50

        // Read second int (endian-aware)
        int val2;
        if (stream->m_byteOrder == 0) {
            if (stream->readBytes(&val2, 4) != 0) { // FUN_006385a0 returns non-zero on success?
                stream->skip(); // FUN_00641890 (probably skip on error)
                return;
            }
        } else {
            // Big-endian: read 4 bytes in reverse order
            unsigned char bytes[4];
            for (int j = 3; j >= 0; j--) {
                bytes[j] = stream->readByte(); // FUN_006418b0
            }
            val2 = *(int*)bytes;
        }
        if (val2 < 0) {
            EARSEngine::logError(stream->m_allocator, "bad integer in %s", stream->m_errorString);
        }
        triple[1] = val2;

        // Read third int (endian-aware)
        int val3;
        if (stream->m_byteOrder == 0) {
            if (stream->readBytes(&val3, 4) != 0) {
                stream->skip();
                return;
            }
        } else {
            unsigned char bytes[4];
            for (int j = 3; j >= 0; j--) {
                bytes[j] = stream->readByte();
            }
            val3 = *(int*)bytes;
        }
        if (val3 < 0) {
            EARSEngine::logError(stream->m_allocator, "bad integer in %s", stream->m_errorString);
        }
        triple[2] = val3;
    }
}

// Helper stubs for the stream methods (not shown, but assumed to exist in the actual class)
int StreamReader::readInt32();               // FUN_00641940 or FUN_00641a50?
void StreamReader::handleAllocFailure();     // FUN_00635a80
void StreamReader::skip();                   // FUN_00641890
int StreamReader::readBytes(void*, int);     // FUN_006385a0 (returns 0 on success?)
unsigned char StreamReader::readByte();      // FUN_006418b0