// FUNC_NAME: SomeEARSObject::SomeEARSObject (constructor)
void __fastcall SomeEARSObject::constructor(void *thisPointer)
{
    // Set initial vtable pointer to base class virtual table (PTR_FUN_00e322ec)
    *(void **)thisPointer = &PTR_FUN_00e322ec;

    // Call base class constructor (likely for some core object)
    FUN_0043e380(thisPointer);

    // Overwrite vtable pointer with derived class virtual table (PTR_LAB_00e30ea0)
    *(void **)thisPointer = &PTR_LAB_00e30ea0;

    return;
}