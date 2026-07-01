// FUNC_NAME: SomeClass::setStringProperty
void __fastcall SomeClass::setStringProperty(int this) {
    char *tempString; // ecx
    int unused1; // stack
    int unused2; // stack
    void (*stringDeleter)(char *); // stack

    tempString = NULL;
    unused1 = 0;
    unused2 = 0;
    stringDeleter = NULL;
    GetLocalizedString(&tempString); // FUN_00839460
    char *finalString = tempString;
    if (tempString == NULL) {
        finalString = (char *)&DAT_0120546e; // default string
    }
    SetString(*(int *)(this + 0xf8), finalString); // FUN_0090e110, likely sets a member string
    if (tempString != NULL) {
        (*stringDeleter)(tempString); // free the allocated string
    }
}