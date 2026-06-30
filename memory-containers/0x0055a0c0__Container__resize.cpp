// FUNC_NAME: Container::resize
// Address: 0x0055a0c0
// Role: Resize a dynamic array of 0x70-byte elements, moving existing elements and releasing references.

// Forward declaration for ref-counted object
class RefCountedObject {
public:
    virtual void destroy(int reason); // vtable+0: destructor
    // +0x04: short refCount? (not directly used here)
    // +0x06: short weakRefCount? (decremented here)
};

// Global default allocator (from DAT_01218a14)
extern Allocator gDefaultAllocator;

// Allocator vtable (first function: allocate, second: free)
struct AllocatorVtable {
    void* (*allocate)(size_t size, Allocator* allocator);
    void  (*free)(void* ptr, Allocator* allocator);
};

struct Container {
    void*           data;       // +0x00: array of elements (each 0x70 bytes)
    int             count;      // +0x04: number of initialized elements
    int             capacity;   // +0x08: current capacity (max elements)
    Allocator*      allocator;  // +0x0C: allocator (if null, use gDefaultAllocator)
    AllocatorVtable* allocVtable; // +0x10: vtable for allocation functions
};

// Placeholder for copy-constructing a new element (FUN_005567b0)
void placementNewElement(void* dst); 

// Decrement ref count and possibly destroy (FUN_00557020, but inline here for clarity)
void releaseRefCountedObject(RefCountedObject* obj) {
    if (obj == nullptr) return;
    short* refCounts = reinterpret_cast<short*>(obj); // +0x04 and +0x06
    if (*(refCounts + 1) != 0) { // +0x04 non-zero? Actually original: *(short *)(puVar1 + 1) -> offset 2? Let's assume offset 4 and 6
        // Decrement "weak" or secondary refcount at offset 6
        *(refCounts + 3) -= 1; // offset +6 as short
        if (*(refCounts + 3) == 0) {
            // Call destructor (vtable[0] with reason 1)
            obj->destroy(1);
        }
    }
}

void Container::resize(uint newCapacity) {
    if ((uint)capacity < newCapacity) {
        // Allocate new buffer
        Allocator* alloc = allocator ? allocator : &gDefaultAllocator;
        void* newData = allocVtable->allocate(newCapacity * 0x70, alloc);
        if (data != nullptr) {
            // Move existing elements
            char* oldPtr = static_cast<char*>(data);
            char* newPtr = static_cast<char*>(newData);
            for (int i = 0; i < count; ++i) {
                // Initialize new element (copy constructor)
                if (newPtr != nullptr) {
                    placementNewElement(newPtr);
                }
                // Handle ref-counted object at old element offset +0x40
                RefCountedObject** refObjPtr = reinterpret_cast<RefCountedObject**>(oldPtr + 0x40);
                RefCountedObject* refObj = *refObjPtr;
                if (refObj != nullptr) {
                    releaseRefCountedObject(refObj);
                    *refObjPtr = nullptr; // Clear old pointer
                }
                oldPtr += 0x70;
                newPtr += 0x70;
            }
            // Free old buffer using allocator's free function
            allocVtable->free(data, alloc);
        }
        data = newData;
        capacity = newCapacity;
    }
}