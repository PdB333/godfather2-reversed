// FUNC_NAME: BaseClass::~BaseClass
// Function address: 0x00728dd0
// Destructor for a game object with a child pointer at +0x08.
// The 'flags' parameter indicates whether to free memory (bit0).
// Releases sub-object at offset +0x08, then sets vtable to base class vtable,
// and optionally deallocates the object.

class BaseClass;

// Forward declarations of internal helpers (names inferred from usage)
void __fastcall releaseSubObject(void** ppSubObj);  // Releases and nullifies the pointed sub-object
void __fastcall deallocateMemory(BaseClass* ptr);   // Operator delete or custom deallocator

// Vtable pointer of the base class (symbolic name, actual address 0x00e2f0c0)
extern void* BASE_CLASS_VTABLE;

BaseClass* __thiscall BaseClass::~BaseClass(BaseClass* this, unsigned char flags)
{
    // Check if the sub-object pointer at offset +0x08 is non-null
    void** ppSubObject = reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 8);
    if (*ppSubObject != nullptr) {
        releaseSubObject(ppSubObject); // Release and nullify
    }

    // Set the vtable to the base class vtable (to avoid virtual calls during destruction)
    *reinterpret_cast<void**>(this) = &BASE_CLASS_VTABLE;

    // If the low bit of flags is set, deallocate the memory
    if ((flags & 1) != 0) {
        deallocateMemory(this);
    }

    return this;
}