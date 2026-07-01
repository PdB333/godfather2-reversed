// FUNC_NAME: ConfigManager::ConfigManager
// Address: 0x00858130
// Constructor for a configuration manager that loads values via hash lookup.

#include <cstdint>

// Forward declarations
class BaseConfig; // base class at FUN_0099c4a0
uint32_t* lookupHash(uint32_t hash); // at FUN_004a3790

class ConfigManager : public BaseConfig {
public:
    // vtable pointer at offset 0x00, set to &PTR_FUN_00d753a0

    // Fields at specific offsets (indices 0x10..0x19 in param_1 array):
    // +0x40 (index 0x10): m_value1
    // +0x44 (index 0x11): unused/padding
    // +0x48 (index 0x12): m_value2
    // +0x4C (index 0x13): m_value3
    // +0x50 (index 0x14): m_value4
    // +0x54 (index 0x15): m_value5
    // +0x58 (index 0x16): m_value6
    // +0x5C (index 0x17): m_value7
    // +0x60 (index 0x18): m_value8
    // +0x64 (index 0x19): m_value9

    uint32_t m_value1;   // +0x40
    // padding at +0x44
    uint32_t m_value2;   // +0x48
    uint32_t m_value3;   // +0x4C
    uint32_t m_value4;   // +0x50
    uint32_t m_value5;   // +0x54
    uint32_t m_value6;   // +0x58
    uint32_t m_value7;   // +0x5C
    uint32_t m_value8;   // +0x60
    uint32_t m_value9;   // +0x64

    ConfigManager(uint32_t param2, uint32_t param3) {
        // Call base class constructor (FUN_0099c4a0)
        BaseConfig::BaseConfig(param2, param3);

        // Set vtable pointer to derived class vtable
        *(void***)this = &PTR_FUN_00d753a0;

        // Initialize all derived fields to 0
        m_value1 = 0;
        m_value2 = 0;
        m_value3 = 0;
        m_value4 = 0;
        m_value5 = 0;
        m_value6 = 0;
        m_value7 = 0;
        m_value8 = 0;
        m_value9 = 0;

        // Lookup via hash and store results if found
        uint32_t* result;
        result = lookupHash(0xe9824d40);
        if (result != nullptr) {
            m_value1 = *result;
        }

        result = lookupHash(0x806a7f17);
        if (result != nullptr) {
            m_value2 = *result;
        }

        result = lookupHash(0x9a13de32);
        if (result != nullptr) {
            m_value3 = *result;
        }

        result = lookupHash(0x70bebcc6);
        if (result != nullptr) {
            uint32_t val = *result;
            // Combination: (val * 2 | val) then multiply by 4 and OR again
            uint32_t temp = (val * 2) | val;
            m_value4 = (temp * 4) | temp;
        }

        result = lookupHash(0xa05d3653);
        if (result != nullptr) {
            m_value5 = *result;
        }

        result = lookupHash(0xe343ec65);
        if (result != nullptr) {
            m_value6 = *result;
        }

        result = lookupHash(0x494036e8);
        if (result != nullptr) {
            m_value7 = *result;
        }

        result = lookupHash(0xfaa4f71d);
        if (result != nullptr) {
            m_value8 = *result;
        }

        result = lookupHash(0x3d8bad2f);
        if (result != nullptr) {
            m_value9 = *result;
        }
    }

private:
    // Prevent copy/assignment
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
};
```