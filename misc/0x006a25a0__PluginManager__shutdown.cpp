// FUNC_NAME: PluginManager::shutdown
void __fastcall PluginManager::shutdown()
{
    // Release the loaded library module handle stored at +0x90
    FreeLibrary(reinterpret_cast<HMODULE>(this->libraryModule));
    // Zero out the library handle and related data (offsets 0x90..0xA4)
    this->libraryModule = nullptr; // +0x90
    this->field_0x94 = 0;           // +0x94
    this->field_0x98 = 0;           // +0x98
    this->field_0x9c = 0;           // +0x9c
    this->field_0xa0 = 0;           // +0xa0
    this->field_0xa4 = 0;           // +0xa4
}