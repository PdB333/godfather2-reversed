// FUNC_NAME: Entity::deletingDestructor
// Address: 0x007dbd20 - Scalar deleting destructor for Entity (or derived class).
// Calls the base destructor (at 0x007dacc0), then if the flag's bit 0 is set,
// calls operator delete (at 0x00624da0) to free the memory.

void* __thiscall Entity::deletingDestructor(char destroyFlag)
{
    // Call base class destructor (internal cleanup)
    // This likely invokes ~BaseClass() or ~Entity()
    // Address: 0x007dacc0
    this->entityDestructor();

    // If the flag indicates memory should be freed (bit 0 set)
    if ((destroyFlag & 1) != 0)
    {
        // Call operator delete to release the allocated memory
        // Address: 0x00624da0
        operatorDelete(this);
    }

    return this;
}