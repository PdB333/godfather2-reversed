// FUNC_NAME: Object::Constructor
void* __fastcall Object::Constructor(void* thisPointer)
{
    initializeBaseMembers(); // Calls base class initializer at 0x004ca180
    return thisPointer;
}