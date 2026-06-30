// FUN_00466040: BaseObject::enable
void __fastcall BaseObject::enable(void* thisPtr)
{
    // Delegate to internal setter with value 1 (enable/true)
    setEnabledFlag(thisPtr, 1);
}