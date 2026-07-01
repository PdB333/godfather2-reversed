// FUNC_NAME: CrewLeaderComponent::registerFields
void __fastcall CrewLeaderComponent::registerFields(void *this)
{
    // Base class registration
    Component::registerFields(); // FUN_005c1740

    // Register fields with offsets and types
    // +0x5c: int field
    registerIntField(&DAT_00d8f8d4, (int*)((char*)this + 0x5c), 1, 0, 0, 1);
    // +0x60: int field
    registerIntField(&DAT_00d8f8cc, (int*)((char*)this + 0x60), 1, 0, 0, 1);
    // +0x64 (100): int field with setter callback LAB_00975560
    registerIntField(&DAT_00d873bc, (int*)((char*)this + 100), 0, &LAB_00975560, 0, 0);
    // +0x68: int field (type 2, perhaps short/unsigned)
    registerIntField(&DAT_00d8f8c4, (int*)((char*)this + 0x68), 2, 0, 0, 1);
    // +0x6c: float field
    registerFloatField(&DAT_00d885e8, (float*)((char*)this + 0x6c), 0, 0, 1);
    // +0x70: float field with getter/setter callback LAB_00974d50
    registerFloatField(&DAT_00d885e0, (float*)((char*)this + 0x70), &LAB_00974d50, 0, 0);
    // +0x74: bool field
    registerBoolField(&DAT_00d8f6dc, (bool*)((char*)this + 0x74), 0, 0, 1);
    // +0x78: bool field
    registerBoolField(&DAT_00d8f6d4, (bool*)((char*)this + 0x78), 0, 0, 1);
    // +0x7c: string field (or ID) – offset less common, maybe a pointer
    registerStringField(&DAT_00d8cc30, (char*)((char*)this + 0x7c), 0, 0, 1);
    // +0x83: int field (type 2, byte? note offset 0x83 is not aligned)
    registerIntField(&DAT_00d8f8c0, (int*)((char*)this + 0x83), 2, 0, 0, 1);
}