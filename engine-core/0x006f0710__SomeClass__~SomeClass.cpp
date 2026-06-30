// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(int this)
{
    // Call base class destructor (0x006fbc70)
    BaseClass::~BaseClass(); // FUN_006fbc70

    // If the pointer at offset +0x4 is non-null, release it (0x004daf90)
    if (*(int *)(this + 4) != 0) {
        ReleaseObjectReference(*(int *)(this + 4)); // FUN_004daf90
    }
    return;
}