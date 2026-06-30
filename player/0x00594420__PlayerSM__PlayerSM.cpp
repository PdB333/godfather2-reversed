// FUNC_NAME: PlayerSM::PlayerSM
void __thiscall PlayerSM::PlayerSM(uint thisPtr)
{
    // Call base class or sub-initializer
    FUN_0059b5e0(); // Probably base constructor or global init

    *(float*)(thisPtr + 0xb0) = *(float*)0x00e2b1a4; // +0xB0: some float (gravity? speed?)
    *(uint*)(thisPtr + 0x7c) = (*(uint*)(thisPtr + 0x7c) & 0xFFFFC700) | 0x700; // +0x7C: flags, set bits 8-10?
    *(float*)(thisPtr + 0xb4) = *(float*)0x00e35654; // +0xB4: another float
    *(float*)(thisPtr + 0xb8) = 0.0f; // +0xB8
    *(float*)(thisPtr + 0xbc) = 0.0f; // +0xBC

    // Subobject at +0xA0 – likely a quaternion (identity: 0,0,0,1)
    typedef void (__thiscall *SetFunc)(float,float,float,float,void*);
    SetFunc setIdentity = (SetFunc)(*(int*)(*(int*)0x012055a8 + 4));
    setIdentity(0.0f, 0.0f, 0.0f, 1.0f, (void*)(thisPtr + 0xA0));

    // Subobject at +0x80 – likely a vector (0,0,1,0) – maybe direction?
    SetFunc setDirection = (SetFunc)(*(int*)(*(int*)0x012055a8 + 4));
    setDirection(0.0f, 0.0f, 1.0f, 0.0f, (void*)(thisPtr + 0x80));

    // Another method on subobject at +0xA0 (at vtable offset 8)
    typedef void (__thiscall *NormalizeFunc)(void*);
    NormalizeFunc normalize = (NormalizeFunc)(*(int*)(*(int*)0x012055a8 + 8));
    normalize((void*)(thisPtr + 0xA0));

    *(uint16*)(thisPtr + 0xf4) = 0; // +0xF4: short
    *(uint16*)(thisPtr + 0xf6) = 0; // +0xF6: short
    *(int*)(thisPtr + 0xfc) = 0;    // +0xFC
    *(uint16*)(thisPtr + 0xfa) = 0; // +0xFA: short
    *(int*)(thisPtr + 0xf0) = 0;    // +0xF0: state/mode
    *(uint16*)(thisPtr + 0xf8) = 4; // +0xF8: short, initial state? 4

    *(uint16*)(thisPtr + 0x104) = 0; // +0x104: short
    *(uint16*)(thisPtr + 0x106) = 0; // +0x106: short
    *(int*)(thisPtr + 0x10c) = 0;    // +0x10C
    *(uint16*)(thisPtr + 0x10a) = 0; // +0x10A: short
    *(int*)(thisPtr + 0x100) = 0;    // +0x100
    *(uint16*)(thisPtr + 0x108) = 4; // +0x108: short, initial state? 4

    *(float*)(thisPtr + 0x130) = *(float*)0x00e2b1a4; // +0x130: same as +0xB0
    *(float*)(thisPtr + 0x134) = *(float*)0x00e2b1a4; // +0x134: same

    // Set many fields to 0
    *(int*)(thisPtr + 0x13c) = 0;
    *(int*)(thisPtr + 0x144) = 0;
    *(int*)(thisPtr + 0x148) = 0;
    *(int*)(thisPtr + 0x14c) = 0;
    *(int*)(thisPtr + 0x150) = 0;
    *(int*)(thisPtr + 0x160) = 0;

    *(float*)(thisPtr + 0x138) = *(float*)0x00e2afac; // +0x138: another global float
    *(int*)(thisPtr + 0x140) = 8; // +0x140: some count/flag
    *(int*)(thisPtr + 0x154) = 0;
    *(int*)(thisPtr + 0x158) = 0;
    *(int*)(thisPtr + 0x15c) = 0;
}