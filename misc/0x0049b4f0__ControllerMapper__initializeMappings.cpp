// FUNC_NAME: ControllerMapper::initializeMappings

#pragma pack(push, 1)
struct ActionMappingEntry {
    int32_t  field_0;   // +0x00 - unknown
    int32_t  type;      // +0x04 - e.g., 1 for gamepad scheme
    int32_t  physical;  // +0x08 - physical input index (0-15)
    uint8_t  virtual;   // +0x0C - virtual input index (0-15)
};
#pragma pack(pop)

class ControllerMapper {
public:
    byte   m_extraVirt1;       // +0xC4
    byte   m_extraVirt2;       // +0xC6
    byte   m_physToVirt[16];   // +0xBC - maps physical index -> virtual index
    int    m_virtToPhys[16];   // +0xCC - maps virtual index -> physical index (initialized to 0x10)

    // pointer to an array of 16 ActionMappingEntry structs
    ActionMappingEntry* m_actions; // +0xB8

    void initializeMappings();
};

void ControllerMapper::initializeMappings()
{
    // Step 1: Reset all virtual mappings to 0x10 (unmapped)
    for (int i = 0; i < 16; i++) {
        m_virtToPhys[i] = 0x10;
    }

    // Step 2: Build bidirectional mapping from the action entries
    for (int i = 0; i < 16; i++) {
        ActionMappingEntry* entry = &m_actions[i];

        if (entry->physical != -1) {
            int physIdx = entry->physical;
            uint8_t virtIdx = entry->virtual;

            if (physIdx < 16 && virtIdx < 16) {
                if (virtIdx != 0) {
                    m_physToVirt[physIdx] = virtIdx;
                }
                m_virtToPhys[virtIdx] = physIdx;
            }
        }
    }

    // Step 3: If the first action entry is for gamepad scheme (type == 1),
    // override some specific mappings
    if (m_actions[0].type == 1) {
        m_extraVirt1 = 10;
        m_virtToPhys[10] = 8;   // mapping virtual 10 -> physical 8
        m_extraVirt2 = 0xB;
        m_virtToPhys[11] = 10;  // mapping virtual 11 -> physical 10
    }
}