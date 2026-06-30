// FUNC_NAME: EARSFrameworkObject::~EARSFrameworkObject
void __fastcall EARSFrameworkObject::~EARSFrameworkObject(int this_)
{
    undefined local_8[8]; // Unused temporary buffer

    // Detach or copy the owned object? 
    // Arguments: temp buffer, this, double-deref of owned pointer, this again, owned pointer
    FUN_006961f0(local_8, this_, **(int**)(this_ + 4), this_, *(int**)(this_ + 4));

    // Delete the owned object (typically operator delete or destructor call)
    FUN_009c8eb0(*(int*)(this_ + 4));

    // Clear references: owned pointer and another field (likely reference count or sibling pointer)
    *(int*)(this_ + 4) = 0; // +0x4: owned object pointer
    *(int*)(this_ + 8) = 0; // +0x8: e.g., reference count or second pointer
    return;
}