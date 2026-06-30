// FUNC_NAME: BaseObject::destroy
// Function address: 0x00683280
// Role: Virtual destructor thunk that delegates to the actual deallocation routine.
// Called as a vtable entry from many derived classes during cleanup.
void BaseObject::destroy(void* object)
{
    FUN_004dafd0(object);
    return;
}