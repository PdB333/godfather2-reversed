// FUNC_NAME: EARSObject::destructor (or similar, based on cleanup pattern)
// Address: 0x004c38e0
// Role: Destructor for an object with two resource pointers: one at offset 0 (sub-object with internal resource at +0x30) and another at offset 0x14.
// Calls base destructor (FUN_00498180), then releases the resource at +0x14, then conditionally releases sub-object and its internal resource.

class EARSObject { // Hypothetical class, adjust as needed
public:
    // +0x00: Pointer to dynamically allocated sub-object (vtable base? or another resource)
    // +0x14: Another resource handle/pointer
    // (actual layout may vary)

private:
    // Declared only to show offsets; not actual members
    void* m_pSubObject;   // offset 0x00
    // padding? but apparently +0x14 is int param_1[5] so it's 4*5 = 20 bytes offset
    void* m_pResource;    // offset 0x14

    // Internal helper functions (from callees)
    static void releaseHandle(void* p) __fastcall; // FUN_009c8f10: release/free a handle
    static void deleteObject(void* p) __fastcall;   // FUN_009c8eb0: delete a heap object

    void baseCleanup() __fastcall; // FUN_00498180

public:
    __thiscall ~EARSObject() {
        baseCleanup();                      // call base class destructor or common cleanup
        releaseHandle(m_pResource);         // release the resource at offset 0x14
        if (m_pSubObject) {
            // Sub-object has its own resource at offset 0x30 (relative to sub-object pointer)
            releaseHandle(*((void**)m_pSubObject + 0x30 / sizeof(void*))); // offset 0x30
            deleteObject(m_pSubObject);
        }
    }
};

// Static helpers definition (implementation not shown)
void __fastcall EARSObject::releaseHandle(void* p) { /* deallocate/release */ }
void __fastcall EARSObject::deleteObject(void* p) { /* operator delete */ }
void __fastcall EARSObject::baseCleanup() { /* base destructor actions */ }