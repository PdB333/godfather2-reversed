// FUNC_NAME: GlobalData::resetFlightCombatSettings
void __cdecl GlobalData::resetFlightCombatSettings(void)
{
    // These are global data structures at 0x011f69f0 and 0x011f6b30 (likely two arrays of 6 entries each: 6 blocks of 24 bytes)
    // Each block: +0x00 = float _DAT_ (some value, initialized to DAT_00e2b1a4), +0x04 = int zero, +0x08 = int zero, +0x0c = int zero, +0x10 = int zero, +0x14 = int zero
    // Actually the pattern repeats at offsets 0x00, 0x18 (24 bytes), 0x30 (48 bytes), 0x48 (72 bytes), 0x60 (96 bytes) and the second array at 0x011f6b30 (same pattern)
    // Looks like two arrays of 5 or 6 flight combat settings (maybe aircraft types or weapon slots)
    // First array at 0x011f69f0 (6 blocks of 24 bytes = 144 bytes, ending at 0x011f6a80)
    // Second array at 0x011f6b30 (6 blocks of 24 bytes = 144 bytes, ending at 0x011f6bc0)

    // +0x00: float unknown1 (init to DAT_00e2b1a4)
    // +0x04: int unknown2 (set to 0)
    // +0x08: int unknown3 (set to 0)
    // +0x0c: int unknown4 (set to 0)
    // +0x10: int unknown5 (set to 0)
    // +0x14: int unknown6 (set to 0)

    // Block 0 (offset 0x00)
    *(float*)0x011f69f0 = *(float*)0x00e2b1a4; // +0x00 = DAT (probably some float constant like 1.0f)
    *(int*)0x011f69f4 = 0;                    // +0x04
    *(int*)0x011f69f8 = 0;                    // +0x08
    *(int*)0x011f69fc = 0;                    // +0x0c
    *(int*)0x011f6a00 = 0;                    // +0x10
    *(int*)0x011f6a04 = *(int*)0x00e2b1a4;    // +0x14 (first field of next block? Actually offset 0x14 is part of block 0, but the next float is at +0x18)
    // It seems the pattern is: at offset 0x00: float, 0x04-0x14: 5 ints zero, then repeat at offset 0x18. So 24 bytes per entry.
    // But the assignment at +0x14 looks like it's writing a float to the last field of the first block? That would be at offset 0x14 which is only 4 bytes before the next block.
    // Actually the code assigns:
    // 0x011f69f0 = DAT (float)
    // 0x011f69f4 = 0 (int)
    // 0x011f69f8 = 0 (int)
    // 0x011f69fc = 0 (int)
    // 0x011f6a00 = 0 (int)
    // 0x011f6a04 = DAT (float) -> this is +0x14 from base, which overlaps with the first 4 bytes of the next block? Actually 0x011f69f0 + 0x14 = 0x011f6a04, which is 20 bytes into the first block. That seems odd.
    // Re-evaluating: The pattern is: at base +0x00: float, base+0x04..base+0x14: five ints? But that's 5 ints = 20 bytes, plus float = 24 bytes total. So block size is 24 bytes.
    // The code writes: float at +0x00, ints at +0x04, +0x08, +0x0c, +0x10, then float at +0x14. So it seems like the last field is also a float (at +0x14). So structure is: float, int[4], float? That would be 4+16+4 = 24 bytes.
    // Let's assume each entry is 24 bytes: { float f1; int i1; int i2; int i3; int i4; float f2; } or similar.

    // Actually let's just follow the decompiled code exactly:

    // First array start at 0x011f69f0 (size 0x140? but only 6 entries visible)
    // Entry 0 (0x011f69f0):
    *(float*)0x011f69f0 = *(float*)0x00e2b1a4; // f1
    *(int*)0x011f69f4 = 0;                    // i1
    *(int*)0x011f69f8 = 0;                    // i2
    *(int*)0x011f69fc = 0;                    // i3
    *(int*)0x011f6a00 = 0;                    // i4? (Actually offset 0x10 from base)
    *(float*)0x011f6a04 = *(float*)0x00e2b1a4; // f2 at offset 0x14

    // Entry 1 (0x011f6a08 = 0x011f69f0 + 0x18):
    *(int*)