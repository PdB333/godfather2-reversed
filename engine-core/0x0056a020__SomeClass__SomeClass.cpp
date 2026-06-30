// FUNC_NAME: SomeClass::SomeClass
class SomeClass {
public:
    void* m_vtable;                 // +0x00
    int field_0x04;                // +0x04 (in_EAX[1])
    int field_0x1C;                // +0x1C (in_EAX[7])
    int field_0x120;               // +0x120 (in_EAX[0x48])
    int field_0x224;               // +0x224 (in_EAX[0x89])
    int field_0x328;               // +0x328 (in_EAX[0xca])
    int field_0x32C;               // +0x32C (in_EAX[0xcb])
    char field_0x330;               // +0x330 (byte at (in_EAX + 0xcc))
    char field_0x331;               // +0x331 (byte at ((int)in_EAX + 0x331))
    int field_0x334;               // +0x334 (in_EAX[0xcd])
    int field_0x338;               // +0x338 (in_EAX[0xce])
    int field_0x33C;               // +0x33C (in_EAX[0xcf])
    char field_0x340;               // +0x340 (byte at (in_EAX + 0xd0))
    int field_0x344;               // +0x344 (in_EAX[0xd1])

    __thiscall SomeClass();
};

__thiscall SomeClass::SomeClass() {
    field_0x04 = 0;
    field_0x1C = 0;
    field_0x120 = 0;
    field_0x224 = 0;
    field_0x328 = 0;
    field_0x32C = 0;
    field_0x330 = 1;               // default to 1
    field_0x331 = 0;
    m_vtable = (void*)0x00e3ab30; // vtable pointer (PTR_FUN_00e3ab30)
    field_0x334 = 0;
    field_0x338 = 0;
    field_0x33C = 0;
    field_0x340 = 0;
    field_0x344 = 0;
}