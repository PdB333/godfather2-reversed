// FUNC_NAME: PluginManager::setActivePlugin
// Address: 0x0056ffa0
// Role: Replaces the global active plugin instance. Calls the Deactivate (vtable+0xC) on the old plugin,
//       then stores the new pointer, and calls Activate (vtable+0x8) on the new plugin if non-null.

static void* s_activePlugin = nullptr; // Global pointer at 0x0120556c

void PluginManager::setActivePlugin(void* newPlugin)
{
    if (s_activePlugin != nullptr)
    {
        // Call Deactivate on the old plugin (vtable offset 0xC = 3rd function)
        void (**vtable)(void) = *static_cast<void (***)(void)>(s_activePlugin);
        vtable[3]();
    }

    s_activePlugin = newPlugin;

    if (newPlugin != nullptr)
    {
        // Call Activate on the new plugin (vtable offset 0x8 = 2nd function)
        void (**vtable)(void) = *static_cast<void (***)(void)>(newPlugin);
        vtable[2]();
    }
}