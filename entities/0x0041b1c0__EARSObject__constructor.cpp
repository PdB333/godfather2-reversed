// FUNC_NAME: EARSObject::constructor
void EARSObject::constructor(uint32_t thisPtr, uint32_t initArg1, uint32_t initArg2) {
    // +0x00: vtable pointer (implicit)
    // Called to initialize base members from initArg1 and pass to initBase
    initBase(thisPtr, initArg1);   // FUN_0041ad20: likely sets up base fields
    initGlobal();                  // FUN_00491090: global/static initialization
    postInit(thisPtr, initArg1, initArg2); // FUN_00418540: finalize object setup
    return;
}