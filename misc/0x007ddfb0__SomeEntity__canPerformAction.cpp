// FUNC_NAME: SomeEntity::canPerformAction
bool __fastcall SomeEntity::canPerformAction(int this) {
    char cVar1;

    // Check flags at offsets +0x75 and +0x74
    if (*(char *)(this + 0x75) == '\0') {
        // If flag at +0x75 is false, check flag at +0x74
        if (*(char *)(this + 0x74) != '\0') {
            return true;
        }
    } else {
        // If flag at +0x75 is true, check global conditions
        cVar1 = FUN_004ac870(0); // Some global check
        if (cVar1 == '\0') {
            return true;
        }
        cVar1 = FUN_004ac2c0(0); // Another global check
        if (cVar1 != '\0') {
            return true;
        }
    }
    return false;
}