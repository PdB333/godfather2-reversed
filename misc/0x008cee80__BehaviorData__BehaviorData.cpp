// FUNC_NAME: BehaviorData::BehaviorData
#include <cstdint>

// Forward declarations
extern void BaseBehavior::BaseBehavior(void* data, uint32_t extra); // FUN_00414f30
extern uint32_t _DAT_00d5780c; // Global constant

// Attribute identifiers (likely CRC32 of string names)
static constexpr uint32_t kAttrField1 = 0x780d0a6;  // sets m_byteField1 (+0x0d)
static constexpr uint32_t kAttrField2 = 0x77212985; // sets m_byteField2 (+0x0e)
static constexpr uint32_t kAttrField3 = 0xe926b6a2; // sets m_byteField3 (+0x35)
static constexpr uint32_t kAttrField4 = 0xae64f0d;  // sets m_byteField4 (+0x36)
static constexpr uint32_t kAttrField5 = 0x78a7dafd; // sets m_byteField5 (+0x37)
static constexpr uint32_t kAttrField6 = 0xfc2cf975; // sets m_byteField6 (+0x39)
static constexpr uint32_t kAttrField7 = 0x79238ce8; // sets m_byteField7 (+0x3a)

// Layout of a single attribute entry in the data source
struct AttributeEntry {
    uint8_t value;       // +0x00
    uint8_t _pad[0x0F];  // padding to 0x10
    uint32_t hash;       // +0x10
};

// Layout of the initialization data block
struct InitData {
    void* pEntries;  // +0x1c: pointer to array of AttributeEntry*
    uint16_t count;  // +0x20: number of entries
};

// The behavior object layout (partial)
class BehaviorData {
public:
    // Vtable pointer at +0x00
    uint8_t m_field1;  // +0x0d
    uint8_t m_field2;  // +0x0e
    uint8_t m_field3;  // +0x35
    uint8_t m_field4;  // +0x36
    uint8_t m_field5;  // +0x37
    uint8_t m_field6;  // +0x39
    uint8_t m_field7;  // +0x3a
    uint32_t m_field8; // +0x3c (from global)

    // Constructor
    BehaviorData(InitData* pData, uint32_t extra);
};

// Constructor implementation
BehaviorData* __thiscall BehaviorData::BehaviorData(InitData* pData, uint32_t extra) {
    // Call base class constructor with the same data
    BaseBehavior::BaseBehavior(pData, extra);

    // Set vtable pointer
    this->vtable = &PTR_FUN_00d7cc20;

    // Initialize default values
    this->m_field1 = 0xFF;
    this->m_field3 = 0;
    this->m_field4 = 6;
    this->m_field5 = 30;  // 0x1e
    this->m_field2 = 18;  // 0x12
    this->m_field6 = 30;  // 0x1e
    this->m_field7 = 60;  // 0x3c
    this->m_field8 = _DAT_00d5780c;

    // Override fields from attribute entries, if any
    if (pData->count != 0) {
        for (uint32_t i = 0; i < pData->count; ++i) {
            AttributeEntry* entry = pData->pEntries[i];
            uint32_t hash = entry->hash;
            uint8_t value = entry->value;

            if (hash < 0x78a7dafe) {
                if (hash == kAttrField5) {
                    this->m_field5 = value;
                } else if (hash == kAttrField1) {
                    this->m_field1 = value;
                } else if (hash == kAttrField4) {
                    this->m_field4 = value;
                } else if (hash == kAttrField2) {
                    this->m_field2 = value;
                }
            } else {
                if (hash == kAttrField7) {
                    this->m_field7 = value;
                } else if (hash == kAttrField3) {
                    this->m_field3 = value;
                } else if (hash == kAttrField6) {
                    this->m_field6 = value;
                }
            }
        }
    }

    return this;
}