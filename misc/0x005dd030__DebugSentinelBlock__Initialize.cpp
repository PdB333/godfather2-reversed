// FUNC_NAME: DebugSentinelBlock::Initialize
void __thiscall DebugSentinelBlock::Initialize(void *this) // EAX = this, size ~0x68 bytes
{
    // +0x44 (in_EAX[0x11]) and +0x4C (in_EAX[0x13]) set to 96000 (likely max timer or counter)
    *(int *)((char *)this + 0x44) = 96000;
    *(int *)((char *)this + 0x4C) = 96000;

    // +0x00, +0x04, +0x28, +0x2C set to value from global DAT_00e2b1a4 (likely a default constant)
    *(int *)this = DAT_00e2b1a4;
    *(int *)((char *)this + 0x04) = DAT_00e2b1a4;
    *(int *)((char *)this + 0x28) = DAT_00e2b1a4;
    *(int *)((char *)this + 0x2C) = DAT_00e2b1a4;

    // +0x21, +0x22 bytes set to 0 (flags/padding)
    *(char *)((char *)this + 0x21) = 0;
    *(char *)((char *)this + 0x22) = 0;

    // +0x08, +0x24, +0x30, +0x34, +0x48, +0x23 set to 0
    *(int *)((char *)this + 0x08) = 0;
    *(int *)((char *)this + 0x24) = 0;
    *(int *)((char *)this + 0x30) = 0;
    *(int *)((char *)this + 0x34) = 0;
    *(int *)((char *)this + 0x48) = 0;
    *(char *)((char *)this + 0x23) = 0;

    // +0x0C set to 1 (boolean flag)
    *(int *)((char *)this + 0x0C) = 1;

    // Sentinel magic numbers for uninitialized detection
    *(int *)((char *)this + 0x10) = 0xbadbadba;
    *(int *)((char *)this + 0x14) = 0xbeefbeef;
    *(int *)((char *)this + 0x18) = 0xeac15a55;
    *(int *)((char *)this + 0x1C) = 0x91100911;

    // +0x38 set to global DAT_00e2b118, +0x3C set to DAT_00e2b1a4 (alternative default)
    *(int *)((char *)this + 0x38) = DAT_00e2b118;
    *(int *)((char *)this + 0x3C) = DAT_00e2b1a4;

    // +0x50..0x64 set to 0 (8 dwords)
    *(int *)((char *)this + 0x50) = 0;
    *(int *)((char *)this + 0x54) = 0;
    *(int *)((char *)this + 0x58) = 0;
    *(int *)((char *)this + 0x5C) = 0;
    *(int *)((char *)this + 0x60) = 0;
    *(int *)((char *)this + 0x64) = 0;
}