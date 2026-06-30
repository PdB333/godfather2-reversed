// FUNC_NAME: EA::EARS::Framework::BaseObject::~BaseObject

void __fastcall EA::EARS::Framework::BaseObject::~BaseObject(void* this)
{
    // Set vtable to the "destructing" variant (base class destructor start)
    *(void**)this = &PTR_FUN_00e3abdc;   // +0x00: vtable pointer set to destructing vtable

    // Get internal reference object (offset +0x04)
    void* internalObj = *(void**)((char*)this + 4);

    // Call Release on the internal object with a parameter from offset +0x20
    (**(code**)(*(int*)internalObj + 4))((void*)((char*)this + 0x20), 0);

    // Check optional secondary object at offset +0x0C
    void* optionalObj = *(void**)((char*)this + 0x0C);
    if (optionalObj != 0) {
        // Set global singleton to the internal object
        _DAT_01205558 = internalObj;
        // Call Release on the base of optionalObj (subtracting 4 to get base object)
        (**(code**)(*(int*)internalObj + 4))((void*)((char*)optionalObj - 4), 0);
        _DAT_01205558 = internalObj; // likely redundant
    }

    // Call Cleanup (or similar) on the internal object (vtable+0x0C)
    (**(code**)(*(int*)internalObj + 0x0C))();

    // Set vtable to the "destroyed" variant (final vtable after destruction)
    *(void**)this = &PTR_LAB_00e3abe0;

    // Clear a global destruction flag
    DAT_012234e8 = 0;
}