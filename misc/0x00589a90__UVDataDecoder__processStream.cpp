// FUNC_NAME: UVDataDecoder::processStream

// This function processes a compressed stream of UV data (6 bytes per entry: ushort U, ushort padding, ushort V)
// and writes decoded float UVs to a vertex buffer (16 bytes per vertex, two floats at offsets 0 and 4).
// Members:
//   +0x20: uint8_t* m_dataBuffer   // pointer to current position in compressed data
//   +0x24: uint32_t m_currentIndex  // index of current entry being read
// Global constants:
//   DAT_00e44564: float center value (likely 0.5f or 0.0f)
//   DAT_00e44820: float scale factor (e.g., 1.0f / 65535.0f)
// Parameters:
//   startIndex in EAX: number of entries to skip before processing
//   param_1: output vertex buffer (pointer to array of 16-byte vertices)
//   param_2: number of entries to process

void __thiscall UVDataDecoder::processStream(int startIndex, void* outVertices, int count)
{
    // Advance to the requested start index
    while (m_currentIndex < startIndex) {
        m_dataBuffer += 6;        // each entry is 6 bytes
        m_currentIndex++;
    }

    // Decode 'count' entries
    for (int i = 0; i < count; i++) {
        // Read the two ushort components from the current entry
        uint16_t* entry = (uint16_t*)m_dataBuffer;
        uint16_t uRaw = entry[0];   // first ushort: U coordinate
        uint16_t vRaw = entry[2];   // third ushort: V coordinate (skip index 1, unused)

        // Decompress to float UV (center - raw * scale)
        float u = DAT_00e44564 - (float)uRaw * DAT_00e44820;
        float v = DAT_00e44564 - (float)vRaw * DAT_00e44820;

        // Write UV pair to the output vertex (16 bytes per vertex)
        // FUN_0056d040 stores two floats at the given address
        FUN_0056d040(v, u, outVertices);   // note: first arg is V, second is U

        // Advance to next entry and next output vertex
        m_dataBuffer += 6;
        m_currentIndex++;
        outVertices = (uint8_t*)outVertices + 0x10;
    }
}