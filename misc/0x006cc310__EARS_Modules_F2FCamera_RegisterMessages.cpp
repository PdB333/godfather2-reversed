// Xbox PDB: EARS::Modules::F2FCamera::RegisterMessages
// FUNC_NAME: registerF2FCameraMessages
void registerF2FCameraMessages(void)
{
    // Register Face-to-Face camera state messages used by the F2F gameplay mode
    registerMessage(&s_iMsgF2FCameraActive, "iMsgF2FCameraActive");
    registerMessage(&s_iMsgF2FCameraInactive, "iMsgF2FCameraInactive");
    registerMessage(&s_iMsgF2FShotEnd, "iMsgF2FShotEnd");
}