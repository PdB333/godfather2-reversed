// FUNC_NAME: EarsMissionObjective::EarsMissionObjective
void __fastcall EarsMissionObjective::EarsMissionObjective(EarsMissionObjective* this)
{
    // Store base class vtable (EarsMissionObject) before calling base constructor
    *(void**)this = (void*)&EarsMissionObject_vtable;   // +0x00: vtable pointer
    // Call base class constructor (sets up base subobject)
    ((void (__fastcall*)(EarsMissionObjective*))0x0043e380)(this);
    // Update vtable to derived class after base initialization
    *(void**)this = (void*)&EarsMissionObjective_vtable; // +0x00: vtable pointer
}