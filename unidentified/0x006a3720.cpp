// FUN_NAME: BaseObject::setVTable
void __fastcall BaseObject::setVTable(void *thisPtr)
{
    // Set vtable pointer to the class's virtual function table
    *(void ***)thisPtr = &PTR_FUN_00d5d3c8;
}