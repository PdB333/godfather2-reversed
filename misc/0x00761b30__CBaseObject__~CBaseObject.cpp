// FUNC_NAME: CBaseObject::~CBaseObject
// Address: 0x00761b30
// Role: Complete object destructor for a class with a virtual base at offset 0x04.
//       Sets vtable to destructor vtable, destroys virtual base subobject if present,
//       then sets vtable to purecall to prevent accidental virtual dispatch.

// Forward declaration of the virtual base subobject type (offset 0x04 from outer object)
struct VirtualBaseSubObject
{
    void** vtable; // +0x00
    // Additional members unknown
};

// Outer class containing the virtual base subobject
struct CBaseObject
{
    void** vtable;                 // +0x00
    VirtualBaseSubObject virtualBase; // +0x04 (virtual base subobject)
};

// Destructor for the virtual base subobject (callee at 0x004daf90)
extern void __fastcall VirtualBaseSubObjectDestructor(VirtualBaseSubObject* pBase);

// Global vtable pointers (set by the constructor)
extern void* PTR_FUN_00d654d0;  // CBaseObject::vtable for destructor (complete object destructor)
extern void* PTR___purecall_00e407a4; // vtable that calls pure virtual function handler

void __fastcall CBaseObject::~CBaseObject(CBaseObject* this)
{
    // Step 1: Switch vtable to the destructor-specific vtable
    this->vtable = (void**)&PTR_FUN_00d654d0;

    // Step 2: If the virtual base subobject has been constructed (its vtable non-null),
    //         destroy it by calling its destructor.
    if (this->virtualBase.vtable != nullptr)
    {
        VirtualBaseSubObjectDestructor(&this->virtualBase); // destroys subobject at this+4
    }

    // Step 3: Replace vtable with purecall handler to prevent any dangling virtual calls
    this->vtable = (void**)&PTR___purecall_00e407a4;
}