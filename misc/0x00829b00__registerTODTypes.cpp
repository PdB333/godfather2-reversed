// FUNC_NAME: registerTODTypes
void registerTODTypes(void)
{
    // Register the TODSequencer class with its hash, name, vtable placeholder, and size
    // Hash: 0x83bef348 (likely CRC32 of "TODSequencer")
    FUN_004833a0(0x83bef348, "TODSequencer", &LAB_008294d0, 0x54);

    // Register the TODSequencerAction class
    // Hash: 0xf7a92bbe (likely CRC32 of "TODSequencerAction")
    FUN_004833a0(0xf7a92bbe, "TODSequencerAction", &LAB_00829500, 0xe4);

    // Register the CurrentCityTODAction class
    // Hash: 0xb5c5b5bb (likely CRC32 of "CurrentCityTODAction")
    FUN_004833a0(0xb5c5b5bb, "CurrentCityTODAction", &LAB_00829a60, 0xf8);

    return;
}