// FUNC_NAME: GameObject::GameObject
// Address: 0x0043fed0
// Constructor for a game object. Sets vtable to base class, initializes a subobject,
// then sets vtable to derived class. Resets a global flag and optionally calls a post-construct function.

#include <cstdint>

// Global flag reset to 0 during construction.
extern int32_t g_bSomeGlobalFlag; // DAT_012233a0

// Forward declarations of helper functions (to be reconstructed separately).
void initSubObject(void* subObject);          // FUN_009c8f10 - initializes subobject at offset +0x04
void postConstruct(GameObject* obj);          // FUN_009c8eb0 - called if allocFlag & 1

class GameObject {
public:
    void* vtable;       // +0x00
    void* subObject;    // +0x04 - pointer to a subobject (initialized by initSubObject)

    // Constructor
    // allocFlag: if bit 0 is set, call postConstruct (e.g., for heap-allocated objects)
    GameObject(uint8_t allocFlag) {
        // Step 1: Set vtable to base class vtable (base constructor may override later)
        this->vtable = (void*)&PTR_FUN_00e31080;  // Base vtable

        // Step 2: Initialize the subobject at offset +0x04
        initSubObject(this->subObject);

        // Step 3: Set vtable to derived class vtable (this object's actual vtable)
        this->vtable = (void*)&PTR_LAB_00e31084;  // Derived vtable

        // Step 4: Clear global flag
        g_bSomeGlobalFlag = 0;

        // Step 5: If the object was allocated on the heap, perform post-construct operations
        if (allocFlag & 1) {
            postConstruct(this);
        }
    }
};