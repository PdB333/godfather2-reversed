// FUNC_NAME: Player::Player
// Address: 0x008022b0
// Constructor for the Player class. Initializes all member variables, sets up vtable pointers,
// registers message handlers, and performs initialization of various subsystems.

#include <cstdint>

class Player {
public:
    // Constructor
    Player(void* param_2, void* param_3, void* param_4, void* param_5, void* param_6);
    virtual ~Player(); // likely

private:
    // Fields (offsets in hex)
    // +0x000: vtable pointer
    // +0x004..+0x3FC: various fields
    // +0x7C7: character used for table initialization
    // etc.
};

// Global data references (from Ghidra)
extern uint32_t DAT_00e44594;
extern uint32_t DAT_00d5d7b8;
extern uint32_t DAT_00d5ccf8;
extern uint32_t _DAT_00d5780c;
extern uint32_t DAT_00d5d934;
extern uint32_t DAT_00e446f4;
extern uint32_t DAT_00d5779c;
extern uint32_t DAT_00d5efa4;
extern uint32_t DAT_00d5eee4;
extern uint32_t DAT_00d71b10;
extern uint32_t DAT_00d5ddec;
extern uint32_t DAT_00e544d8;
extern uint32_t DAT_00e2e37c;
extern uint32_t DAT_00d5ef90;
extern uint32_t DAT_00e53770;
extern uint32_t DAT_00d71b20;
extern uint32_t DAT_00d71b24;
extern uint32_t DAT_00d71b30;
extern uint32_t DAT_00d5c454;
extern uint32_t DAT_00d71b3c;
extern uint32_t DAT_00d71b64;
extern uint32_t DAT_00d71b6c;
extern uint32_t DAT_00d71b74;
extern uint32_t DAT_00d71b7c;
extern uint32_t DAT_00d71b84;
extern uint32_t DAT_00d5c458;
extern uint32_t DAT_0112d9e4;
extern uint32_t DAT_0112f1dc;
extern uint32_t DAT_0112edf4;
extern uint32_t DAT_0112ef7c;

// External functions
extern void FUN_009c5140(void* param_2, void* param_3, void* param_4, void* param_5);
extern void FUN_0054da10();
extern void FUN_005fdac0();
extern uint32_t FUN_009c8f80(void* param_6);
extern void FUN_00704340(uint32_t, void*);
extern void FUN_007fa810();
extern void FUN_00549bf0();
extern void FUN_0080c150();
extern void FUN_007ee510();
extern void FUN_007ee9e0();
extern void FUN_005fea00(uint32_t, int);
extern int FUN_00471610();
extern void FUN_006016e0(int);
extern void FUN_004daf90(uint32_t*);
extern void FUN_007fc9f0();
extern void FUN_004dde90(uint32_t*, int);
extern void FUN_007ee550(Player*);
extern void FUN_007ee690(Player*);
extern int FUN_009c8e50(int);
extern int FUN_008c9790(uint32_t);
extern void FUN_007f7380();
extern void FUN_00408240(uint32_t*, const char*);
extern void FUN_00408900(uint32_t*, uint32_t*, uint32_t);
extern void FUN_00408680(uint32_t*);

// Global array for table manipulation
extern uint8_t DAT_0112c7bf[0x50]; // size 0x50

