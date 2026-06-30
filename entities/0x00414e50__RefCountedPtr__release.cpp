// FUNC_NAME: RefCountedPtr::release
// Address: 0x00414e50
// Releases ownership of a ref-counted object, decrementing its reference count
// (+0x04) and calling the virtual destructor (vtable[1]) if the count reaches zero.
// The internal pointer is set to null after release.

class RefCountedPtr {
public:
    void* m_ptr; // +0x00: raw pointer to the ref-counted object

    // Decrement reference and potentially destroy the object
    void __thiscall release() {
        if (m_ptr == nullptr)
            return;

        // Object layout: [vtable ptr (0x00)][refCount (0x04)]
        int* obj = static_cast<int*>(m_ptr);          // treat as int* for compatibility
        int* pRefCount = reinterpret_cast<int*>(
            reinterpret_cast<char*>(obj) + 4          // byte offset +0x04
        );
        int newCount = --(*pRefCount);

        if (newCount == 0) {
            // Fetch vtable (first dword of object) and call destructor (second entry, offset +0x04)
            void** vtable = *reinterpret_cast<void***>(obj);
            typedef void (*Destructor)(void*);
            Destructor dtor = reinterpret_cast<Destructor>(vtable[1]);
            dtor(obj);
        }

        m_ptr = nullptr;
    }
};