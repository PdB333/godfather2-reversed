// FUNC_NAME: CrewLeaderComponent::create
#include <cstdint>

// Forward declaration for base class constructor
class Component {
public:
    Component(); // base constructor at FUN_008d3980
};

// Allocation function (likely custom allocator)
void* allocate(uint32_t size); // at FUN_009c8e50

// Vtable and static label pointers (from .data)
extern void* CrewLeaderComponent_vtable; // PTR_FUN_00d7d55c
extern void* someStaticLabel;            // PTR_LAB_00d7d54c

class CrewLeaderComponent : public Component {
public:
    static CrewLeaderComponent* create(int param1, uint32_t param2);

    // Virtual table pointer at +0x00
    // Offsets based on decompiled array indexing:
    // puVar1[7]  -> offset 0x1C (7 * 4 = 28)
    // puVar1[0x12] -> offset 0x48 (18 * 4 = 72)
    // puVar1[0x13] -> offset 0x4C (19 * 4 = 76)

    uint32_t field_0x1C;   // +0x1C: param2
    int      field_0x48;   // +0x48: param1 (non-zero guard)
    void*    field_0x4C;   // +0x4C: pointer to static label
    // Remaining fields to fill 0x84 (132 bytes)
    uint8_t  pad[0x84 - 0x50]; // approximate padding (0x50 = 80 bytes used)
};

// Static factory/constructor
CrewLeaderComponent* CrewLeaderComponent::create(int param1, uint32_t param2) {
    if (param1 == 0) {
        return nullptr;
    }

    void* mem = allocate(0x84); // size = 132 bytes
    if (mem == nullptr) {
        return nullptr;
    }

    CrewLeaderComponent* obj = static_cast<CrewLeaderComponent*>(mem);

    // Call base class constructor (Component::Component)
    Component::Component();

    // Initialize fields
    obj->field_0x1C = param2;       // puVar1[7] = param2
    obj->field_0x48 = param1;       // puVar1[0x12] = param1
    obj->vtable = &CrewLeaderComponent_vtable; // *puVar1 = vtable
    obj->field_0x4C = &someStaticLabel;       // puVar1[0x13] = label

    return obj;
}