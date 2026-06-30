// FUNC_NAME: RefCountedPtr::constructor
// Function address: 0x005a1c50
// Reconstructed C++ for a smart pointer constructor with reference counting.
// The class holds a pointer to a reference-counted object (first field is refcount).
// The constructor initializes the smart pointer, increments the object's refcount,
// then immediately decrements it (likely a bug in decompilation or part of a different path).
// If the refcount reaches zero, the object is destroyed and freed.

class RefCountedPtr {
public:
    int m_refCount;          // +0x00: smart pointer's own reference count (set to 0)
    int* m_object;           // +0x04: pointer to the managed object
    int m_typeId;            // +0x08: some identifier (passed in EAX)
    char m_flag;             // +0x0C: flag byte (set to 0)

    // Constructor: takes a raw pointer to a reference-counted object and a type ID.
    // __thiscall: 'this' in ECX, object in stack, typeId in EAX (register)
    void __thiscall constructor(int* object, int typeId) {
        m_refCount = 0;
        m_object = object;
        m_typeId = typeId;
        m_flag = 0;

        if (object != nullptr) {
            // Increment the object's reference count (first field at offset 0)
            *object = *object + 1;
        }

        // The following code appears to decrement the object's refcount and possibly destroy it.
        // This is unusual for a constructor; may be a decompilation artifact or part of a different function.
        if (object != nullptr) {
            *object = *object - 1;
            if (*object == 0) {
                // Call object destructor (FUN_005a1b40) and free memory (size 0x30)
                FUN_005a1b40();  // likely destructor for the object
                (*DAT_0119caf8)(object, 0x30);  // deallocation function
            }
        }
    }
};