// FUNC_NAME: ResourceKey::areNotEqual
bool __thiscall ResourceKey::areNotEqual(int* pLeft, int* pRight)
{
    // Compare two resource keys (3 ints each: type, ???, id)
    // Returns true if keys are considered not equal
    // Equality condition: types match AND (type is zero OR ids match)
    // Offsets: +0x00 type, +0x04 ???, +0x08 id
    bool bEqual = false;
    if ((*pLeft == *pRight) && ((*pLeft == 0) || (pLeft[2] == pRight[2])))
    {
        bEqual = true;
    }
    return !bEqual;
}