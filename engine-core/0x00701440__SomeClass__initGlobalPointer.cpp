// FUNC_NAME: SomeClass::initGlobalPointer
void __fastcall SomeClass::initGlobalPointer(void* obj) {
    // +0x528: some pointer field initialized from global DAT_00d60d00
    *(int*)((char*)obj + 0x528) = DAT_00d60d00;
}