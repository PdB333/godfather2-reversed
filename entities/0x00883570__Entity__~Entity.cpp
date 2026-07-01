// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(Entity* this)
{
    // Set vtable to base class to prevent virtual calls during destruction
    this->vtable = &BASE_CLASS_VTABLE;

    // Check if we have a child object and the "hasChild" flag (bit 0 at +0x74)
    if ((this->flags & 1) != 0 && this->childObject != nullptr)
    {
        // If child has a specific resource (at +0x4A8), release it
        if (*(int*)(this->childObject + 0x4A8) != 0)
        {
            stopAllSounds(0);
            // Check if child's flag at +0x1B94 bit 0x15 is clear, then enable something
            if ((*(uint*)(this->childObject + 0x1B94) >> 0x15 & 1) == 0)
            {
                enableSomething(1, 1);
            }
        }
        disableSomething(0);
        setState(4);
        // If "detach" flag (bit 2 at +0x74) is set, detach from parent
        if ((this->flags >> 2 & 1) != 0)
        {
            detachFromParent();
        }
    }

    // If child exists, set its state to 79 (likely "destroyed")
    if (this->childObject != nullptr)
    {
        setState(0x4F);
    }

    // If child exists and "releaseChild" flag (bit 3 at +0x74) is set, call child's virtual release
    if (this->childObject != nullptr && (this->flags >> 3 & 1) != 0)
    {
        (*(void (**)(void))(*(int*)this->childObject + 0x7C))();
    }

    // Release the pointer at +0x50
    if (this->somePointer != nullptr)
    {
        releasePointer(&this->somePointer);
    }

    // Final base cleanup
    baseCleanup();
}