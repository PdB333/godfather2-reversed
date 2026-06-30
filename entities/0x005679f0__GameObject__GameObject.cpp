// FUNC_NAME: GameObject::GameObject
uint __thiscall GameObject::GameObject(byte initFlags)
{
    // Call the base initialization routine (FUN_00567a20)
    this->initializeBase();
    // If the lowest bit is set, perform additional cleanup (likely a special path for reuse/recycle)
    if ((initFlags & 1) != 0) {
        this->destroySubResources(); // Calls cleanup function (FUN_009c8eb0)
    }
    // Return the this pointer as required by the calling convention
    return (uint)this;
}