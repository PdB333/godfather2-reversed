// FUNC_NAME: NPC::handleManagerCall
void __thiscall NPC::handleManagerCall(void *this, undefined4 param_2, undefined4 param_3, uint param_4)
{
    int *pManager;
    
    pManager = getManager();
    if (pManager != NULL) {
        pManager = getManager();
        if (pManager != NULL) {
            // Subtract 0x58 to get the base object hosting the manager's result
            callManagerMethod((char *)pManager - 0x58, this, param_4);
            return;
        }
        callManagerMethod(NULL, this, param_4);
    }
    return;
}