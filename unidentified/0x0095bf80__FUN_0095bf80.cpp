// FUNC_NAME: SomeClass::cloneFields
void __fastcall SomeClass::cloneFields(void *thisPtr)
{
    // FUN_0095bd70 is likely base class initialization or copy-constructor
    baseInitialize();
    // Copy field from offset +0x68 to +0x90 (e.g., network ID or handle)
    *(int *)((char *)thisPtr + 0x90) = *(int *)((char *)thisPtr + 0x68);
}