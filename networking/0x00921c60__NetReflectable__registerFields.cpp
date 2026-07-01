// FUNC_NAME: NetReflectable::registerFields
void __fastcall NetReflectable::registerFields(int thisPtr)
{
    // Call base class constructor/init
    thunk_FUN_005c1740();

    // Register fields with global names
    registerField(&DAT_00d86488, (void*)(thisPtr + 0x78), 0, nullptr, 0, 1);
    registerField(&DAT_00d86480, (void*)(thisPtr + 0x7c), 0, nullptr, 0, 1);
    registerField(&DAT_00d86478, (void*)(thisPtr + 0x80), 0, nullptr, 0, 1);
    registerField(&DAT_00e3d6f8, (void*)(thisPtr + 0x58), 0, nullptr, 0, 1);
    registerField(&DAT_00d85730, (void*)(thisPtr + 0x74), 0, &LAB_00921c50, 0, 0);
    registerField(&DAT_00d86470, (void*)(thisPtr + 0x84), 6, nullptr, 0, 1);   // float
    registerField(&DAT_00d86468, (void*)(thisPtr + 0x88), 1, nullptr, 0, 1);   // int
    registerField(&DAT_00d86460, (void*)(thisPtr + 0x8c), 1, nullptr, 0, 1);
    registerField(&DAT_00d86458, (void*)(thisPtr + 0x90), 1, nullptr, 0, 1);
    registerField(&DAT_00d86450, (void*)(thisPtr + 0x94), 1, nullptr, 0, 1);
    registerField(&DAT_00d86448, (void*)(thisPtr + 0x98), 6, nullptr, 0, 1);   // float
    registerField(&DAT_00d86440, (void*)(thisPtr + 0x9c), 1, nullptr, 0, 1);
    registerField(&DAT_00d86438, (void*)(thisPtr + 0xa0), 2, nullptr, 0, 1);   // byte
    registerField(&DAT_00d86430, (void*)(thisPtr + 0xa1), 2, nullptr, 0, 1);   // byte
}