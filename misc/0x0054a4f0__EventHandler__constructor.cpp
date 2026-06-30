// FUNC_NAME: EventHandler::constructor
// Address: 0x0054a4f0
// Role: Constructor for EventHandler class. Initializes fields, stores owner pointer, calls a virtual function on the owner, and releases four static resources.
// Fields: +0x00 vtable, +0x04 someFlag (int), +0x08 owner (void*), +0x0C field_C (int), +0x10 field_10 (int), +0x14 field_14 (int)

void __fastcall EventHandler::constructor(void* param_1) // param_1 passed in ECX, usually owner pointer
{
    // this pointer is in ESI (unaff_ESI)
    // Note: In the decompiler, unaff_ESI represents the 'this' pointer.
    this->someFlag = 0;            // +0x04
    this->owner = param_1;          // +0x08
    this->vtable = &PTR_LAB_00e39c3c; // +0x00, set class vtable
    this->field_C = 0;              // +0x0C
    this->field_10 = 0;             // +0x10
    this->field_14 = 0;             // +0x14

    // Call virtual function at index 2 (offset 8) on the owner object.
    // The owner is assumed to have a vtable and the function does some initialization/release.
    (**(code **)(*(int *)this->owner + 8))();

    // Release four static resources (likely strings or handles)
    FUN_0049c6e0(&PTR_LAB_00e39bd8, 1);   // deallocate resource
    FUN_0049c6e0(&DAT_00e39bdc, 1);       // deallocate resource
    FUN_0049c6e0(&DAT_00e39be0, 1);       // deallocate resource
    FUN_0049c6e0(&DAT_00e39be4, 1);       // deallocate resource

    return;
}