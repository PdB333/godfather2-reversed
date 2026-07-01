// FUNC_NAME: Entity::Entity
#include <cstdint>

// Base class constructor called at 0x0046c590
void __fastcall BaseClassConstructor(uint32_t param);

// Vtable pointer at 0x00d73070
extern const void* g_vtable_Entity;
extern const void* g_vtable_Entity_iface1; // at offset 0x3C
extern const void* g_vtable_Entity_iface2; // at offset 0x48

// Global value from DAT_00e44690
extern uint32_t g_globalEntityFlag;

class Entity {
public:
    // Constructor
    void __thiscall Entity(uint32_t baseParam) {
        // Call base class constructor (likely initializes some base fields)
        BaseClassConstructor(baseParam);

        // Set vtable pointers (single inheritance with multiple interfaces?)
        this->vtable = &g_vtable_Entity;
        this->iface1Vtable = &g_vtable_Entity_iface1; // +0x3C
        this->iface2Vtable = &g_vtable_Entity_iface2; // +0x48

        // Zero-initialize remaining fields
        this->field_0x50 = 0;            // +0x50 (uint32_t)
        this->field_0x54 = 0;            // +0x54 (uint16_t)
        this->field_0x56 = 0;            // +0x56 (uint16_t)
        this->field_0x58 = 0;            // +0x58 (uint32_t)
        this->field_0x5C = 0;            // +0x5C (uint16_t)
        this->field_0x5E = 0;            // +0x5E (uint16_t)
        this->field_0x60 = 0;            // +0x60 (uint32_t)
        this->field_0x64 = 0;            // +0x64 (uint32_t)
        this->field_0x68 = 0;            // +0x68 (uint32_t)
        this->field_0x6C = 0;            // +0x6C (uint32_t)
        this->field_0x74 = 0;            // +0x74 (uint32_t)
        // Note: offset 0x70 (field_0x1c) is set from global
        this->field_0x70 = g_globalEntityFlag; // +0x70 (uint32_t)
    }

private:
    // Vtable pointer (offset 0x00)
    const void* vtable;

    // Padding/intermediate fields (offsets 0x04 to 0x38) not shown; assumed to be handled by base constructor
    // Interface vtable pointers
    const void* iface1Vtable;   // +0x3C
    // ... unknown fields up to +0x48
    const void* iface2Vtable;   // +0x48

    // Zero-initialized data members (offsets relative to start of this class)
    uint32_t field_0x50;        // +0x50
    uint16_t field_0x54;        // +0x54
    uint16_t field_0x56;        // +0x56
    uint32_t field_0x58;        // +0x58
    uint16_t field_0x5C;        // +0x5C
    uint16_t field_0x5E;        // +0x5E
    uint32_t field_0x60;        // +0x60
    uint32_t field_0x64;        // +0x64
    uint32_t field_0x68;        // +0x68
    uint32_t field_0x6C;        // +0x6C
    uint32_t field_0x70;        // +0x70 (set from global)
    uint32_t field_0x74;        // +0x74
};
// The actual layout may be affected by base class fields – exact offsets depend on base class.