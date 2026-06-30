// FUNC_NAME: ComponentSystem::updateActiveComponents
// Function at 0x004a5690: Iterates over component entries flagged with bit 0x800 and calls their virtual update method.
// Class fields at offsets: +0x68 (array of entries), +0x6c (count of entries).
// Each entry is 0x10 bytes: +0x0 pointer to component object, +0x4 flags (uint16), rest unused.

class ComponentSystem {
    // Unknown base class data...
public:
    // Offset +0x68: pointer to array of ComponentEntry structures
    // Offset +0x6c: number of entries in the array
    void updateActiveComponents(uint32_t deltaTime, uint32_t arg3, uint32_t arg4)
    {
        ComponentEntry* entries = reinterpret_cast<ComponentEntry*>(*(int*)((uint8_t*)this + 0x68));
        uint32_t count = *(uint32_t*)((uint8_t*)this + 0x6c);

        for (uint32_t i = 0; i < count; i++)
        {
            ComponentEntry& entry = entries[i];

            // Check if the 'active' flag (0x800) is set in the entry's flags (at offset +0x4)
            if ((entry.flags & 0x800) != 0)
            {
                // The first 4 bytes of the entry point to a component object with a vtable.
                // Call the virtual function at vtable offset +0x58 (method index 22).
                // This is likely a per-frame update method, taking three parameters passed through.
                void* component = entry.component;
                auto vtable = *(uint32_t**)component;
                auto updateFunc = (void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))vtable[0x58 / 4];
                updateFunc(component, deltaTime, arg3, arg4);
            }
        }
    }

private:
    struct ComponentEntry
    {
        void* component; // +0x0: pointer to the component object
        uint16_t flags;  // +0x4: bitmask flags (0x800 = active/update-enabled)
        // Remaining bytes (up to 0x10 total) are unused or hold other data not accessed here.
    };
    static_assert(sizeof(ComponentEntry) == 0x10, "ComponentEntry size mismatch");
};