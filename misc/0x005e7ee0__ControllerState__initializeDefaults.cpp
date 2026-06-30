// FUNC_NAME: ControllerState::initializeDefaults
// Address: 0x005e7ee0
// Role: Initializes default values for a controller/input state structure (4 sub-slots)

void ControllerState::initializeDefaults(void)
{
    // External constants (likely default stick/trigger centers or colors)
    const uint32_t kDefaultAxisCenter = DAT_00e2b1a4;    // +0x00e2b1a4
    const uint32_t kDefaultThumbY = DAT_00e2b04c;        // +0x00e2b04c
    const uint32_t kDefaultThumbX = DAT_00e2b050;        // +0x00e2b050

    // Global system pointer for player data allocation
    int* pSystem = DAT_01223510; // vtable of some system

    // Set various fields on the main structure
    this->field8 = kDefaultAxisCenter;               // +0x08
    this->field0 = 0;                                 // +0x00
    this->field1 = 0;                                 // +0x04
    this->field2 = 0;                                 // +0x08
    this->field6 = 0xFFFFFFFF;                        // +0x18 (invalid index)
    this->field7 = 0xFFFFFFFF;                        // +0x1C
    this->field9 = 0;                                 // +0x24
    this->field10 = 0;                                // +0x28
    this->field12 = 0x1000;                           // +0x30 (buffer size?)
    this->field11 = 96000;                            // +0x2C (threshold)
    this->field14 = 0;                                // +0x38

    // Call a virtual function to get some player data pointer
    uint32_t playerData = (**(code **)(*pSystem + 0x5c))();
    this->field15 = playerData;                       // +0x3C

    this->field16 = 0;                                // +0x40
    this->field18 = 0;                                // +0x48
    this->field19 = 0;                                // +0x4C
    this->field20 = 0;                                // +0x50
    this->field21 = 0;                                // +0x54
    this->field22 = 0x32;                             // +0x58 (50, maybe dead zone)
    this->field50 = 0;                                // +0xC8
    this->byte51 = 0;                                 // +0xCC
    this->byte205 = 0;                                // +0xCD
    this->byte206 = 0;                                // +0xCE
    this->byte207 = 0;                                // +0xCF
    this->byte52 = 0;                                 // +0xD0
    this->byte209 = 0;                                // +0xD1
    this->byte210 = 0;                                // +0xD2
    this->byte211 = 0;                                // +0xD3
    this->field179 = 0;                               // +0x2CC
    this->field180 = 0;                               // +0x2D0
    this->field178 = 0;                               // +0x2C8
    this->field176 = 0xFFFFFFFE;                      // +0x2C0
    this->field177 = 0xFFFFFFFE;                      // +0x2C4
    this->field23 = 0;                                // +0x5C
    this->byte24 = 0;                                 // +0x60
    this->byte97 = 0;                                 // +0x61
    this->field46 = 0;                                // +0xB8
    this->field47 = 0;                                // +0xBC
    this->field48 = 0xFFFFFFFF;                       // +0xC0
    this->field25 = 1;                                // +0x64
    this->field26 = 0;                                // +0x68
    this->field27 = 0;                                // +0x6C
    this->byte28 = 0;                                 // +0x70
    this->field38 = 0;                                // +0x98
    this->byte33 = 0;                                 // +0x84
    this->field34 = kDefaultAxisCenter;               // +0x88
    this->byte133 = 0;                                // +0x85
    this->field35 = kDefaultThumbY;                   // +0x8C
    this->field36 = kDefaultThumbX;                   // +0x90
    this->field37 = 0;                                // +0x94
    this->field39 = 0;                                // +0x9C
    this->field40 = 0;                                // +0xA0
    this->field41 = kDefaultAxisCenter;               // +0xA4
    this->field42 = kDefaultAxisCenter;               // +0xA8
    this->field43 = kDefaultAxisCenter;               // +0xAC
    this->field44 = 100;                              // +0xB0
    this->field45 = 0;                                // +0xB4
    this->field49 = 0;                                // +0xC4

    // Initialize 4 sub-slots (e.g., for 4 local players)
    // Each sub-struct is 0x78 bytes (30 ints) starting at offset 0xF4
    uint32_t* pSlot = &this->slots[0]; // pointer to first sub-slot (offset 0x3D * 4 = 0xF4)
    for (int i = 0; i < 4; i++)
    {
        // Offsets relative to sub-slot start
        pSlot[-5] = 0;           // subFieldA
        pSlot[0x17] = 0;         // subFieldB
        pSlot[0x18] = 0;         // subFieldC
        pSlot[-4] = 0;           // subFieldD
        *(uint8_t*)(pSlot - 3) = 0;           // byte subFieldE
        *(uint8_t*)((int)pSlot - 0xB) = 0;    // byte subFieldF
        pSlot[0x13] = 0;         // subFieldG
        pSlot[0x14] = 0;         // subFieldH
        pSlot[0x15] = 0xFFFFFFFF; // invalid index
        pSlot[-2] = 1;           // subFieldI
        pSlot[-1] = 0;           // subFieldJ
        *pSlot = 0;              // subFieldK
        *(uint8_t*)(pSlot + 1) = 0;           // byte subFieldL
        pSlot[0xB] = 0;          // subFieldM
        *(uint8_t*)(pSlot + 6) = 0;           // byte subFieldN
        pSlot[7] = kDefaultAxisCenter;        // subFieldO
        *(uint8_t*)((int)pSlot + 0x19) = 0;   // byte subFieldP
        pSlot[8] = kDefaultThumbY;            // subFieldQ
        pSlot[9] = kDefaultThumbX;            // subFieldR
        pSlot[10] = 0;          // subFieldS
        pSlot[0xC] = 0;         // subFieldT
        pSlot[0xD] = 0;         // subFieldU
        pSlot[0xE] = kDefaultAxisCenter;      // subFieldV
        pSlot[0xF] = kDefaultAxisCenter;      // subFieldW
        pSlot[0x10] = kDefaultAxisCenter;      // subFieldX
        pSlot[0x11] = 100;      // subFieldY
        pSlot[0x12] = 0;        // subFieldZ
        pSlot[0x16] = 0;        // subFieldAA

        // Move to next sub-slot (0x1E * 4 = 0x78 bytes)
        pSlot += 0x1E;
    }
    return;
}