// FUNC_NAME: SimObject::SimObject
class SimObject {
public:
    // Offsets from this:
    // +0x00: mNext (pointer to next object in list)
    // +0x04: mFlagsLow (byte)
    // +0x05: mFlagsHigh (byte)
    // +0x08 to +0x48: padding/other fields
    // +0x1C: mType (set to 5 in constructor)
    // +0x4C: mNameTerminator (byte, always 0)
    // +0x4D: mName (char[32])
    // +0x6C: mTrailingByte (always 0)

    __thiscall SimObject() {
        mNext = nullptr;
        mFlagsLow = 0;
        mFlagsHigh = 0;
        m_field2 = 0;   // +0x08
        m_field3 = 0;   // +0x0C
        m_field4 = 0;   // +0x10
        m_field5 = 0;   // +0x14
        m_field6 = 0;   // +0x18
        mType = 5;      // +0x1C
        m_field8 = 0;   // +0x20
        m_field9 = 0;   // +0x24
        m_field10 = 0;  // +0x28
        m_field11 = 0;  // +0x2C
        m_field12 = 0;  // +0x30
        m_field13 = 0;  // +0x34
        m_field14 = 0;  // +0x38
        m_field15 = 0;  // +0x3C
        m_field16 = 0;  // +0x40
        m_field17 = 0;  // +0x44
        m_field18 = 0;  // +0x48
        mNameTerminator = 0;  // +0x4C

        // Get default name from system (e.g., "SimObject_<unique_id>")
        const char* defaultName = GetDefaultSimObjectName(); // FUN_0069d890
        snprintf(mName, sizeof(mName), "%s", defaultName);

        mTrailingByte = 0; // +0x6C
    }

private:
    void* mNext;                // +0x00
    uint8_t mFlagsLow;          // +0x04
    uint8_t mFlagsHigh;         // +0x05
    // padding to align to 4 bytes? But offsets suggest 0x08 is next dword.
    // 6 bytes from 0x06 to 0x07 uninitialized? Actually only 2 bytes at 0x04-0x05 are set.
    // The rest are uint32_t fields.
    uint32_t m_field2;          // +0x08
    uint32_t m_field3;          // +0x0C
    uint32_t m_field4;          // +0x10
    uint32_t m_field5;          // +0x14
    uint32_t m_field6;          // +0x18
    uint32_t mType;             // +0x1C (always 5 initially)
    uint32_t m_field8;          // +0x20
    uint32_t m_field9;          // +0x24
    uint32_t m_field10;         // +0x28
    uint32_t m_field11;         // +0x2C
    uint32_t m_field12;         // +0x30
    uint32_t m_field13;         // +0x34
    uint32_t m_field14;         // +0x38
    uint32_t m_field15;         // +0x3C
    uint32_t m_field16;         // +0x40
    uint32_t m_field17;         // +0x44
    uint32_t m_field18;         // +0x48
    uint8_t mNameTerminator;    // +0x4C
    char mName[32];             // +0x4D
    uint8_t mTrailingByte;      // +0x6C
};