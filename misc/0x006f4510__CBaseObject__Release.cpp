// FUNC_NAME: CBaseObject::Release
// Address: 0x006f4510
// Role: Release method that calls virtual release on child objects, then virtual destroy on self, and optionally deletes memory.

typedef void (__thiscall *VoidFunc)(void*, int);
typedef void (__thiscall *VoidNoArgFunc)(void*);

struct CObjectVTable;

// Forward declaration of a class that uses this pattern
class CBaseObject
{
public:
    virtual int queryInterface(int, void**);     // vtable+0x00
    virtual int addRef(void);                    // vtable+0x04
    virtual int release(void);                   // vtable+0x08
    virtual void destroy(void);                  // vtable+0x0C
    // ... other virtuals

    // Members at known offsets:
    uint32_t m_child1;      // +0x00 (at param_1[0])
    uint32_t field_4;       // +0x04 (unknown)
    uint32_t field_8;       // +0x08 (unknown)
    uint32_t m_child2;      // +0x0C (at param_1[3])
    uint32_t m_vtablePtr;   // +0x10? Actually param_1[4] is at offset 0x10? But let's place it after.
    // The struct size is at least 5*4 = 20 bytes.
};

// The actual function as reconstructed:
CBaseObject* __fastcall CBaseObject::Release(CBaseObject* thisPtr)
{
    // unaff_ESI is a register flag set by caller, bit 0 indicates heap allocation.
    uint unaff_ESI;

    // Get vtable from m_vtablePtr (which is itself a pointer to the vtable of some interface)
    // Actually param_1[4] is at +0x10, but we treat it as a pointer to an object that has a vtable.
    // For clarity, we assume that m_vtablePtr points to an internal object (e.g., a reference manager).
    // The virtual function at vtable+4 (addRef) is called on that internal object, passing thisPtr->m_child1 and 0.
    ((void (__thiscall*)(void*, int))((int*)thisPtr->m_vtablePtr)[1])((void*)thisPtr->m_child1, 0);

    // Call the same function on m_child2 if it is non-null.
    if (thisPtr->m_child2 != 0)
    {
        ((void (__thiscall*)(void*, int))((int*)thisPtr->m_vtablePtr)[1])((void*)thisPtr->m_child2, 0);
    }

    // Call the virtual function at vtable+12 (destroy) on the internal object, with no extra arguments.
    ((void (__thiscall*)(void*))((int*)thisPtr->m_vtablePtr)[3])((void*)thisPtr->m_vtablePtr);

    // If the object was dynamically allocated (bit 0 of unaff_ESI set), free it.
    if ((unaff_ESI & 1) != 0)
    {
        FUN_009c8eb0(thisPtr);  // Likely operator delete or custom deallocator
    }

    return thisPtr;
}