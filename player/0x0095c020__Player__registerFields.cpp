//FUNC_NAME: Player::registerFields
void __thiscall Player::registerFields(int thisPtr)
{
    // Call base class field registration (likely Entity or Sentient)
    thunk_FUN_005c1740();

    // Register member variables with the reflection/serialization system
    // Each call registers a field at a specific offset from thisPtr
    // Offsets: +0x74 through +0xc0 (many fields)
    registerFieldWithDefault(&DAT_00d885e0, thisPtr + 0x74, &LAB_0095be70, 0, 0);
    registerFieldWithDefault(&DAT_00d885d8, thisPtr + 0x78, 0, 0, 1);
    registerFieldWithFlags(&DAT_00d8cc50, thisPtr + 0x7c, 0, 0, 1, 1);
    registerFieldWithFlags(&DAT_00d8cc48, thisPtr + 0x80, 0, 0, 1, 1);
    registerFieldWithFlags(&DAT_00d8cc40, thisPtr + 0x84, 0, 0, 1, 1);
    registerFieldWithFlags(&DAT_00d8cc38, thisPtr + 0x88, 0, 0, 1, 1);
    registerFieldWithDefault(&DAT_00d8cc30, thisPtr + 0x8c, 0, 0, 1);
    registerFieldWithDefault(&DAT_00d8be4c, thisPtr + 0x90, 0, &LAB_0095c000, 0);
    registerFieldWithDefault(&DAT_00d8be44, thisPtr + 0x94, &LAB_0095b6d0, 0, 0);
    registerFieldWithFlags(&DAT_00d8be3c, thisPtr + 0x98, 0, 0, 1, 1);
    registerFieldWithFlags(&DAT_00d8be34, thisPtr + 0x9c, 0, 0, 1, 1);
    registerFieldWithFlags(&DAT_00d8be2c, thisPtr + 0xa0, 0, 0, 1, 1);
    registerFieldWithFlags(&DAT_00d8cc28, thisPtr + 0xa4, 0, 0, 1, 1);
    registerFieldWithFlags(&DAT_00d8be24, thisPtr + 0xa8, 0, 0, 1, 1);
    registerFieldPointer(&DAT_00d8cc20, thisPtr + 0xb0, 0, 0, 1);
    registerFieldWithDefault(&DAT_00d8be1c, thisPtr + 0xb4, 0, 0, 1);
    registerFieldWithDefault(&DAT_00d8be14, thisPtr + 0xb8, 0, 0, 1);
    registerFieldWithDefault(&DAT_00d8be0c, thisPtr + 0xc0, 0, 0, 1);
    registerFieldWithFlags(&DAT_00d8be04, thisPtr + 0xac, 0, 0, 1, 1);
}