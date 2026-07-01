// FUNC_NAME: Entity::~Entity
// Function at 0x009902e0: Destructor for Entity class - scalar deleting destructor pattern
void* __thiscall Entity::~Entity(unsigned char flags)
{
    // Call base class destructor or common cleanup
    destroyBase();
    // If the flag has bit 0 set, release memory (scalar deleting destructor)
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }
    return this;
}