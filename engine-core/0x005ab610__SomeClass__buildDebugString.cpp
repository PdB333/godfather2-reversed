// FUNC_NAME: SomeClass::buildDebugString
void FUN_005ab610(int this)
{
    undefined4 uVar1;
    int iVar2;
    char *unaff_EDI;
    undefined1 local_100 [256];
    
    iVar2 = 0;
    if (0 < *(int *)(this + 0x54)) { // +0x54: count of items
        do {
            if (*(int *)(*(int *)(this + 0x4c) + iVar2 * 4) != 0) { // +0x4c: pointer to array of items
                uVar1 = FUN_005a90a0(local_100,0x100); // likely a string conversion function
                _sprintf(unaff_EDI,"%s",uVar1);
            }
            _sprintf(unaff_EDI,"%s",&DAT_00e3c9fc); // append separator (likely comma or space)
            iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(this + 0x54));
    }
    *unaff_EDI = '\0'; // null-terminate the output string
    return;
}