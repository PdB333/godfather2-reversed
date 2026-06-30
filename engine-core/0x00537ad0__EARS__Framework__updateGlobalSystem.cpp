// FUNC_NAME: EARS::Framework::updateGlobalSystem
void EARS::Framework::updateGlobalSystem(void)
{
    // DAT_0121a390 is a global system instance (likely a singleton handle)
    // DAT_0121b638 is a pointer to a configuration block; dereference to pass the actual config
    EARS::Framework::processSystem(DAT_0121a390, *DAT_0121b638);
}