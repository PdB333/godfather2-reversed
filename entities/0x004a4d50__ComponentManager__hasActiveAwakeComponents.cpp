// FUNC_NAME: ComponentManager::hasActiveAwakeComponents
// Address: 0x004a4d50
// Iterates an array of Component objects (size 0x10 each) stored at this+0x68 (pointer) with count at this+0x6C.
// For each component, checks if flags (offset +0x4) have bit 0x2 and 0x200 set.
// If both flags are set, calls the virtual method at vtable index 7 (offset 0x1C) which returns a byte (bool).
// ORs all results together and returns non‑zero if any returned true.

bool __thiscall ComponentManager::hasActiveAwakeComponents()
{
    int count = *(int *)((char *)this + 0x6C);
    if (count == 0)
        return false;

    byte result = 0;
    // Array of Component objects, each 0x10 bytes
    char *base = *(char **)((char *)this + 0x68);
    for (int i = 0; i < count; ++i) {
        char *entry = base + i * 0x10;
        unsigned short flags = *(unsigned short *)(entry + 4);
        if ((flags & 0x2) && (flags & 0x200)) {
            // vtable is at entry+0, first field is pointer to vtbl
            void **vtbl = *(void ***)entry;
            // Virtual function at vtable offset 0x1C (index 7)
            typedef byte (__thiscall *VFunc)(void *);
            VFunc func = reinterpret_cast<VFunc>(vtbl[0x1C / 4]);
            result |= func(entry);
        }
    }
    return result != 0;
}