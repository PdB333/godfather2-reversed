// FUNC_NAME: SomeClass::resolveValue
uint __thiscall SomeClass::resolveValue(uint alternativeId) {
    int* someObject = *(int**)(this + 0x20); // +0x20: pointer to some other object
    if (someObject != nullptr) {
        uint localVar;
        uint result = computeSomething(&localVar); // FUN_0067bb50
        *(uint8*)(someObject + 0x1ec) = (uint8)(result & 0xff); // store low byte at offset 0x1ec
        return localVar & 0xffff; // return 16-bit value
    }
    int* otherObject = *(int**)(this + 0x48); // +0x48: pointer to another object
    if (otherObject != nullptr) {
        uint localVar = alternativeId;
        uint result = processAlternative(alternativeId); // FUN_00675200
        return result;
    }
    return 0;
}