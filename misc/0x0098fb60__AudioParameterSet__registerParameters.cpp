// FUNC_NAME: AudioParameterSet::registerParameters
void __fastcall AudioParameterSet::registerParameters(int thisPtr)
{
    // Base initializer
    FUN_005c1740();

    // Register parameter at offset 0x5c (likely a float: duration or start time)
    FUN_005c01d0(&DAT_00d91b54, thisPtr + 0x5c, 0, 0, 0, 1);
    // Register parameter at offset 0x60 (likely a float: end time or fade)
    FUN_005c01d0(&DAT_00d91b4c, thisPtr + 0x60, 0, 0, 0, 1);
    // Register parameter at offset 100 (0x64) with type 5 (float) (e.g., loop start)
    FUN_005c01d0(&DAT_00d86468, thisPtr + 100, 5, 0, 0, 1);
    // Register parameter at offset 0xE8 with type 5 (float) (e.g., volume)
    FUN_005c01d0(&DAT_00d91b44, thisPtr + 0xE8, 5, 0, 0, 1);
    // Register parameter at offset 0x185 with type 2 (int) (e.g., playback count)
    FUN_005c01d0(&DAT_00d91b3c, thisPtr + 0x185, 2, 0, 0, 1);
}