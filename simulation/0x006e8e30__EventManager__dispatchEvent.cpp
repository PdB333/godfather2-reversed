// FUNC_NAME: EventManager::dispatchEvent

void __thiscall EventManager::dispatchEvent(uint *this, EventHandler *handler)
{
    uint *globalEventFlags;

    // Look up global event flags from singleton manager via hash key
    globalEventFlags = (uint *)HashTable::find(0xb284d27b);
    if (globalEventFlags != (uint *)0x0) {
        // Check if the bit corresponding to this object's event flag is set
        if ((*globalEventFlags & *(uint *)(this + 0x4)) != 0) {
            // Call virtual function at vtable offset 100 (likely a 'processActive' handler)
            (**(code **)(*(int *)handler + 100))();
            return;
        }
        // Otherwise call virtual function at offset 104 (likely a 'processInactive' or default handler)
        (**(code **)(*(int *)handler + 104))();
    }
    return;
}