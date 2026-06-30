// FUNC_NAME: ObjectList::printAllNames
void __fastcall ObjectList::printAllNames(ObjectList *this)
{
    uint uVar2;
    int *piVar3;
    uint count;
    char *namePtr;

    count = *(uint *)((int)this + 0x124); // number of elements in list
    if (count != 0) {
        piVar3 = (int *)((int)this + 0x24); // pointer to array of element pointers
        uVar2 = 0;
        do {
            // Each element pointer points to an object, at offset 0x24 is a name string pointer
            namePtr = *(char **)(*piVar3 + 0x24);
            if (namePtr == (char *)0x0) {
                namePtr = (char *)&DAT_0120546e; // default string (e.g., "null")
            }
            FUN_00565870(namePtr); // output the name (likely debug print)
            uVar2 = uVar2 + 1;
            piVar3 = piVar3 + 1;
        } while (uVar2 < count);
    }
    return;
}