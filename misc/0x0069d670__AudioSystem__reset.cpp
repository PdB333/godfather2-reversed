// FUNC_NAME: AudioSystem::reset
void AudioSystem::reset(void)
{
    g_audioInitialized = 1;  // DAT_0112a02a, global flag indicating audio subsystem state
    FUN_0069d240(0);          // internal helper function, called with argument 0 (likely reset type or component index)
}