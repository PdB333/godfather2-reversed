// FUNC_NAME: SomeClass::setSomeProperty
void SomeClass::setSomeProperty(int param1, char param2, int param3)
{
    struct SomeStruct {
        int field0;      // +0x00
        int field4;      // +0x04
        char field8;     // +0x08
        int fieldC;      // +0x0C
    } localStruct;

    localStruct.field8 = param2;  // +0x08
    localStruct.fieldC = param1;  // +0x0C
    localStruct.field0 = 2;      // +0x00
    localStruct.field4 = param3; // +0x04

    FUN_00834800(&localStruct);
    return;
}