// FUNC_NAME: setPrimaryControllerOnce
void setPrimaryControllerOnce(uint32_t controllerId)
{
    // 0x01205650: g_bPrimaryControllerSet (bool)
    // 0x0119cc58: g_dwPrimaryController (uint32_t)
    if (g_bPrimaryControllerSet == 0) {
        g_dwPrimaryController = controllerId;
        g_bPrimaryControllerSet = 1;
    }
}