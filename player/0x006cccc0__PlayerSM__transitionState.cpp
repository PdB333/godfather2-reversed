// FUNC_NAME: PlayerSM::transitionState
// Address: 0x006cccc0
// Swaps between mutually exclusive state flags (bit1 and bit2) and sets auxiliary bits (11 and 19).
// This is likely part of a state machine transition (e.g., between ground and air states).

class PlayerSM {
public:
    // +0xdc: State flags (bit0..bit31)
    uint32_t m_stateFlags;

    // __thiscall: this in ecx
    __declspec(naked) void transitionState() {
        __asm {
            push ebp
            mov ebp, esp
            push ecx          // save this
            mov eax, ecx      // eax = this
            // Check bit 1 (mask 0x2)
            mov ecx, [eax+0xdc]
            shr ecx, 1
            and ecx, 1
            test ecx, ecx
            jz L1
            // Bit1 set: clear it and set bits 1+11+19? Actually set 0x80802 which has bit1, bit11, bit19
            and dword ptr [eax+0xdc], 0xfffffffd   // clear bit1
            or dword ptr [eax+0xdc], 0x80802       // set bits 1,11,19
            pop ecx
            pop ebp
            ret
L1:
            // Check bit 2 (mask 0x4)
            mov ecx, [eax+0xdc]
            shr ecx, 2
            and ecx, 1
            test ecx, ecx
            jz L2
            // Bit2 set: clear it and set bits 2+11+19 (0x80804)
            and dword ptr [eax+0xdc], 0xfffffffb   // clear bit2
            or dword ptr [eax+0xdc], 0x80804       // set bits 2,11,19
L2:
            pop ecx
            pop ebp
            ret
        }
    }
};