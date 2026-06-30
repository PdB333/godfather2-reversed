// FUNC_NAME: UnknownClass::UnknownClass

// Constructor at 0x00685440
// Seems to be a derived class with multiple inheritance (three vtable pointers at offsets 0x00, 0x3C, 0x48)
// param_2 is a boolean flag for heap allocation; if set, calls a custom deallocation function.

class UnknownClass : public BaseClass1, public BaseClass2, public BaseClass3 // guessed inheritance order
{
public:
    void * __thiscall UnknownClass(byte isHeapAllocated);
};

// Forward declarations of base class constructors (the addresses are 0x006b8060 and 0x0046c640)
void __thiscall BaseClass1::BaseClass1(void); // called with this
void __thiscall BaseClass2::BaseClass2(void); // called with this

// Custom deallocation function at 0x0043b960, size likely 0x74 bytes
void __stdcall customObjectDelete(void *obj, uint size); // FUN_0043b960

void * __thiscall UnknownClass::UnknownClass(byte isHeapAllocated)
{
    // Set initial vtable pointers (likely for this derived class)
    *(void**)this = (void*)0x00d58928;      // +0x00: main vtable
    *(void**)((char*)this + 0x3C) = (void*)0x00d58918; // +0x3C: secondary vtable
    *(void**)((char*)this + 0x48) = (void*)0x00d58914; // +0x48: tertiary vtable

    // Call first base class constructor (at 0x006b8060)
    // This constructor may set its own vtable, overwriting the pointers above.
    BaseClass1::BaseClass1();

    // After base constructor, re‑set derived class vtable pointers
    *(void**)this = (void*)0x00d5888c;
    *(void**)((char*)this + 0x3C) = (void*)0x00d5887c;
    *(void**)((char*)this + 0x48) = (void*)0x00d58878;

    // Call second base class constructor (at 0x0046c640)
    BaseClass2::BaseClass2();

    // If the object was heap‑allocated, perform cleanup (custom delete)
    if (isHeapAllocated & 1) {
        customObjectDelete(this, 0x74); // 0x74 = sizeof(UnknownClass)
    }

    return this;
}