// FUNC_NAME: Entity::getComponentOwner
// Function at 0x00691810: returns the owning object of a component stored at offset 0x74c
int __thiscall Entity::getComponentOwner(void)
{
    // 0x74c = component pointer (likely derived from some component system)
    int* componentPtr = *(int**)(this + 0x74c); // dereference field at +0x74c
    if (componentPtr != NULL)
    {
        // The component is embedded in its owner at offset 0x48, subtract to get owner
        return (int)(componentPtr - 0x48); // cast to int since return is pointer-sized
    }
    return 0;
}