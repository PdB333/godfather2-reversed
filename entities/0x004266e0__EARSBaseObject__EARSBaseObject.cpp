// FUNC_NAME: EARSBaseObject::EARSBaseObject

#include <cstdint>

// Forward declaration of the global manager class
class GlobalManager;

// Global singleton instance (DAT_00e2e6f0)
extern GlobalManager g_Manager;

// Base object that stores an identifier and registers itself with the engine manager
class EARSBaseObject {
public:
    // +0x00: Unique identifier or pointer (e.g., object type ID)
    uint32_t m_id;

    // Constructor: copies the given ID and registers this object with the global manager
    __thiscall EARSBaseObject(uint32_t id) {
        // Store the identifier at offset 0x00 of the object
        this->m_id = id;

        // Register this instance with the global manager (e.g., for lifetime tracking or event dispatch)
        g_Manager.Register(this);
    }
};