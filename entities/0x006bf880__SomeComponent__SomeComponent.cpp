// FUNC_NAME: SomeComponent::SomeComponent
// Function address: 0x006bf880
// Constructor for a game component. Calls base constructor and optionally allocates internal data of size 0x190 (400).
int __thiscall SomeComponent::SomeComponent(void* this, byte initFlags)
{
    // Base class constructor (address 0x006bf7e0)
    BaseComponent::Constructor(this);
    if (initFlags & 1) {
        // Allocate/initialize internal buffer (likely for component data, address 0x0043b960)
        allocateInternalBuffer(this, 400);
    }
    return (int)this;
}