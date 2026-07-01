// FUNC_NAME: BytecodeBuffer::emitPair
class BytecodeBuffer {
public:
    struct CodeStream {
        uint32_t* m_pCode;       // +0x0C: pointer to code array (uint32_t per element)
        uint32_t* m_pData;       // +0x14: pointer to data array (uint32_t per element)
        int m_codeCapacity;      // +0x2C: allocated size of m_pCode (number of elements)
        int m_dataCapacity;      // +0x30: allocated size of m_pData
    };

    CodeStream* m_pStream;       // +0x00: pointer to the underlying code/data stream
    void* m_allocator;           // +0x04: allocator for growing arrays
    int m_index;                 // +0x18: current write index (number of pairs emitted)
    int m_debugIndex;            // +0x20: previously set to -1, probably debug counter reset

    // Emit a pair of values into the code and data arrays, growing them if necessary
    void emitPair(uint32_t param1, uint32_t param2) {
        CodeStream* stream = m_pStream;

        // Prologue – likely checks or resets some internal state
        FUN_006426a0();
        m_debugIndex = -1;

        // Grow code array if needed
        if (stream->m_codeCapacity < m_index + 1) {
            uint32_t* newCode = (uint32_t*)FUN_00627930(
                m_allocator,
                stream->m_pCode,
                &stream->m_codeCapacity,
                4,                       // sizeof(uint32_t)
                "code size overflow"
            );
            stream->m_pCode = newCode;
        }

        // Grow data array if needed
        if (stream->m_dataCapacity < m_index + 1) {
            uint32_t* newData = (uint32_t*)FUN_00627930(
                m_allocator,
                stream->m_pData,
                &stream->m_dataCapacity,
                4,
                "code size overflow"
            );
            stream->m_pData = newData;
        }

        // Write the pair at the current index
        stream->m_pCode[m_index] = param1;
        stream->m_pData[m_index] = param2;

        // Advance the index
        m_index++;
    }
};