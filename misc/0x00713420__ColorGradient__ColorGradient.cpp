// FUNC_NAME: ColorGradient::ColorGradient
void __fastcall ColorGradient::ColorGradient(ColorGradient* this)
{
    // Initialize vtable pointer at offset 0x00
    this->vtable = &ColorGradient_VTable;

    // Call base class constructor (likely VFXBase or similar)
    // FUN_0084b910 is the base constructor; we assume it sets up vtable and other base members
    FUN_0084b910();

    // Initialize fields: first set a flag to 1, then zeros
    this->field_04 = 1;       // +0x04
    this->field_08 = 0;       // +0x08
    this->field_0C = 0;       // +0x0C
    this->field_10 = 0;       // +0x10

    // +0xAC (offset 0x2b*4)
    this->field_AC = 0;

    // +0xC8 (offset 0x32*4) is set to -1 (0xFFFFFFFF)
    this->field_C8 = 0xFFFFFFFF;

    // +0x38 (offset 0x0e*4) is set to a default float (likely 1.0f)
    this->someDefaultFloat1 = DAT_00d5ccf8;        // +0x38

    // +0xCC (offset 0x33*4) also gets same default
    this->someDefaultFloat2 = DAT_00d5ccf8;        // +0xCC

    // Repeated pattern: blocks of 3 zeros followed by default float
    // These likely represent RGBA color stops (RGB=0, Alpha=1.0)
    // Block 1: offsets 0x34-0x37
    this->colorStop1[0] = 0;   // +0xD0
    this->colorStop1[1] = 0;   // +0xD4
    this->colorStop1[2] = 0;   // +0xD8
    this->colorStop1[3] = DAT_00d5ccf8;  // +0xDC (Alpha)

    // Block 2: offsets 0x38-0x3B
    this->colorStop2[0] = 0;   // +0xE0
    this->colorStop2[1] = 0;   // +0xE4
    this->colorStop2[2] = 0;   // +0xE8
    this->colorStop2[3] = DAT_00d5ccf8;  // +0xEC

    // Block 3: offsets 0x3C-0x3F
    this->colorStop3[0] = 0;   // +0xF0
    this->colorStop3[1] = 0;   // +0xF4
    this->colorStop3[2] = 0;   // +0xF8
    this->colorStop3[3] = DAT_00d5ccf8;  // +0xFC

    // Block 4: offsets 0x40-0x43
    this->colorStop4[0] = 0;   // +0x100
    this->colorStop4[1] = 0;   // +0x104
    this->colorStop4[2] = 0;   // +0x108
    this->colorStop4[3] = DAT_00d5ccf8;  // +0x10C

    // Block 5: offsets 0x44-0x47
    this->colorStop5[0] = 0;   // +0x110
    this->colorStop5[1] = 0;   // +0x114
    this->colorStop5[2] = 0;   // +0x118
    this->colorStop5[3] = DAT_00d5ccf8;  // +0x11C

    // Block 6: offsets 0x48-0x4B
    this->colorStop6[0] = 0;   // +0x120
    this->colorStop6[1] = 0;   // +0x124
    this->colorStop6[2] = 0;   // +0x128
    this->colorStop6[3] = DAT_00d5ccf8;  // +0x12C

    // Additional blocks: offsets 0x4C-0x4F
    this->colorStop7[0] = 0;   // +0x130
    this->colorStop7[1] = 0;   // +0x134
    this->colorStop7[2] = 0;   // +0x138
    this->colorStop7[3] = DAT_00d5ccf8;  // +0x13C

    // Clear some more fields: +0xB8 (0x2e*4), +0xB4 (0x2d*4), +0xB0 (0x2c*4),
    // +0xC4 (0x31*4), +0xC0 (0x30*4), +0xBC (0x2f*4)
    this->field_B8 = 0;
    this->field_B4 = 0;
    this->field_B0 = 0;
    this->field_C4 = 0;
    this->field_C0 = 0;
    this->field_BC = 0;

    // Now initialize a set of what look like curve control points (7 fields each)
    // The pattern repeats for 4 "keys", but note the offsets are not contiguous; they seem to interleave.
    // Global constants are loaded into registers: uVar1 = DAT_00d5ccf8 (float 1.0f maybe)
    // uVar2 = DAT_00e445ac, uVar3 = DAT_00e445f8, uVar4 = DAT_00e44634,
    // uVar5 = DAT_00e44718, uVar6 = DAT_00e44948
    // We treat these as unknown default float values for different channels.

    // Key 1 (starts at offset 0x4C, 7 fields: indices 0x13,0x17,0x1b,0x1f,0x23,0x27, then 0xf? Actually the code sets:
    // param_1[0x13] = uVar3; [0x17]=uVar5; [0x1b]=uVar1; [0x1f]=uVar2; [0x23]=uVar6; [0x27]=uVar4;
    // This looks like 6 fields, but then next group uses 7 fields. Possibly it's a 4x7 matrix.
    // Given the complexity, we just replicate the assignments as seen.

    // Offset 0x4C (0x13*4) set to DAT_00e445f8
    this->curveKey1[0] = DAT_00e445f8;   // +0x4C
    // Offset 0x5C (0x17*4)
    this->curveKey1[1] = DAT_00e44718;   // +0x5C
    // Offset 0x6C (0x1b*4)
    this->curveKey1[2] = DAT_00d5ccf8;   // +0x6C
    // Offset 0x7C (0x1f*4)
    this->curveKey1[3] = DAT_00e445ac;   // +0x7C
    // Offset 0x8C (0x23*4)
    this->curveKey1[4] = DAT_00e44948;   // +0x8C
    // Offset 0x9C (0x27*4)
    this->curveKey1[5] = DAT_00e44634;   // +0x9C

    // Next set: offsets 0x3C (0xf*4), 0x50 (0x14), 0x60 (0x18), 0x70 (0x1c), 0x80 (0x20), 0x90 (0x24), 0xA0 (0x28)
    // This is 7 fields.
    this->curveKey2[0] = DAT_00e44634;   // +0x3C
    this->curveKey2[1] = DAT_00e445f8;   // +0x50
    this->curveKey2[2] = DAT_00e44718;   // +0x60
    this->curveKey2[3] = DAT_00d5ccf8;   // +0x70
    this->curveKey2[4] = DAT_00e445ac;   // +0x80
    this->curveKey2[5] = DAT_00e44948;   // +0x90
    this->curveKey2[6] = DAT_00e44634;   // +0xA0

    // Next set: offsets 0x40 (0x10*4), 0x54 (0x15), 0x64 (0x19), 0x74 (0x1d), 0x84 (0x21), 0x94 (0x25), 0xA4 (0x29)
    this->curveKey3[0] = DAT_00e44634;   // +0x40
    this->curveKey3[1] = DAT_00e445f8;   // +0x54
    this->curveKey3[2] = DAT_00e44718;   // +0x64
    this->curveKey3[3] = DAT_00d5ccf8;   // +0x74
    this->curveKey3[4] = DAT_00e445ac;   // +0x84
    this->curveKey3[5] = DAT_00e44948;   // +0x94
    this->curveKey3[6] = DAT_00e44634;   // +0xA4

    // Next set: offsets 0x44 (0x11*4), 0x58 (0x16), 0x68 (0x1a), 0x78 (0x1e), 0x88 (0x22), 0x98 (0x26), 0xA8 (0x2a)
    this->curveKey4[0] = DAT_00e44634;   // +0x44
    this->curveKey4[1] = DAT_00e445f8;   // +0x58
    this->curveKey4[2] = DAT_00e44718;   // +0x68
    this->curveKey4[3] = DAT_00d5ccf8;   // +0x78
    this->curveKey4[4] = DAT_00e445ac;   // +0x88
    this->curveKey4[5] = DAT_00e44948;   // +0x98
    this->curveKey4[6] = DAT_00e44634;   // +0xA8

    // Finally, offset 0x48 (0x12*4) set to DAT_00e44634
    this->curveKey5[0] = DAT_00e44634;   // +0x48

    return this;
}