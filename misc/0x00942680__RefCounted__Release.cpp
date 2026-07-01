// FUNC_NAME: RefCounted::Release
// Address: 0x00942680
// This function appears to be a release/decrement-refcount method for a reference-counted object.
// It uses a vtable pointer at offset 0x10 from this, with methods at offsets 4 and 12.
// Arguments: ECX = this, EDX (unaff_ESI) = flag indicating whether to deallocate memory (1 = delete).
// Sub-objects at offsets 0x00 and 0x0C are released first, then a shutdown/destroy call is made,
// and finally memory is freed if requested.

typedef unsigned int uint;
typedef void* void_ptr;

// Forward declaration of the object class
class RefCounted;

// Vtable layout for the sub-object (offset 0x10)
struct VtableLayout {
    void* method0;       // +0x00
    void* method4;       // +0x04  // release(object, flag)
    void* method8;       // +0x08
    void* methodC;       // +0x0C  // shutdown/destroy()
};

class RefCounted {
public:
    void* field_0;       // +0x00  // first sub-object pointer
    // ... unknown fields at +0x04 and +0x08 ...
    void* field_C;       // +0x0C  // second sub-object pointer (optional)
    VtableLayout* m_pVtable; // +0x10  // pointer to vtable of associated object
};

// External deallocation function (operator delete equivalent)
void __fastcall operatorDelete(void* ptr); // FUN_009c8eb0

void __fastcall RefCounted::Release(RefCounted* this, uint deallocFlag)
{
    // Release first sub-object
    void* subObj1 = this->field_0;
    VtableLayout* vtable = this->m_pVtable;
    // vtable->method4 is a release function taking (object, flag)
    (*(void (__fastcall**)(void*, int))&vtable->method4)(subObj1, 0);

    // Release second sub-object if non-null
    void* subObj2 = this->field_C;
    if (subObj2 != nullptr) {
        (*(void (__fastcall**)(void*, int))&vtable->method4)(subObj2, 0);
    }

    // Call shutdown/destroy on the associated object
    (*(void (__fastcall**)())&vtable->methodC)();

    // If deallocation flag is set (low bit), free memory
    if (deallocFlag & 1) {
        operatorDelete(this);
    }
}