extern "C" void __thiscall FUN_004088c0(int* const param_1)
{
    using Method8 = void(__thiscall*)(void*);

    reinterpret_cast<Method8>(*reinterpret_cast<std::uint32_t*>(param_1) + 8)(
        param_1
    );

    if (DAT_012067c4 != 0)
    {
        if (FUN_00402080(&DAT_012067c4) == '\0')
        {
            _DAT_012067c8 = _DAT_012067c8 + 1;
            FUN_004084d0(&DAT_012067c4, 0x8000);
        }
    }
}