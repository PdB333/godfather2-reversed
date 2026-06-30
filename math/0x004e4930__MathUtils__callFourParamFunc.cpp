// FUNC_NAME: MathUtils::callFourParamFunc
void __fastcall MathUtils::callFourParamFunc(MathUtils* thisPtr)
{
    // Calls an external function with the four uint32 values stored at offsets 0x0, 0x4, 0x8, 0xC
    FUN_005277b0(thisPtr->value0, thisPtr->value1, thisPtr->value2, thisPtr->value3);
}