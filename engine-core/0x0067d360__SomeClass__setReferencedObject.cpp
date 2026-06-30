// FUNC_NAME: SomeClass::setReferencedObject
// Function address: 0x0067d360
// Role: Replace a reference-counted object pointer at +0x20, releasing the old one and adding a reference to the new one.

class RefCounted {
public:
    virtual void QueryInterface(int riid, void** ppvObj) = 0; // vtable[0] (offset 0x0)
    virtual void AddRef() = 0;                                 // vtable[1] (offset 0x4)
    virtual void Release() = 0;                                // vtable[2] (offset 0x8)
    // There is an additional virtual at offset 0xc (possibly another release or method)
    virtual void UnknownRelease() = 0;                         // vtable[3] (offset 0xc)
};

class SomeClass {
private:
    RefCounted* m_pRefCounted; // +0x20

public:
    void setReferencedObject(RefCounted* newPtr) {
        // Release the existing pointer if any
        if (m_pRefCounted != nullptr) {
            // Call vtable[3] (offset 0xc) - likely Release or similar
            m_pRefCounted->UnknownRelease();
        }

        // Assign new pointer
        m_pRefCounted = newPtr;

        // AddRef the new pointer if non-null
        if (newPtr != nullptr) {
            // Call vtable[2] (offset 0x8) - likely AddRef or similar
            newPtr->AddRef();
        }
    }
};