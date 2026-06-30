// FUNC_NAME: StreamReader::processCommands
// Function address: 0x00513a20
// Reconstructed C++ code for an EARS engine stream reader that reads a header of three dwords
// (type, count, alignment/size) from an internal buffer, advances the buffer pointer,
// aligns to the next boundary based on the size field, then calls a handler function
// with the type, a 64-bit value (count in high, aligned address in low if count != 0), and size.

class StreamReader {
public:
    // +0x18: pointer to current position in the stream buffer
    uint32_t* m_pCurrent;
    
    // param_2 is a pointer to an object whose first member is a function (handler)
    void processCommands(void* handler) {
        // Read three dwords from the current position
        uint32_t* current = m_pCurrent;
        uint32_t commandType = current[0];
        m_pCurrent = current + 1;
        uint32_t count = current[1];
        m_pCurrent = current + 2;
        uint32_t size = current[2];
        m_pCurrent = current + 3;
        
        // Compute aligned address: align (baseAddr + size + 0xB) to a multiple of size
        uint32_t baseAddr = reinterpret_cast<uint32_t>(current);
        uint32_t alignedAddr = (baseAddr + size + 0xB) & ~(size - 1);
        // Update current pointer to skip the data block (count * 8 bytes after alignment)
        m_pCurrent = reinterpret_cast<uint32_t*>(count * 8 + alignedAddr);
        
        // Call the handler function stored at offset 0 of the handler object
        // The second argument is a 64-bit value: high = count, low = (count != 0) ? alignedAddr : 0
        uint64_t secondArg = (static_cast<uint64_t>(count) << 32) | (count ? alignedAddr : 0);
        reinterpret_cast<void (*)(uint32_t, uint64_t, uint32_t)>(*reinterpret_cast<void**>(handler))(
            commandType, secondArg, size
        );
    }
};