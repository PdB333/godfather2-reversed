// FUNC_NAME: SomeClass::EnsureInitializedAndExecute
// Lazy initialization wrapper: checks if a flag at offset +0x04 is zero,
// if so, calls init function FUN_00535450 with the stored value at +0x00,
// then sets the flag to 1.
// Then delegates to FUN_0060cd00 with caller's parameters and flags (0,1,0).
// Struct layout:
//   +0x00: uint32_t resourceIdOrPtr
//   +0x04: uint8_t  initializedFlag
void __thiscall SomeClass::EnsureInitializedAndExecute(SomeClass *this, uint32_t param1, uint32_t param2)
{
    if (this->initializedFlag == 0) {
        FUN_00535450(0, this->resourceIdOrPtr);
        this->initializedFlag = 1;
    }
    FUN_0060cd00(param1, param2, 0, 1, 0);
}