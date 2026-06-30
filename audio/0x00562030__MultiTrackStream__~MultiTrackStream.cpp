// FUNC_NAME: MultiTrackStream::~MultiTrackStream

// Destructor for MultiTrackStream (EA EARS engine streaming class).
// Cleans up subobjects at offsets +0x8C and +0x90, plus dynamic members at +0x88 and +0xC0.
// Vtables are managed manually during destruction to prevent re-entrancy.

// Forward declarations of external vtable/label symbols (from other translation units)
extern void* PTR_FUN_00e3a428;    // Destructor-stage vtable
extern void* PTR_FUN_00e3a038;    // Sub-object vtable (base class)
extern void* PTR_LAB_00e3a054;    // Another sub-object vtable
extern void* PTR_LAB_00dc3dd4;    // Final vtable (purecall guard)
extern void* PTR___purecall_00e3924c; // Purecall barrier

// Helper functions (unknown but present in binary)
extern void FUN_009f01a0();
extern void FUN_009f1b20(void* arg);

// Forward declaration of the sub-object class (at offset +0x8C)
class MultiTrackStreamSubObject {
public:
    void* vtable; // +0x00
    // ... remaining members
};

// Main class definition
class MultiTrackStream {
public:
    void* vtable;                 // +0x00

    // Fields derived from param_1 offsets
    char unknown_0x04[0x84];      // +0x04–0x84: padding / other members
    void* field_0x88;             // +0x88: pointer to managed resource (e.g., buffer)
    MultiTrackStreamSubObject* subObject; // +0x8C: embedded sub-object
    void* subObjectVtable2;       // +0x90: vtable pointer for second sub-object
    char unknown_0x94[0x2C];      // +0x94–0xBF: padding
    void* field_0xC0;             // +0xC0: another dynamically allocated object

    // Destructor (__fastcall, this in ECX, implied)
    void __fastcall destroy();
};

void __fastcall MultiTrackStream::destroy()
{
    // Set this object's vtable to destructor-specific vtable
    this->vtable = &PTR_FUN_00e3a428;

    // Release resource at +0x88 if non-null
    if (this->field_0x88 != nullptr) {
        FUN_009f01a0();
    }

    // Call sub-object's virtual destructor at vtable offset +0x18 (index 6)
    // The sub-object is at offset +0x8C
    void (__fastcall* subDestroy)(MultiTrackStreamSubObject*, void*, int) =
        *(void (__fastcall**)(MultiTrackStreamSubObject*, void*, int))
            ((char*)this->subObject->vtable + 0x18);
    this->field_0x88 = nullptr;   // Clear resource pointer before destruction
    subDestroy(this->subObject, nullptr, 0); // ECX, EDX (implicit), arg0 = 0

    // Repoint sub-object's vtable to a base class vtable
    this->subObject->vtable = &PTR_FUN_00e3a038;

    // Set second sub-object's vtable at +0x90
    this->subObjectVtable2 = &PTR_LAB_00e3a054;

    // If dynamic object at +0xC0 exists, destroy it
    if (this->field_0xC0 != nullptr) {
        FUN_009f1b20(&this->subObject);  // Probably cleans up the sub-object region
        FUN_009f01a0();                   // Release associated memory
    }

    // Final vtable swaps – install purecall guards to prevent accidental calls
    this->subObjectVtable2 = &PTR_LAB_00dc3dd4;
    this->subObject->vtable = &PTR___purecall_00e3924c;
}