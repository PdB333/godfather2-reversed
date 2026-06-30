// FUNC_NAME: SomeClass::initStaticData
// Address: 0x00537640
// Role: Wrapper to bind a 4-byte global data block (at 0x01198e20) to an instance, likely initializing a pointer or handle.
// Calls internal utility FUN_0060c8d0 with hardcoded flags (0x40000000) and a null offset, passing `this` as the last argument.

void __fastcall SomeClass::initStaticData(void)
{
    // FUN_0060c8d0 parameters:
    //   arg0 = 0 (possibly source offset or null)
    //   arg1 = &DAT_01198e20 (global static buffer)
    //   arg2 = 4 (size in bytes)
    //   arg3 = 0 (flags variant?)
    //   arg4 = 0x40000000 (allocation or copy flags)
    //   arg5 = this (pointer to current object)
    FUN_0060c8d0(0, &DAT_01198e20, 4, 0, 0x40000000, this);
    return;
}