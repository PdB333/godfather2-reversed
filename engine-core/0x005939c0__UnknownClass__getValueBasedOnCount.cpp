// FUNC_NAME: UnknownClass::getValueBasedOnCount
#pragma pack(push, 1)
class UnknownClass {
public:
    union {
        uint32_t m_countAndSmall;          // +0x4  (raw value, low byte = count, byte at +6 = smallValue)
        struct {
            uint8_t m_count;               // +0x4  (low byte)
            uint8_t padding_5;             // +0x5
            uint8_t m_smallValue;          // +0x6
            uint8_t padding_7;             // +0x7
        } parts;
    };
    uint32_t m_largeValue;                 // +0xC

    // Returns m_smallValue if m_count <= 9, otherwise returns m_largeValue.
    uint32_t getValueBasedOnCount() const {
        if (m_count > 9) {
            return m_largeValue;
        } else {
            return static_cast<uint32_t>(m_smallValue);
        }
    }
};
#pragma pack(pop)