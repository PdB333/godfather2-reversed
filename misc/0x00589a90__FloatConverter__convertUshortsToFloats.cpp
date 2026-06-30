// FUNC_NAME: FloatConverter::convertUshortsToFloats
// Address: 0x00589a90
// Decodes a stream of 16-bit unsigned integer pairs into 32-bit floats using scale/offset.
// The function maintains internal pointers (m_pSourceData at +0x20, m_currentIndex at +0x24).
// It first fast-forwards the internal index to match a start value (passed in EAX register),
// then writes up to count elements to the output buffer.
// Each source element is a triplet of ushorts (6 bytes), but only ushort[0] and ushort[2] are used.
// Output buffer advances by 0x10 bytes per call to FUN_0056d040 (assumed to write two floats).

class FloatConverter {
public:
    // +0x20: pointer to source data (array of ushort triplets)
    ushort* m_pSourceData;
    // +0x24: current position index (number of elements processed)
    int m_currentIndex;

    // param_1: pointer to output buffer (float2 or float4 structure)
    // param_2: total number of elements to write (exclusive end index)
    // in_EAX: start index to skip to before writing (passed in EAX register)
    void __thiscall convertUshortsToFloats(void* pOutputBuffer, int endIndex) {
        // Fast-forward: skip source entries until m_currentIndex == startIndex (in_EAX)
        while (m_currentIndex < startIndex) { // startIndex is passed via EAX (not shown in stack params)
            m_pSourceData += 3;          // each entry is 3 ushorts (6 bytes)
            m_currentIndex++;
        }

        // Process entries from current index up to (endIndex - 1)
        while (m_currentIndex < endIndex) {
            // Convert two ushorts to scaled floats: offset - ushort * scale
            float x = kOffset - (float)m_pSourceData[2] * kScale;
            float y = kOffset - (float)m_pSourceData[0] * kScale;
            // Call helper to write two floats to output (assumed function at 0x0056d040)
            FUN_0056d040(x, y, pOutputBuffer); // pOutputBuffer is treated as int by callee

            // Advance both pointers
            m_pSourceData += 3;           // skip 3 ushorts
            m_currentIndex++;
            pOutputBuffer = (void*)((int)pOutputBuffer + 0x10); // advance output by 16 bytes
        }
    }

private:
    // Constants (from DAT_00e44564 and DAT_00e44820)
    static const float kOffset = 0.0f;   // placeholder: actual value unknown
    static const float kScale = 1.0f;    // placeholder: actual value unknown

    // External helper function (likely writes two floats to a 16-byte structure)
    void FUN_0056d040(float x, float y, void* output);
};