// FUNC_NAME: GameReplicatedObject::registerNetworkVars
void __fastcall GameReplicatedObject::registerNetworkVars(void* thisPtr)
{
    // Base class registration (likely initializes the replication system)
    FUN_005c1740();

    // Register replicated fields with global descriptors (DAT_* are static field definitions)
    // Each call: FUN_005c01d0(&descriptor, this + offset, size, unknown1, unknown2, replicateFlag)
    // replicateFlag = 1 indicates this field is replicated over network

    FUN_005c01d0(&DAT_00d87b18, (char*)thisPtr + 0x60, 4, 0, 0, 1);  // int field at +0x60
    FUN_005c01d0(&DAT_00d87b10, (char*)thisPtr + 0x64, 4, 0, 0, 1); // int field at +0x64 (100 decimal)
    FUN_005c01d0(&DAT_00d87b08, (char*)thisPtr + 0x5c, 0, 0, 0, 1); // size 0? Possibly a pointer or special
    FUN_005c01d0(&DAT_00d87b00, (char*)thisPtr + 0x68, 6, 0, 0, 1); // 6-byte field at +0x68 (e.g., GUID or MAC)
    FUN_005c01d0(&DAT_00d87af8, (char*)thisPtr + 0x6c, 6, 0, 0, 1); // 6-byte field at +0x6c
    FUN_005c01d0(&DAT_00e40ec8, (char*)thisPtr + 0x78, 1, 0, 0, 1); // byte field at +0x78
    FUN_005c01d0(&DAT_00d87af0, (char*)thisPtr + 0x7c, 2, 0, 0, 1); // short field at +0x7c
}