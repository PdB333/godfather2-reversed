// FUNC_NAME: SomeClass::canShootOrSomething
bool SomeClass::canShootOrSomething(void)
{
    int iVar1;
    char cVar2;
    int unaff_EDI;  // this pointer
    
    iVar1 = *(int *)(unaff_EDI + 8); // this+8: linked list head pointer
    while ((iVar1 != 0 &&
           ((*(char *)(iVar1 + 8) == '\0' || (cVar2 = FUN_005f03c0(unaff_EDI), cVar2 == '\0'))))) {
        iVar1 = *(int *)(iVar1 + 4); // next node in linked list
    }
    return *(ushort *)(unaff_EDI + 0x12) < 0x23; // this+0x12: some 16-bit field, check if < 35
}