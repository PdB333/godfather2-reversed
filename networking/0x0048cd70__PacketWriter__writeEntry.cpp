// FUNC_NAME: PacketWriter::writeEntry

// Reconstructed from x86 decompilation of The Godfather 2 (EARS engine)
// Address: 0x0048cd70
// Role: Writes a type-tagged data entry into a global packet buffer (used in RPC/network serialization)

// Global buffer state – pointer at address 0x01206880 + 0x14 holds the current write position
extern void* g_packetBufferWritePtr;  // Actually stored as offset +0x14 in a larger global structure

// The function writes two different structures depending on a flag in 'this':
// - First time (flag == 0): writes an 8-byte header entry (type tag + 4-byte data)
// - Always: writes a 16-byte data entry (type tag + 8-byte data + 4-byte param)
// Both entries are appended to the growing buffer.

class PacketWriter {
public:
    // Memory layout:
    // +0x00: vtable or other base (size 4)
    // +0x04: data field (uint32, likely a pointer or ID)
    // +0x08: (unknown)
    // +0x0C: bool isInitialized (flag)
    // +0x10: ... (end)

    uint32_t   m_data;          // +0x04
    bool       m_isInit;        // +0x0C

    // Write a type-tagged entry with optional initial header
    void writeEntry(uint32_t param2) {  // param2 is additional 4-byte value
        uint32_t dataVal = m_data;

        // First‑time initialization: write a header entry
        if (!m_isInit) {
            // Write type tag (pointer to a vtable or type descriptor)
            writeTypeTag(reinterpret_cast<void*>(0x01123d28)); // PTR_LAB_01123d28
            // Write the data value (4 bytes)
            writeRawData(&dataVal, 4);  // Actually *(uint32*)*currentWritePtr = dataVal; advance by 4
            m_isInit = true;
        }

        // Always write a data entry
        // Note: Ghidra shows loading an 8-byte value from this+4, but originally it's 4 bytes.
        // The decompiler likely misinterpreted due to alignment; we use the actual 4-byte field.
        uint64_t packedData = static_cast<uint64_t>(dataVal); // For 8-byte write (may be a pointer+size)

        // Write type tag for data entry
        writeTypeTag(reinterpret_cast<void*>(0x01123ddc)); // PTR_FUN_01123ddc

        // Align to 4-byte boundary (though already aligned)
        alignWritePtr(4);

        // Write 8 bytes of data (the packedData)
        writeRawData(&packedData, 8);  // *puVar5 = uVar3

        // Write the second parameter at offset +8 from the start of the 8-byte data
        // Actually this is within the same 12-byte data block: after 8 bytes, write param2
        writeRawDataAtOffset(reinterpret_cast<const char*>(&packedData) + 8, ¶m2, 4);
        // Equivalent: *(uint32*)(currentPtr + 8) = param2; then advance pointer by 12 total
        // The function ends by advancing the global write pointer by 12 bytes after the 8-byte data start.
        advanceWritePtr(12);
    }

private:
    // Inline helper functions mirroring the low-level pointer operations
    void writeTypeTag(void* tag) {
        uint32_t*& writePtr = getWritePtrRef();
        *reinterpret_cast<uint32_t*>(*writePtr) = reinterpret_cast<uint32_t>(tag);
        *writePtr += 4;
    }

    void writeRawData(const void* data, int size) {
        uint32_t*& writePtr = getWritePtrRef();
        memcpy(reinterpret_cast<void*>(*writePtr), data, size);
        *writePtr += size;
    }

    void alignWritePtr(int alignment) {
        uint32_t*& writePtr = getWritePtrRef();
        *writePtr = (*writePtr + 3) & ~(alignment - 1);
    }

    void writeRawDataAtOffset(const void* base, const void* data, int size) {
        uint32_t*& writePtr = getWritePtrRef();
        // Base is the current write pointer before advancing; we write param2 at base+8
        memcpy(reinterpret_cast<void*>(reinterpret_cast<uint32_t>(base) + 8), data, size);
    }

    void advanceWritePtr(int delta) {
        uint32_t*& writePtr = getWritePtrRef();
        *writePtr += delta;
    }

    uint32_t*& getWritePtrRef() {
        // The global pointer is stored at DAT_01206880 + 0x14
        // We assume it's a global variable (or a field in a global structure)
        extern uint32_t* g_packetBufferWritePtr; // Actually DAT_01206880 + 0x14
        return g_packetBufferWritePtr;
    }
};