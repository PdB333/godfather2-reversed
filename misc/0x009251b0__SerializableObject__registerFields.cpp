// FUNC_NAME: SerializableObject::registerFields
void __fastcall SerializableObject::registerFields(int this)
{
    // Call base class field registration (base constructor)
    FUN_005c1740();

    // Register field: unknown name (DAT_00e3d6f8) at offset 0x64 (100), size 1 (byte?), flags: 0,0,1 (network?).
    FUN_005c01d0(&DAT_00e3d6f8, this + 0x64, 1, 0, 0, 1);

    // Register field: DAT_00d8771c at offset 0x7c, size 4 (int), flags: 0,0,1
    FUN_005c01d0(&DAT_00d8771c, this + 0x7c, 4, 0, 0, 1);

    // Similar fields at various offsets, size 4 (int32) or 2 (int16)
    FUN_005c01d0(&DAT_00d87714, this + 0x80, 4, 0, 0, 1);
    FUN_005c01d0(&DAT_00d8770c, this + 0x74, 4, 0, 0, 1);
    FUN_005c01d0(&DAT_00d87704, this + 0x78, 4, 0, 0, 1);
    FUN_005c01d0(&DAT_00d876fc, this + 0x6c, 4, 0, 0, 1);
    FUN_005c01d0(&DAT_00d876f4, this + 0x70, 4, 0, 0, 1);

    // Explicit string "index" at offset 0x68, size 1 (byte?)
    FUN_005c01d0("index", this + 0x68, 1, 0, 0, 1);

    FUN_005c01d0(&DAT_00d876ec, this + 0x5c, 4, 0, 0, 1);
    FUN_005c01d0(&DAT_00d876e4, this + 0x60, 4, 0, 0, 1);

    // Fields likely related to screen/script timing: "scrinc", "scrmin", "scrmax", "sctime"
    FUN_005c01d0("scrinc", this + 0xac, 4, 0, 0, 1);
    FUN_005c01d0("scrmin", this + 0xa8, 4, 0, 0, 1);
    FUN_005c01d0("scrmax", this + 0xa4, 4, 0, 0, 1);
    FUN_005c01d0("sctime", this + 0x84, 4, 0, 0, 1);

    // Timer fields: "lTime" (int32 at +0x13ac) and "lDone" (int16 at +0x13b2)
    FUN_005c01d0("lTime", this + 0x13ac, 4, 0, 0, 1);
    FUN_005c01d0("lDone", this + 0x13b2, 2, 0, 0, 1);
}
```