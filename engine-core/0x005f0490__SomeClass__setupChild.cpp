// FUNC_NAME: SomeClass::setupChild
int SomeClass::setupChild(void* param) // param passed in EDI; this in EAX
{
    int* childObj = *(int**)(this + 0x0C); // child object pointer (offset +0x0C)
    if (childObj == 0)
        return 0;

    initialize(); // FUN_005dbc10

    if (*(int*)(param + 4) != 0) { // transfer a pointer from param+0x04 to childObj+0x44
        *(int*)(childObj + 0x44) = *(int*)(param + 4);
        *(int*)(param + 4) = 0; // clear source
    }

    if (!validateStep1()) return 0; // FUN_005f0990
    if (!validateStep2()) return 0; // FUN_005f09e0
    if (!validateStep3(childObj)) return 0; // FUN_005f0a30

    return 1;
}