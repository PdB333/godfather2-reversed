// Xbox PDB: EARS_Modules_TopDonChallenge_TopDonChallenge
// FUNC_NAME: TopDonChallenge::TopDonChallenge
// Address: 0x008383a0
// Constructor for the Top Don Challenge manager (manages challenge lifecycle and messages)

TopDonChallenge* __thiscall TopDonChallenge::TopDonChallenge(TopDonChallenge* this, int param_2)
{
    // Initialize base component (unknown class)
    sub_46C590(param_2); // FUN_0046c590

    // Set virtual function tables
    this->vtable = &TopDonChallenge_vtable;                  // +0x00
    this->someVtable1 = &someVtable1_00d73cd4;               // +0x3C (0xF * 4)
    this->someVtable2 = &someVtable2_00d73cd0;               // +0x48 (0x12 * 4)

    // Zero out 18 integer fields starting at offset 0x50
    // Likely an array or a set of flags
    for (int i = 0; i < 18; i++)
        this->unknownField[i] = 0;                           // +0x50 through +0x94

    // Zero out 10 challenge entries (each 8 bytes: two shorts and one int)
    // Structure: short field1, short field2; int field3
    for (int j = 0; j < 10; j++)
    {
        *(short*)((char*)this + 0x98 + j * 8) = 0;           // +0x98 + j*8
        *(short*)((char*)this + 0x9A + j * 8) = 0;           // +0x9A + j*8
        *(int*)((char*)this + 0x9C + j * 8) = 0;             // +0x9C + j*8
    }

    // Zero four integer fields at offset 0xE8..0xF4
    for (int k = 0; k < 4; k++)
        this->fieldE8[k] = 0;                                // +0xE8, +0xEC, +0xF0, +0xF4

    // Initialize challenge state indices
    this->currentChallengeIndex = -1;                        // +0xF8 (0x3E*4)
    this->challengeState = 0;                                 // +0xFC (0x3F*4)

    // Set debug signature / magic values
    this->magicBad = 0xBADBADBA;                             // +0x11C (0x47*4)
    this->magicBeef = 0xBEEFBEEF;                            // +0x120 (0x48*4)
    this->magicEars = 0xEAC15A55;                            // +0x124 (0x49*4)
    this->magicShock = 0x91100911;                           // +0x128 (0x4A*4)

    // Zero a large block of fields (0x12C through 0x198)
    for (int m = 0; m < 0x1C; m++)                           // 0x66 - 0x4B +1 = 0x1C (28 integers)
        this->field4B[m] = 0;                                // +0x12C through +0x198

    // Initialize timer-related fields
    this->field100 = 0;                                      // +0x100 (0x40*4)
    this->field104 = 0;                                      // +0x104 (0x41*4)
    this->field108 = 0;                                      // +0x108 (0x42*4)
    this->timer = g_systemTimeMs;                            // +0x10C (0x43*4)  _DAT_00d5780c

    this->field110 = 0;                                      // +0x110 (0x44*4)
    this->field114 = 0;                                      // +0x114 (0x45*4)
    this->field118 = 0;                                      // +0x118 (0x46*4)

    // Register interior message strings for challenge notifications
    registerInteriorMessage(&this->msgChallengeCompleted, "iMsgTopDonChallengeCompleted"); // FUN_00408240
    registerInteriorMessage(&this->msgChallengeFailed, "iMsgTopDonChallengeFailed");       // FUN_00408240

    return this;
}