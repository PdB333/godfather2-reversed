// FUNC_NAME: EntityObject::processLinkedData
void EntityObject::processLinkedData()
{
    // Check if bit 2 at offset 0x5e is set (likely a "has pending links" flag)
    if ((*(byte *)(this + 0x5e) & 2) != 0)
    {
        // Look up a data binding by hash 0x5e1f74a6 in the hash table at offset 0x20
        int bindingA = findDataByHash(this + 0x20, 0x5e1f74a6, 0xffffffff);
        if (bindingA != 0 && (*(undefined4 *)(bindingA + 0xc) != (undefined4 *)0x0))
        {
            // Copy the value from offset 0xc of the binding to offset 0x60 of this object
            *(undefined4 *)(this + 0x60) = *(undefined4 *)(bindingA + 0xc);
        }

        // Look up a second binding by hash 0x137726b7
        int bindingB = findDataByHash(this + 0x20, 0x137726b7, 0xffffffff);
        if (bindingB != 0)
        {
            // If found, trigger a global action (e.g. notify, initialize)
            triggerBindingAction();
        }
    }
}