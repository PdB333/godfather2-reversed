// FUNC_NAME: Entity::Entity
// Address: 0x006e05d0
// Role: Entity constructor (initializes base class, vtable, interface pointers, and zeroed fields)

// External symbols for vtable and interface pointers
extern void* g_vtable_Entity;            // PTR_FUN_00d5f758
extern void* g_interface_0x3C;           // PTR_LAB_00d5f748
extern void* g_interface_0x48;           // PTR_LAB_00d5f744
extern void* g_interface_0x50;           // PTR_LAB_00d5f740

// Forward declaration of called functions
void __thiscall BaseClassConstruct(int param);                 // FUN_00473840
void __cdecl EntityInitPart2(void);                            // FUN_006e01d0

class Entity {
public:
    // Known field offsets (in bytes)
    void* vtable;            // +0x00
    // (other members possibly before offset 0x3C)
    void* field_0x3C;        // +0x3C (offset 0x0f in words)
    void* field_0x48;        // +0x48 (offset 0x12)
    void* field_0x50;        // +0x50 (offset 0x14)
    int field_0x58;          // +0x58 (offset 0x16)
    int field_0x5C;          // +0x5C (offset 0x17)
    int field_0x60;          // +0x60 (offset 0x18)
    int field_0x64;          // +0x64 (offset 0x19)

    __thiscall Entity(int initParam) {
        // Call base class constructor with the same parameter
        BaseClassConstruct(initParam);

        // Set vtable pointer
        this->vtable = &g_vtable_Entity;

        // Set interface pointers
        this->field_0x3C = &g_interface_0x3C;
        this->field_0x48 = &g_interface_0x48;
        this->field_0x50 = &g_interface_0x50;

        // Zero out 4 fields (likely state flags)
        this->field_0x58 = 0;
        this->field_0x5C = 0;
        this->field_0x60 = 0;
        this->field_0x64 = 0;

        // Additional initialization (might set up subsystems)
        EntityInitPart2();
    }
};