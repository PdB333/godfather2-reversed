// FUNC_NAME: BaseObject::~BaseObject

class BaseObject {
public:
    // vtable pointer (offset +0x00)
    void** vtable;

    // pointer to a reference-counted child object (offset +0x20)
    int* m_pChild;

    // Destructor
    void __thiscall ~BaseObject(unsigned char flags) {
        // Decrement reference count on child object if it exists
        if (m_pChild != nullptr) {
            int* refCount = reinterpret_cast<int*>(m_pChild + 1); // +0x04
            (*refCount)--;

            // If reference count reaches zero, delete child via its virtual destructor
            if (*refCount == 0) {
                void** childVtable = reinterpret_cast<void**>(*m_pChild);
                void (__thiscall* childDestructor)(int*) = reinterpret_cast<void (__thiscall*)(int*)>(childVtable[1]); // vtable+4
                childDestructor(m_pChild);
            }

            m_pChild = nullptr;
        }

        // Switch vtable to base class
        vtable = &PTR_LAB_00e3729c;

        // If flags indicate deallocation, free memory
        if (flags & 1) {
            void* allocator = reinterpret_cast<void*>(FUN_009c8f80());
            void (__thiscall* deallocate)(BaseObject*, int) = reinterpret_cast<void (__thiscall*)(BaseObject*, int)>(*(int*)allocator + 4);
            deallocate(this, 0);
        }
    }
};