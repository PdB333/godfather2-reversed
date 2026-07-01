// FUNC_NAME: RefCountedObject::~RefCountedObject
// Destructor for a reference-counted base object.
// Sets vtable to base, decrements refcount on shared sub-object, clears weak pointer, then calls base destruction and optionally frees this.
void __thiscall RefCountedObject::~RefCountedObject(byte freeThis)
{
    int* refCountPtr;

    // Reset vtable to base (destructor cleanup)
    this->vtable = &BASE_VTABLE;

    // If shared sub-object exists (field at +0x24)
    if (this->sharedObject != 0)
    {
        // Decrement reference count at offset +0x04 of shared object
        refCountPtr = (int*)(this->sharedObject + 4);
        --*refCountPtr;

        // If ref count became zero, call virtual destructor of shared object
        if (*(int*)(this->sharedObject + 4) == 0)
        {
            // Vtable pointer at +0x00 of shared object, destructor at vtable+4
            (*(void(__thiscall**)(void*))(*(int*)this->sharedObject + 4))(this->sharedObject);
        }
        this->sharedObject = 0;
    }

    // Clear weak/easily-ownable sub-object (field at +0x20)
    if (this->subObject != 0)
    {
        // Set some field at +0x08 to null
        *(undefined4*)(this->subObject + 8) = 0;
        this->subObject = 0;
    }

    // Common base destruction routine (e.g., unregister from managers)
    RefCountedObject::baseDestroy();

    // If caller requested deletion, free this object via operator delete
    if (freeThis & 1)
    {
        operatorDelete(this);
    }
}