Player::Player(void* param_2, void* param_3, void* param_4, void* param_5, void* param_6)
{
    uint32_t uVar1, uVar2, uVar4;
    uint32_t uVar5, uVar7, uVar8, uVar9;
    int iVar6;
    int* piVar10;
    bool bVar11;

    // Call base class constructor (likely EARSObject or similar)
    FUN_009c5140(param_2, param_3, param_4, param_5);

    // Set vtable pointers (multiple virtual function tables)
    this->field_0xE4 = &PTR_LAB_00d71bdc; // +0xE4
    this->field_0xE6 = 0;                  // +0xE6
    this->field_0xE5 = &PTR_LAB_00d58278; // +0xE5
    this->field_0xE9 = 0;                  // +0xE9
    this->field_0xE8 = &PTR_LAB_00d71d6c; // +0xE8
    this->vtable = &PTR_FUN_00d720a8;      // +0x00
    this->field_0xF = &PTR_LAB_00d72098;   // +0x0F
    this->field_0x12 = &PTR_LAB_00d72094;  // +0x12
    this->field_0x14 = &PTR_LAB_00d72090;  // +0x14
    this->field_0x15 = &PTR_LAB_00d72030;  // +0x15
    this->field_0x16 = &PTR_LAB_00d71fc8;  // +0x16
    this->field_0xE4 = &PTR_LAB_00d71fa8;  // +0xE4 (overwritten)
    this->field_0xE5 = &PTR_FUN_00d71f94;  // +0xE5 (overwritten)
    this->field_0xE8 = &PTR_LAB_00d71f8c;  // +0xE8 (overwritten)
    this->field_0xEB = 0;                  // +0xEB
    this->field_0xEC = 0;                  // +0xEC

    // Initialize subsystems
    FUN_0054da10();
    FUN_005fdac0();

    // Initialize many fields to zero
    this->field_0x17C = 1;  // +0x17C
    this->field_0x17D = 0;  // +0x17D
    this->field_0x17E = 0;  // +0x17E
    this->field_0x17F = 0;  // +0x17F
    this->field_0x180 = 0;  // +0x180
    this->field_0x181 = 0;  // +0x181
    this->field_0x182 = 0;  // +0x182
    this->field_0x183 = 0;  // +0x183
    *(uint8_t*)(this + 0x184) = 0;   // +0x184
    *(uint8_t*)((int)this + 0x611) = 0; // +0x611
    *(uint8_t*)((int)this + 0x612) = 0; // +0x612
    this->field_0x185 = 0;  // +0x185
    this->field_0x186 = 0;  // +0x186
    this->field_0x187 = 0;  // +0x187
    this->field_0x188 = 0;  // +0x188
    this->field_0x189 = 0;  // +0x189
    this->field_0x18A = 0;  // +0x18A
    this->field_0x18B = 0;  // +0x18B

    // Clear array of 22 elements starting at +0x198
    uint32_t* puVar3 = &this->field_0x198;
    iVar6 = 0x16;
    do {
        *puVar3 = 0;
        puVar3++;
        iVar6--;
    } while (iVar6 >= 0);

    // More zeroing
    this->field_0x1B5 = 0;
    this->field_0x1B6 = 0;
    this->field_0x1B7 = 0;
    this->field_0x1B8 = 0;
    this->field_0x1B9 = 0;
    this->field_0x1BA = 0;
    this->field_0x1BB = 0;
    this->field_0x1BC = 0;
    this->field_0x1BD = 0;
    this->field_0x1BE = 0;
    this->field_0x1BF = 0;
    this->field_0x1C0 = 0;
    this->field_0x1C1 = 0;
    this->field_0x1C2 = 0;
    this->field_0x1C3 = 0;
    this->field_0x1C4 = 0;
    this->field_0x1C5 = 0;
    this->field_0x1C6 = 0;

    // Process param_6
    uVar4 = FUN_009c8f80(param_6);
    FUN_00704340(uVar4, param_6);

    // More zeroing
    this->field_0x1D3 = 0;
    this->field_0x1D4 = 0;
    this->field_0x1D7 = 0;
    this->field_0x1D8 = 0;
    this->field_0x1D9 = 0;
    this->field_0x1DA = 0;
    this->field_0x1DB = 0;
    this->field_0x1DC = 0;
    this->field_0x1DD = 0;
    this->field_0x1DE = 0;
    this->field_0x1DF = 0;
    this->field_0x1E0 = 0;
    this->field_0x1E1 = 0;
    this->field_0x1E2 = 0;
    this->field_0x1E3 = 0;
    this->field_0x1E4 = 0;
    this->field_0x1E5 = 0;
    this->field_0x1E6 = 0;

    // Copy global values into fields
    uVar2 = DAT_00e44594;
    uVar1 = DAT_00d5d7b8;
    this->field_0x1E7 = 0;
    this->field_0x1EB = DAT_00d5ccf8 средњим;
    uVar4 = _DAT_00d5780c;
    this->field_0x1EC = _DAT_00d5780c;
    this->field_0x1ED = uVar4;
    this->field_0x1EE = DAT_00d5d934;
    this->field_0x1EF = DAT_00e446f4;
    uVar4 = DAT_00d5779c;
    this->field_0x1F0 = DAT_00d5779c;
    this->field_500 = uVar4; // offset 0x1F4? Actually 500*4 = 0x7D0, but likely a typo
    this->field_0x1F6 = DAT_00d5efa4;
    uVar4 = DAT_00d5eee4;
    this->field_0x1F2 = uVar2;
    uVar2 = DAT_00d71b10;
    this->field_0x1F7 = uVar4;
    uVar4 = DAT_00d5ddec;
    this->field_0x1E8 = 0;
    this->field_0x1E9 = 0;
    this->field_0x1EA = 0;
    this->field_0x1F1 = uVar1;
    this->field_499 = uVar2; // offset 0x7CC? again likely a typo
    this->field_0x1F5 = uVar1;
    this->field_0x1F8 = uVar42;

    // More zeroing
    this->field_0x1F9 = 0;
    this->field_0x1FA = 0;
    this->field_0x1FB = 0;
    this->field_0x1FC = 0;
    this->field_0x1FD = 0;
    this->field_0x1FE = 0;
    this->field_0x1FF = 0;
    this->field_0x200 = 0;
    this->field_0x201 = 0;
    this->field_0x202 = 0;
    this->field_0x203 = 0;
    this->field_0x204 = 0;
    this->field_0x205 = 0;
    this->field_0x206 = 0;
    this->field_0x207 = 0;
    this->field_0x20A = 0;
    this->field_0x20B = 0;
    this->field_0x20C = 0;
    this->field_0x20D = 0;
    this->field_0x20E = 0;
    this->field_0x210 = 0;
    this->field_0x211 = 0;
    this->field_0x212 = 0;
    this->field_0x213 = 0;
    this->field_0x214 = 0;
    this->field_0x215 = DAT_00e544d8;
    this->field_0x216 = 4;
    this->field_0x217 = 4;
    this->field_0x218 = 0;
    this->field_0x219 = 0;
    this->field_0x225 = 0;
    this->field_0x226 = 0;
    this->field_0x227 = 0;
    this->field_0x232 = 0;
    this->field_0x233 = 0;
    this->field_0x234 = 0;
    this->field_0x235 = 0;
    this->field_0x236 = 0;
    this->field_0x237 = DAT_00e2e37c;
    this->field_0x243 = 0;

    FUN_007fa810();

    this->field_0x3FC = 0;
    this->field_0x3FD = 0;
    this->field_0x3FF = 0;
    this->field_0x400 = 0;
    this->field_0x401 = 0;
    this->field_0x402 = 0;

    // Call a function 10 times
    iVar6 = 9;
    do {
        FUN_00549bf0();
        iVar6--;
    } while (iVar6 >= 0);

    // Set sentinel values (debug markers)
    *(uint8_t*)(this + 0x6E3) = 0; // +0x6E3
    this->field_0x6E4 = 0;
    this->field_0x6E5 = 0;
    this->field_0x6E7 = 0xbeefbeef; // sentinel
    this->field_0x6E8 = 0xeac15a55; // sentinel
    this->field_0x6E9 = 0x91100911; // sentinel
    this->field_0x6E6 = 0xbadbadba; // sentinel
    this->field_0x6EA = 0;
    this->field_0x6EB = 0;
    this->field_0x6EC = 0;
    this->field_0x6ED = 0;
    this->field_0x6F1 = 0;
    this->field_0x6F2 = 0;
    this->field_0x6F3 = 0;
    this->field_0x6F6 = 0xeac15a55DOIs;
    this->field_0x6F4 = 0xbadbadba;
    this->field_0x6F5 = 0xbeefbeef;
    this->field_0x6F7 = 0x91100911;
    this->field_0x6FA = 0xeac15a55;
    this->field_0x6F8 = 0xbadbadba;
    this->field_0x6F9 = 0xbeefbeef;
    this->field_0x6FB = 0x91100911;
    this->field_0x6FC = 0;
    this->field_0x6FD = 0;
    this->field_0x6FE = 0;
    this->field_0x6FF = 0;
    this->field_0x71E = 0;
    this->field_0x71F = 0;
    this->field_0x720 = 0xfe16702f; // another sentinel
    this->field_0x721 = 0;
    this->field_0x722 = 0;
    this->field_0x730 = 02;

    // Initialize a series of 10 pairs of fields (each pair: uint32_t + uint16_t)
    // Offsets: 0x731, 0x732, 0x733, ... up to 0x745
    *(uint16_t*)(this + 0x731) = 0;
    *(uint16_t*)((int)this + 0x1CC6) = 0; // +0x1CC6
    this->field_0x732 = 0;
    *(uint16_t*)(this + 0x733) = 0;
    *(uint16_t*)((int)this + 0x1CCE) = 0;
    this->field_0x734 = 0;
    *(uint16_t*)(this + 0x735) = 0;
    *(uint16_t*)((int)this + 0x1CD6) = 0;
    this->field_0x736 = 0;
    *(uint16_t*)(this + 0x737) = 0;
    *(uint16_t*)((int)this + 0x1CDE) = 0;
    this->field_0x738 = 0;
    *(uint16_t*)(this + 0x739) = 0;
    *(uint16_t*)((int)this + 0x1CE6) = 0;
    this->field_0x73A = 0;
    *(uint16_t*)(this + 0x73B) = 0;
    *(uint16_t*)((int)this + 0x1CEE) = 0;
    this->field_0x73C = 0;
    *(uint16_t*)(this + 0x73D) = 0;
    *(uint16_t*)((int)this + 0x1CF6) = 0;
    this->field_0x73E = 0;
    *(uint16_t*)(this + 0x73F) = 0;
    *(uint16_t*)((int)this + 0x1CFE) = 0;
    this->field_0x740 = 0;
    *(uint16_t*)(this + 0x741) = 0;
    *(uint16_t*)((int)this + 0x1D06) = 0;
    this->field_0x742 = 0;
    *(uint16_t*)(this + 0x743) = 0;
    *(uint16_t*)((int)this + 0x1D0E) = 0;
    this->field_0x744 = 0;
    *(uint16_t*)(this + 0x745) = 0;
    *(uint16_t*)((int)this + 0x1D16) = 0;

    FUN_0080c150();

    *(uint8_t*)(this + 0x782) = 0; // +0x782

    FUN_007ee510();
    FUN_007ee9e0();

    // Zero a large block of fields (0x790 to 0x7AB)
    this->field_0x790 = 0;
    this->field_0x791 = 0;
    this->field_0x792 = 0;
    this->field_0x793 = 0;
    this->field_0x794 = 0;
    this->field_0x795 = 0;
    this->field_0x796 = 0;
    this->field_0x797 = 0;
    this->field_0x798 = 0;
    this->field_0x799 = 0;
    this->field_0x79A = 0;
    this->field_0x79B = 0;
    this->field_0x79C = 0;
    this->field_0x79D = 0;
    this->field_0x79E = 0;
    this->field_0x79F = 0;
    this->field_0x7A0 = 0;
    this->field_0x7A1 = 0;
    this->field_0x7A2 = 0;
    this->field_0x7A3 = 0;
    this->field_0x7A4 = 0;
    this->field_0x7A5 = 0;
    uVar4 = DAT_00d5ef90;
    this->field_0x7A6 = 0;
    this->field_0x7A7 = 0;
    this->field_0x7A8 = 0;
    this->field_0x7A9 = 0;
    this->field_0x7AA = 0;
    this->field_0x7AB = uVar4;
    this->field_0x7AC = 0;
    this->field_0x7AD = 0;
    this->field_0x7AE = 0;
    this->field_0x7AF = 0;
    this->field_0x7B0 = 0;
    *(uint8_t*)(this + 0x7B1) = 0; // +0x7B1
    *(uint8_t*)((int)this + 0x1EC5) = 0; // +0x1EC5
    this->field_0x7B2 = 0;
    this->field_0x7B3 = 0;
    this->field_0x7B4 = 0;
    this->field_0x7B5 = 0;
    this->field_0x7B6 = 0;
    this->field_0x7B7 = 0;
    this->field_0x7BD = 0xffffffff;
    this->field_0x7BE = 0xffffffff;

    // Initialize a character at +0x7C7 from a global array
    iVar6 = DAT_00e53770;
    bVar11 = (DAT_00e53770 == 0);
    this->field_0x7B8 = 0;
    this->field_0x7B9 = 0;
    this->field_0x7BA = 0;
    this->field_0x7BB = 0;
    this->field_0x7BC = 0xde578cc7; // sentinel
    this->field_0x7BF = 0;
    this->field_0x7C0 = 0;
    this->field_0x7C1 = 0;
    this->field_0x7C2 = 0;
    this->field_0x7C3 = 0;
    this->field_0x7C4 = 0x46f5c7b4; // sentinel
    this->field_0x7C5 = 0;
    this->field_0x7C6 = 0;
    *(uint8_t*)(this + 0x7C7) = 0; // +0x7C7

    if (bVar11) {
        *(uint8_t*)(this + 0x7C7) = 0x50; // 'P'
    } else {
        DAT_00e53770 = iVar6 - 1;
        *(uint8_t*)(this + 0x7C7) = DAT_0112c7bf[iVar6];
    }

    // If the character is not 'P', perform a complex table manipulation
    if (*(char*)(this + 0x7C7) != 'P') {
        uint32_t uVar7 = 2;
        do {
            uVar8 = (uint32_t)*(uint8_t*)(this + 0x7C7);
            uVar9 = uVar7 - 2;
            if (uVar8 != uVar9) {
                uVar5 = uVar9;
                if (uVar9 < uVar8) {
                    uVar5 = uVar8;
                    uVar8 = uVar9;
                }
                DAT_0112c7bf[(uVar5 - ((-uVar8 + 0x4f) * (-uVar8 + 0x50) >> 1)) - uVar8] = 0;
            }
            uVar8 = (uint32_t)*(uint8_t*)(this + 0x7C7);
            uVar9 = uVar7 - 1;
            if (uVar8 != uVar9) {
                uVar5 = uVar9;
                if (uVar9 < uVar8) {
                    uVar5 = uVar8;
                    uVar8 = uVar9;
                }
                DAT_0112c7bf[(uVar5 - ((-uVar8 + 0x4f) * (-uVar8 + 0x50) >> 1)) - uVar8] = 0;
            }
            uVar9 = (uint32_t)*(uint8_t*)(this + 0x7C7);
            if (uVar9 != uVar7) {
                uVar8 = uVar7;
                if (uVar7 < uVar9) {
                    uVar8 = uVar9;
                    uVar9 = uVar7;
                }
                DAT_0112c7bf[(uVar8 - ((-uVar9 + 0x4f) * (-uVar9 + 0x50) >> 1)) - uVar9] = 0;
            }
            uVar8 = (uint32_t)*(uint8_t*)(this + 0x7C7);
            uVar9 = uVar7 + 1;
            if (uVar8 != uVar9) {
                uVar5 = uVar9;
                if (uVar9 < uVar8) {
                    uVar5 = uVar8;
                    uVar8 = uVar9;
                }
                DAT_0112c7bf[(uVar5 - ((-uVar8 + 0x4f) * (-uVar8 + 0x50) >> 1)) - uVar8] = 0;
            }
            uVar8 = (uint32_t)*(uint8_t*)(this + 0x7C7);
            uVar9 = uVar7 + 2;
            if (uVar8 != uVar9) {
                uVar5 = uVar9;
                if (uVar9 < uVar8) {
                    uVar5 = uVar8;
                    uVar8 = uVar9;
                }
                DAT_0112c7bf[(uVar5 - ((-uVar8 + 0x4f) * (-uVar8 + 0x50) >> 1)) - uVar8] = 0;
            }
            uVar9 = uVar7 + 3;
            uVar7 = uVar7 + 5;
        } while (uVar9 < 0x50);
    }

    uVar4 = DAT_00d5eee4;
    this->field_0x157 = this; // self-reference
    FUN_005fea00(uVar4, 0apse);
    this->field_0x15B = 0;
    this->field_0x159 |= 0x20; // set bit 5

    iVar6 = FUN_00471610();
    FUN_006016e0(iVar6 + 0x30);

    if (this->field_0x3FC != 0) {
        FUN_004daf90(&this->field_0x3FC);
        this->field_0x3FC = 0;
    }
    *(uint8_t*)(this + 0x3FE) = 0; // +0x3FE
    *(uint8_t*)((int)this + 0xFF9) = 0xFF; // +0xFF9

    FUN_007fc9f0();

    piVar10 = &this->field_0x6EA;
    this->field_0x181 = 0;
    this->field_0x182 = 0;
    this->field_0x720 = 0xfe16702f;
    if (*piVar10 != 0) {
        FUN_004daf90(piVar10);
        *piVar10 = 0;
    }
    this->field_0x6EC = 0;
    piVar10 = &this->field_0x6FC;
    this->field_0x6EE = 0;
    this->field_0x6EF = 0;
    this->field_0x6F0 = 0;
    if (*piVar10 != 0) {
        FUN_004daf90(piVar10);
        *piVar10 = 0;
    }
    this->field_0x6FE = 0;
    this->field_0x700 = 0;
    this->field_0x701 = 0;
    this->field_0x702 = 0;

    // Call virtual function via vtable at +0x16
    (*(void (**)(int))(this->field_0x16 + 0x28))(0x20);

    FUN_004dde90(&this->field_0x238, 0x80);

    // Zero a block of fields (0x21A to 0x224)
    this->field_0x21B = 0;
    this->field_0x21A = 0;
    this->field_0x21D = 0;
    this->field_0x21C = 0;
    this->field_0x21F = 0;
    this->field_0x21E = 0;
    this->field_0x221 = 0;
    this->field_0x220 = 0;
    this->field_0x223 = 0;
    this->field_0x222 = 0;
    this->field_0x224 = 0;

    *(uint8_t*)(this + 0x184) = 0;
    *(uint8_t*)((int)this + 0x611) = 0;
    *(uint8_t*)((int)this + 0x612) = 0;

    this->field_0x228 = 0;
    this->field_0x6E9 = 0;
    this->field_0x6E8 = 0;
    this->field_0x6E7 = 0;
    this->field_0x6E6 = 0;
    this->field_0x6F7 = 0;
    this->field_0x6F6 = 0;
    this->field_0x6F5 = 0;
    this->field_0x6F4 = 02;

    piVar10 = &this->field_0x7A7;
    this->field_0x6FB = 0;
    this->field_0x6FA = 0;
    this->field_0x6F9 = 0;
    this->field_0x6F8 = 0;
    if (*piVar10 != 0) {
        FUN_004daf90(piVar10);
        *piVar10 = 0;
    }

    this->field_0x730 = 0;
    this->field_0x732 = 0;
    this->field_0x734 = 0;
    this->field_0x736 = 0;
    this->field_0x738 = 0;
    this->field_0x73A = 0;
    this->field_0x73C = 0;
    this->field_0x73E = 0;
    this->field_0x740 = 0;
    this->field_0x742 = 0;
    this->field_0x744 = 0;

    this->field_0x1D5 = 0;
    this->field_0x1D6 = 0;
    this->field_0x748 = 0;
    this->field_0x74A = 0;
    this->field_0x74C = 0;
    this->field_0x74E = 0;
    this->field_0x74F = 0;
    this->field_0x750 = 0;
    this->field_0x751 = 0;

    this->field_0xED = 0;

    // Set some fields from globals
    this->field_0x723 = DAT_00d71b20;
    this->field_0x724 = DAT_00d71b24;
    this->field_0x725 = DAT_00d71b20;
    this->field_0x726 = DAT_00d71b24;
    this->field_0x727 = DAT_00d71b30;
    this->field_0x728 = DAT_00d5c454;
    this->field_0x729 = DAT_00d71b30;
    this->field_0x72A = DAT_00d71b3c;

    this->field_0x1AF = 0xffffffff;
    this->field_0x1B0 = 0xffffffff;
    this->field_0x1B1 = 0xffffffff;
    this->field_0x1B2 = 0xffffffff;
    this->field_0x1B3 = 0xffffffff;
    *(uint16_t*)(this + 0x1B4) = 0xffff;

    piVar10 = &this->field_0x1D3;
    *(uint8_t*)((int)this + 0x6D2) = 0xFF;
    if (*piVar10 != 0) {
        FUN_004daf90(piVar10);
        *piVar10 = 0;
    }

    uVar4 = DAT_00d71b84;
    *(uint64_t*)(this + 0x1C7) = DAT_00d71b64; // 8 bytes
    *(uint64_t*)(this + 0x1C9) = DAT_00d71b6c;
    *(uint64_t*)(this + 0x1CB) = DAT_00d71b74;
    *(uint64_t*)(this + 0x1CD) = DAT_00d71b7c;
    this->field_0x1CF = uVar4;

    this->field_0x23E = 0;
    this->field_0x23D = 0;
    this->field_0x23C = 0;

    FUN_007ee550(this);
    FUN_007ee690(this);

    // Clean up pointer arrays
    piVar10 = &this->field_0x1F9;
    iVar6 = 7;
    do {
        if (*piVar10 != 0) {
            FUN_004daf90(piVar10);
            *piVar10 = 0;
        }
        piVar10 += 2;
        iVar6--;
    } while (iVar6 != 0);

    piVar10 = &this->field_0x1D7;
    iVar6 = 8;
    do {
        if (*piVar10 != 0) {
            FUN_004daf90(piVar10);
            *piVar10 = 0;
        }
        piVar10 += 2;
        iVar6--;
    } while (iVar6 != 0);

    // Allocate and initialize a structure
    iVar6 = FUN_009c8e50(0x44);
    if (iVar6 == 0) {
        iVar6 = 0;
    } else {
        iVar6 = FUN_008c9790(this->field_0x1F6);
    }
    uVar4 = this->field_0x1F8;
    this->field_0x1EA = iVar6;
    *(uint32_t*)(iVar6 + 0x38) = this->field_0x1F7;
    *(uint32_t*)(iVar6 + 0x3C) = uVar4;

    FUN_007f7380();

    if (this->field_0x790 != 0) {
        FUN_004daf90(&this->field_0x790);
        this->field_0x790 = 0;
    }

    uVar4 = DAT_00d5ccf8;
    this->field_0x218 = 0;
    this->field_0x208 = 0;
    this->field_0x749 = uVar4;
    this->field_0x74B = uVar4;
    uVar4 = _DAT_00d5c458;
    this->field_0x186 = _DAT_00d5c458;
    this->field_0x187 = uVar4;
    this->field_0x188 = uVar4;
    this->field_0x189 = uVar4;
    this->field_0x18A = uVar4;
    this->field_0x18B = uVar4;
    this->field_0x209 = 0;
    this->field_0x25C = 0;

    // Register message handlers
    FUN_00408240(&DAT_0112d9e4, "iMsgBroadcastTemporaryLookatPoint");
    if (DAT_0112d9e4 != 0) {
        FUN_00408900(&this->field_0xF, &DAT_0112d9e4, 0x8000);
    }
    FUN_00408240(&DAT_0112f1dc, "iMsgSentientScoreboardRegistrationNotice");
    if (DAT_0112f1dc != 0) {
        FUN_00408900(&this->field_0xF, &DAT_0112f1dc, 0x8000);
    }
    FUN_00408240(&DAT_0112edf4, "iMsgVoipBroadcastStart");
    FUN_00408240(&DAT_0112ef7c, "iMsgVoipBroadcastStop");
    FUN_00408680(&DAT_0112edf4);
    FUN_00408680(&DAT_0112ef7c);

    this->field_0x6E2 = 0;
    this->field_0x6E1 = 0;
    this->field_0x6E0 = 0;
    this->field_0x20F = 0;

    return;
}