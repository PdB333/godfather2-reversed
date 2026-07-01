// FUNC_NAME: Entity::setActive
void __thiscall Entity::setActive(bool enable)
{
    ushort *flags = reinterpret_cast<ushort *>(this + 0xC8);
    int *controllerPtr = reinterpret_cast<int *>(this + 0x50);

    if (enable) {
        // Clear inactive flag (bit 6)
        *flags &= ~0x40;
        // If we have a controller/component, notify it via virtual call
        if (*controllerPtr != 0) {
            int *vtable = reinterpret_cast<int *>(*controllerPtr - 0x48);
            char dummy = 0;
            // 0x10e5319e is likely a hash for an event like "onActivated"
            (reinterpret_cast<void (__stdcall *)(int, char *)>(*(int *)(*vtable + 0x10)))(0x10e5319e, &dummy);
        }
        // Perform any post-activation updates
        FUN_008622a0();
    } else {
        // Set inactive flag (bit 6) and clear active flag (bit 0)
        *flags |= 0x40;
        *flags &= ~0x1;
    }
}