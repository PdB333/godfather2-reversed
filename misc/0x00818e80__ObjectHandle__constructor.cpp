// FUNC_NAME: ObjectHandle::constructor
// Address: 0x00818e80
// Role: Constructor for a small handle/object wrapper.
// Stores an object pointer and optionally registers it with a numeric handle,
// calling the object's third virtual function (likely AddRef or Init).

class ObjectHandle {
public:
    void* m_object; // +0x00: Pointer to the referenced object
    int m_handle;   // +0x04: Handle or registration ID (0 if none provided)

    // __thiscall: ECX = this
    void __thiscall constructor(void* obj, int handle) {
        m_object = obj;
        // Call the third virtual function on the object (vtable offset +0x08)
        // Typical uses: AddRef, Init, or Activate
        (*(void (__thiscall**)(void*))(*(int*)m_object + 8))();
        if (handle != 0) {
            // Register the object with the given handle, store returned ID
            m_handle = registerObjectHandle(handle, m_object);
        } else {
            m_handle = 0;
        }
    }
};

// Declaration for the external registration function (FUN_004265d0)
int __cdecl registerObjectHandle(int handle, void* obj);