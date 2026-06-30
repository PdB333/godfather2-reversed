// FUNC_NAME: PluginModule::unload
void __thiscall PluginModule::unload(void) {
    char ready;

    ready = isModuleReady();
    if (ready != '\0') {
        // Call the shutdown function pointer at +0x98
        (*(void (__thiscall *)(PluginModule *))(this + 0x98))(this);
    }
    // Free the loaded library
    FreeLibrary(*(HMODULE *)(this + 0x90));
    // Clear all module pointers
    *(uint32_t *)(this + 0x90) = 0; // hModule
    *(uint32_t *)(this + 0x94) = 0; // unknown
    *(uint32_t *)(this + 0x98) = 0; // shutdownFunc
    *(uint32_t *)(this + 0x9c) = 0; // unknown
    *(uint32_t *)(this + 0xa0) = 0; // unknown
    *(uint32_t *)(this + 0xa4) = 0; // unknown
}