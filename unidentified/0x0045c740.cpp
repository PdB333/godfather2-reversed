// FUN_0045c740: SmallStruct::constructor(void *this, uint param2, uint param3, uint param4, uint param5, uint param6, uint param7, uint param8)
undefined4 SmallStruct::constructor(undefined4 this, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6, undefined4 param7, undefined4 param8)
{
    // local_18 is a 20-byte temporary buffer (5 uint32s or 5 floats)
    undefined1 local_18[20];

    // Initialize something using param2 (likely a source parameter)
    initSomethingWithParam2(param2);  // FUN_004eacb0

    // Core initialization: fills local_18 and copies into this? Or uses this directly
    internalInit(this, local_18, param3, param4, param5, param6, param7, param8);  // FUN_004df420

    return this;
}