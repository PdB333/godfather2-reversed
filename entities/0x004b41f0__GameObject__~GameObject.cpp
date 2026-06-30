// FUNC_NAME: GameObject::~GameObject
// 0x004b41f0: Scalar deleting destructor for GameObject (size 0x870)
// Calls base destructor and conditionally frees memory via sized operator delete.
GameObject * __thiscall GameObject::~GameObject(GameObject *this, byte flags)
{
    // Call base class destructor (FUN_004b3c50)
    this->BaseClass::~BaseClass();

    // If flags bit 0 is set, this is a "deleting" destructor (called from operator delete)
    if (flags & 1)
    {
        // Retrieve the global delete function table (static pointer from FUN_009c8f80)
        // The table holds function pointers; offset +4 is sized operator delete.
        typedef void (*DeleteFn)(void *ptr, unsigned int size);
        int *pTable = (int *)FUN_009c8f80(); // returns pointer to static table of ints (function pointers)
        DeleteFn sizedDelete = (DeleteFn)pTable[1];
        sizedDelete(this, 0x870); // sizeof(GameObject) == 0x870
    }
    return this;
}