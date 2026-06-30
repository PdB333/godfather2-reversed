// FUNC_NAME: CApplicationManager::setActiveInstance
void __thiscall CApplicationManager::setActiveInstance(CApplicationManager *this) {
    // Global singleton pointer (0x012058e8) - set to this instance
    g_pActiveAppManager = this;

    // Release sub-manager pointers at +0x10 and +0x14
    ReleaseSubManager(*(void **)((char *)this + 0x10)); // +0x10: e.g., m_pAudioManager
    ReleaseSubManager(*(void **)((char *)this + 0x14)); // +0x14: e.g., m_pVideoManager
}