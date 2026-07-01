// FUNC_NAME: MyComponent::Constructor
#include <cstdint>

// Base class with vtable and possibly a property manager at offset 0x14
class BaseComponent {
public:
    virtual ~BaseComponent() {}
    // Other virtual functions...
};

// Vtable reference - likely for MyComponent
extern void* g_vtable_MyComponent; // from PTR_LAB_00d761ec

// Forward declaration for external functions
void BaseComponent_Constructor(void* arg2, void* arg3); // FUN_0086b060
void* GetPropertyBag(int param); // Possibly FUN_0043c490? No, it's different.
void FUN_0043c490(void* ptr, int value);

class MyComponent : public BaseComponent {
public:
    // Offsets known: vtable at +0x00, propertyManager at +0x14 (pointer)
    // Fields at +0x18 through +0x1f (8 ints)
    uint32_t field_0x18; // +0x18
    uint32_t field_0x19; // +0x19
    uint32_t field_0x1a; // +0x1a
    uint32_t field_0x1b; // +0x1b
    uint32_t field_0x1c; // +0x1c
    uint32_t field_0x1d; // +0x1d
    uint32_t field_0x1e; // +0x1e
    uint32_t field_0x1f; // +0x1f

    // Property manager object (at +0x14) – has a vtable with functions at offsets 0x10 and 0x24
    class PropertyManager* propMgr; // +0x14

    // Hash for property name (likely "IsActive" or similar)
    static const uint32_t kHashIsActive = 0x3a8fda85;

    // Constructor
    __thiscall MyComponent(void* arg2, void* arg3) {
        // Call base constructor
        BaseComponent_Constructor(arg2, arg3);

        // Initialize fields
        this->field_0x18 = 0;
        this->vtable = &g_vtable_MyComponent; // Vtable for this class
        this->field_0x19 = 0;
        this->field_0x1a = 0;
        this->field_0x1b = 0;
        this->field_0x1c = 0;
        this->field_0x1f = 0; // Order as per decompiled
        this->field_0x1e = 0;
        this->field_0x1d = 0;

        // Set property via property manager virtual function at offset 0x10
        // This function takes a hash and a pointer to a bool (arg3 = 0 initially)
        bool result;
        void* propFunc = (void* (*)(uint32_t, bool*))((intptr_t*)(this->propMgr->vtable))[0x10 / 4]; // offset 0x10
        bool active = (propFunc(kHashIsActive, &result) != 0) ? true : false; // Interpret return as boolean
        // Store result into field_0x18 (likely active flag)
        this->field_0x18 = active ? 1 : 0;

        // Get something from property manager via vtable offset 0x24 with argument 5
        void* getFunc = (void* (*)(int))((intptr_t*)(this->propMgr->vtable))[0x24 / 4]; // offset 0x24
        void* obj = getFunc(5);
        if (obj) {
            FUN_0043c490(obj, 5);
        }
    }
};