// FUNC_NAME: SomeGameObject::SomeGameObject (derived class constructor)
// Constructor at 0x008d3c90 for a derived class object.
// Base constructor call: FUN_008d3980 (likely base class constructor).
// Initializes vtable pointer, a static class descriptor pointer, and two member fields.
class SomeGameObject : public BaseClass {
public:
    // __thiscall: this passed in ecx
    __thiscall SomeGameObject(void* param2, void* param3) {
        // Call base class constructor (FUN_008d3980)
        BaseClass::BaseClass();

        // Store param2 at offset +0x48 (index 0x12)
        this->m_field48 = param2;                       // param_1[0x12] = param_2

        // Override vtable pointer to derived class vtable
        this->vtablePtr = &g_vtableSomeGameObject;      // *param_1 = &PTR_FUN_00d7d55c

        // Set class descriptor pointer at offset +0x4C (index 0x13)
        this->m_classDesc = &g_classDescSomeGameObject; // param_1[0x13] = &PTR_LAB_00d7d54c

        // Store param3 at offset +0x1C (index 7)
        this->m_field1C = param3;                       // param_1[7] = param_3

        // Return this implicitly (return param_1)
    }

private:
    // Offsets are approximate based on decompilation:
    // +0x00: void* vtablePtr (overridden after base constructor)
    // +0x48 (0x12*4): void* m_field48
    // +0x4C (0x13*4): void* m_classDesc (static descriptor, e.g., RTTI or class name)
    // +0x1C (7*4): void* m_field1C
    // Base class members occupy offsets 0x04..0x18 (assumption)
    void* m_field48;
    void* m_classDesc;
    void* m_field1C;
};

// Static data referenced by the constructor:
extern void* g_vtableSomeGameObject;   // PTR_FUN_00d7d55c
extern void* g_classDescSomeGameObject; // PTR_LAB_00d7d54c