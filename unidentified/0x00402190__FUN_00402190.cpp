std::uint32_t* __fastcall FUN_00402190(int param_1)
{
    std::uint32_t* puVar1;
    std::uint32_t uVar2;

    if ((*reinterpret_cast<int*>(param_1 + 0x34) == 0) &&
        ((*reinterpret_cast<int*>(param_1 + 0x30) == 0) ||
         ((*reinterpret_cast<std::uint8_t*>(param_1 + 0x24) & 1) == 0))) {
        FUN_004de190();
    }

    puVar1 = reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uint32_t*>(param_1 + 0x34));
    if (puVar1 != nullptr) {
        uVar2 = *puVar1;
        *reinterpret_cast<int*>(param_1 + 0x10) = *reinterpret_cast<int*>(param_1 + 0x10) + 1;
        *reinterpret_cast<int*>(param_1 + 0x0c) = *reinterpret_cast<int*>(param_1 + 0x0c) + -1;
        *reinterpret_cast<std::uint32_t*>(param_1 + 0x34) = uVar2;
        return puVar1;
    }

    return nullptr;
}