// FUNC_NAME: shutdownGlobalResources
void shutdownGlobalResources(void)
{
    // Release first global resource if valid
    if (DAT_012055e0 != (uint *)0x0) {
        // Call destructor/dispose function from dispatch table (indexed by low 15 bits of first DWORD)
        (**(code **)(&DAT_0103aee0 + (*DAT_012055e0 & 0x7fff) * 4))(DAT_012055e0);
        DAT_012055e0 = (uint *)0x0; // Mark as null
    }
    // Release second global resource
    if (DAT_012055e8 != (uint *)0x0) {
        (**(code **)(&DAT_0103aee0 + (*DAT_012055e8 & 0x7fff) * 4))(DAT_012055e8);
        DAT_012055e8 = (uint *)0x0;
    }
    // Release third global resource
    if (DAT_012055e4 != (uint *)0x0) {
        (**(code **)(&DAT_0103aee0 + (*DAT_012055e4 & 0x7fff) * 4))(DAT_012055e4);
        DAT_012055e4 = (uint *)0x0;
    }
    // Additional cleanup
    FUN_005ba710();
    return;
}