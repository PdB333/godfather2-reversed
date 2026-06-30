// FUNC_NAME: Entity::releaseSubObject
void __thiscall Entity::releaseSubObject(void)
{
    // +0x50: pointer to a child component (e.g., AudioComponent, Animation)
    void* pChild = *(void**)(this + 0x50);
    if (pChild != nullptr)
    {
        // FUN_006b0ee0 likely retrieves a sub-resource or container from the child
        void* pSubResource = (void*)FUN_006b0ee0(pChild);
        if (pSubResource != nullptr)
        {
            // +0x40 of pSubResource: handle or pointer to something to release
            // FUN_006be3f0 performs the actual release/cleanup
            FUN_006be3f0(*(uint*)((int)pSubResource + 0x40));
        }
    }
    return;
}