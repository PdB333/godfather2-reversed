// FUNC_NAME: Asset::~Asset
// Function address: 0x00549cb0
// Role: Destructor for Asset class that releases a reference-counted sub-object.
// The Asset holds a pointer at +0xC0 to a sub-object (ResObject) with its own vtable at offset 0,
// and a reference count stored as a short at offset 6 (with a check short at offset 4).
// The destructor sets the Asset's vtable to a 'destructed' vtable and then releases the sub-object.

class Asset {
public:
    // +0x00: vtable pointer (implicit, set here to destructor-specific vtable)
    // +0xC0: pointer to a reference-counted sub-object (ResObject)
    void* m_resObject;  // actual type: ResObject*

    virtual ~Asset() {
        // Replace vtable with a known destructor vtable to avoid double-destruction
        *(void**)this = &PTR_FUN_00e39bc8;

        if (m_resObject != nullptr) {
            // The sub-object has two shorts at offsets 4 and 6.
            // Offset 4: a flag indicating that this sub-object has references (non‑zero = active)
            short* flagPtr = (short*)((int)m_resObject + 4);
            // Offset 6: the actual reference count
            short* refCountPtr = (short*)((int)m_resObject + 6);

            if (*flagPtr != 0) {
                (*refCountPtr)--;
                if (*refCountPtr == 0) {
                    // Call the first virtual function of the sub‑object (release/delete) with arg 1
                    void** vtable = *(void***)m_resObject;
                    using ReleaseFunc = void (__fastcall*)(void*, int);
                    ReleaseFunc release = (ReleaseFunc)vtable[0];
                    release(m_resObject, 1);
                }
            }
            m_resObject = nullptr;
        }
    }
};