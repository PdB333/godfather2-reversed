std::uint32_t __thiscall FUN_009b3f60(int thisObj, int param_2, int* outValue)
{
    char cVar1;
    int iVar2;
    long double fVar3;
    int objPtr;
    int vtblPtr;
    auto fp = static_cast<long double(__thiscall*)(int)>(nullptr);

    cVar1 = FUN_007f47a0();
    if (cVar1 != '\0') {
        return 0;
    }

    objPtr = *reinterpret_cast<int*>(thisObj + 0x1C);
    iVar2 = FUN_00801760(objPtr);
    *outValue = iVar2;

    if ((iVar2 == 0) &&
        (vtblPtr = *reinterpret_cast<int*>(objPtr),
         fp = *reinterpret_cast<long double(__thiscall**)(int)>(vtblPtr + 0xBC),
         fVar3 = fp(param_2),
         fVar3 == static_cast<long double>(0.0)) &&
        (*reinterpret_cast<int*>(objPtr + 0x2138) == *reinterpret_cast<int*>(param_2 + 0x1ED4))) {
        return 0;
    }

    return 1;
}