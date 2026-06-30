// FUNC_NAME: GameObject::checkAndProcessEvent
void __thiscall GameObject::checkAndProcessEvent(int this, int otherObject)
{
    char unkFlag;
    void **local_14;  // pointer to a function pointer table
    int local_10;
    int local_c;
    undefined4 local_8;
    undefined4 local_4;

    // +0x0c: m_bProcessed flag
    if (*(char *)(this + 0xc) == '\0') {
        // +0x10: some data  
        local_8 = *(undefined4 *)(this + 0x10);
        // +0x14: another data  
        local_4 = *(undefined4 *)(this + 0x14);
        // +0x18: pointer to something
        local_c = this + 0x18;
        // Global function pointer table (used for virtual dispatch?)
        local_14 = &g_pFunctionTable;
        local_10 = otherObject;

        // +0xb2 in otherObject: bit0 masked flag (e.g., m_bDestroyed)
        if (((*(byte *)(otherObject + 0xb2) & 1) != 0) ||
           (unkFlag = g_pFunctionTable(), unkFlag == '\0')) {
            // Call common handler with a label and the local function pointer address
            FUN_0049d0c0(&LAB_0049cd60, &local_14);
        }
    }
    return;
}