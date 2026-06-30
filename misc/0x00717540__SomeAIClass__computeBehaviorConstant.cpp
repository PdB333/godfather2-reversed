// FUNC_NAME: SomeAIClass::computeBehaviorConstant
int __fastcall SomeAIClass::computeBehaviorConstant(int thisObj)
{
    int resultCode; // eax
    byte flag; // bl

    resultCode = globalGetDifficultyOrState(); // FUN_00800b60
    flag = *(byte*)(*(int*)(thisObj + 0x48) + 0x88) & 1; // Check bit 0 of a flag at offset +0x88 from sub-object at +0x48

    if (resultCode == 1)
    {
        // Difficulty/state 1: return a value modified by flag
        return (flag != 0 ? 0xFC485B9A : 0) + 0x900029F;
    }
    if ((resultCode != 2) && (resultCode != 3) && (resultCode != 4))
    {
        // Unknown/unhandled state: return another modified constant
        return (flag != 0 ? 0xE41BDC1A : 0) + 0x212C821F;
    }
    // States 2,3,4: return this modified constant
    return (flag != 0 ? 0x38AEA6F1 : 0) + 0x58377EA0;
}