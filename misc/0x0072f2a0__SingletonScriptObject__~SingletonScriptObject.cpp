// FUNC_NAME: SingletonScriptObject::~SingletonScriptObject

// This is a destructor for a class that manages a dynamically allocated child object.
// The child pointer is at offset +0x04. The destructor releases the child, then
// re-points the vtable to a base class, and optionally deallocates this object.
class SingletonScriptObject {
public:
    // VTable pointer at +0x00 (set to base class vtable at end)
    // Pointer to managed child object at +0x04
    void* m_childObject; // +0x04

    // Destructor, returns this pointer (__thiscall)
    // param_2: if bit 0 set, deallocate memory for this object (operator delete)
    SingletonScriptObject* __thiscall destructor(byte deallocFlag) {
        if (m_childObject != nullptr) {
            // Release the child object – likely decrement refcount or delete
            releaseChildObject(&m_childObject);
        }
        // Reset vtable to base class (to prevent double deletion via derived)
        this->vtable = &gSingletonScriptObjectVTableBase;
        if (deallocFlag & 1) {
            deallocateMemory(this);
        }
        return this;
    }
};

// External helper functions (their definitions are elsewhere)
void releaseChildObject(void** objPtr);
void deallocateMemory(void* ptr);