// FUNC_NAME: EARSString::assignSubstring

// Reconstructed from 0x0043eeb0: EARSString internal substring assignment
// Copies up to 'count' characters from 'src' starting at 'offset' into this string.
// Uses small-string optimization: when m_capacity < 16, data is stored inline at this+4;
// otherwise, m_data points to heap-allocated buffer.

class EARSString {
public:
    // offsets:
    // +0x00: unknown (possibly vtable or alignment padding)
    // +0x04: data pointer (if m_capacity >= 16) or start of inline buffer (if m_capacity < 16)
    // +0x14: m_size  (current length)
    // +0x18: m_capacity (total allocated capacity, including null terminator)
    char* m_data;          // +0x04
    uint32_t m_size;       // +0x14
    uint32_t m_capacity;   // +0x18

    // Internal: returns pointer to writable character buffer
    char* _getBuffer() const {
        if (m_capacity < 16) {
            // Inline buffer starts at this+4
            return reinterpret_cast<char*>(const_cast<EARSString*>(this) + 4);
        } else {
            return m_data;
        }
    }

    // The method being decompiled
    EARSString* assignSubstring(const EARSString& src, uint32_t offset, uint32_t count);
};

EARSString* EARSString::assignSubstring(const EARSString& src, uint32_t offset, uint32_t count) {
    // Validate source offset
    if (src.m_size < offset) {
        // assertion failure (likely crash/abort)
        FUN_00b965e0();
    }

    // Compute max copy length
    uint32_t maxCount = src.m_size - offset;
    if (count < maxCount) {
        maxCount = count;
    }

    // Self-assignment check
    if (this != &src) {
        // Handle the case where the destination needs resizing
        if (maxCount == 0xFFFFFFFF) {
            // Invalid count, assert
            FUN_00b9654f();
        }

        if (m_capacity < maxCount) {
            // Need to grow: call resize function (probably sets new capacity and reallocates)
            FUN_0043f830(maxCount, m_size);
        } else if (maxCount == 0) {
            // Special case: set empty string
            m_size = 0;
            if (m_capacity < 16) {
                // Inline: null-terminate at buffer start
                *(reinterpret_cast<char*>(this) + 4) = '\0';
            } else {
                // Heap: null-terminate the buffer pointed to by m_data
                *m_data = '\0';
            }
            return this;
        }

        if (maxCount != 0) {
            // Get source data pointer based on inline/heap
            const char* srcData;
            if (src.m_capacity < 16) {
                srcData = reinterpret_cast<const char*>(&src) + 4;
            } else {
                srcData = src.m_data;
            }

            // Get destination data pointer
            char* destData;
            if (m_capacity < 16) {
                destData = reinterpret_cast<char*>(this) + 4;
            } else {
                destData = m_data;
            }

            // Copy the substring
            _memcpy_s(destData, m_capacity, srcData + offset, maxCount);
            m_size = maxCount;

            // Null-terminate
            if (m_capacity < 16) {
                destData[maxCount] = '\0';
            } else {
                m_data[maxCount] = '\0';
            }
        }
    } else {
        // Self-assignment: move data within same string using helper
        // FUN_0043f360(a,b) likely shifts or copies region within the buffer
        FUN_0043f360(maxCount + offset, 0xFFFFFFFF);
        FUN_0043f360(0, offset);
    }

    return this;
}