// FUNC_NAME: EARSObject::release
void EARSObject::release() {
    // Offset +0x20: pointer to an owned resource (e.g., memory allocation)
    if (this->m_pOwnedResource != 0) {
        extern void* g_resourceManager;  // DAT_012233a4 – global manager handle
        extern void releaseResource(void* manager);  // FUN_0044fbd0 – releases resource from manager
        releaseResource(g_resourceManager);
    }
}