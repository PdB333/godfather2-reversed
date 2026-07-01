// FUNC_NAME: DebugInitStruct::init
void __fastcall DebugInitStruct::init(undefined2 *thisStruct)
{
    // Write debug sentinel values to detect memory corruption
    *(undefined4 *)(thisStruct + 2) = 0xbadbadba;   // offset +4 bytes
    *(undefined4 *)(thisStruct + 4) = 0xbeefbeef;   // offset +8 bytes
    *(undefined4 *)(thisStruct + 6) = 0xeac15a55;   // offset +12 bytes
    *(undefined4 *)(thisStruct + 8) = 0x91100911;   // offset +16 bytes
    thisStruct[10] = 6;                              // offset +20 bytes (2-byte field)

    // Now clear all fields to zero (except the one at offset 20)
    *thisStruct = 0;                                 // offset 0 (2-byte field)
    *(undefined4 *)(thisStruct + 8) = 0;             // offset +16
    *(undefined4 *)(thisStruct + 6) = 0;             // offset +12
    *(undefined4 *)(thisStruct + 4) = 0;             // offset +8
    *(undefined4 *)(thisStruct + 2) = 0;             // offset +4
    return;
}