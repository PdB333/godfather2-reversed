// FUNC_NAME: AudioVoice::stopVoice
void __thiscall AudioVoice::stop() {
    // +0x0C: active flag (set to 0 when stopping)
    *(int32_t*)(this + 0x0C) = 0;

    // +0x36C: pointer to a linked sub-object (e.g., a stream handle)
    if (*(int32_t*)(this + 0x36C) != 0) {
        int32_t subObj = *(int32_t*)(this + 0x36C);
        // +0x14 in sub-object: pointer to an inner resource (e.g., a voice or buffer)
        int32_t inner = *(int32_t*)(subObj + 0x14);
        if (inner != 0) {
            // Release/stop the inner resource
            FUN_004cb8a0(inner);
        }

        // Global sound manager singleton (0x0122344c)
        if (g_pSoundManagerGlobal != nullptr) {
            // Call first virtual method on the manager with argument 1 (e.g., NotifyVoiceStopped)
            (*(void(__thiscall*)(int32_t))*g_pSoundManagerGlobal)(1);
        }
    }
    // Clear the linked sub-object pointer
    *(int32_t*)(this + 0x36C) = 0;
}