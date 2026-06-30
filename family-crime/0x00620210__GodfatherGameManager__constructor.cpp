// FUNC_NAME: GodfatherGameManager::constructor

void GodfatherGameManager::constructor(void* parent)
{
    // Set vtable pointer at +0x00
    *(int*)this = (int)&PTR_FUN_00e41490;

    // Base class constructor (likely Framework::Object)
    FUN_00c9ec50();

    // Initialize with flags (0,1)
    FUN_00ab5fb0(0, 1);

    // Zero out early fields
    this->field_0x84 = 0; // +0x84
    this->field_0x88 = 0; // +0x88
    this->field_0x90 = 0; // +0x90
    this->field_0x94 = 0; // +0x94

    // Store parent pointer at +0x08
    this->m_pParent = parent;

    // Additional initialization
    FUN_00c9eac0();

    // If parent's field at +0x28 is zero, run extra init
    if (*(int*)(this->m_pParent + 0x28) == 0) {
        FUN_00ca3ee0();
    }

    // Create and store sub-objects
    int sub1 = FUN_00ca8180();
    FUN_00c9ceb0(sub1);

    if (*(int*)(this->m_pParent + 0x28) == 0) {
        FUN_00ca3ee0();
    }

    int sub2 = FUN_00caa1c0();
    FUN_00c9ceb0(sub2);

    int sub3 = FUN_00cd2a00();
    FUN_00ca3e90(sub3);
    FUN_00c96910(sub3);

    // Final base init
    FUN_00c9eae0();

    // Copy singleton reference into member at +0x38
    this->m_pGlobalRef = g_pGodfatherGameManager; // DAT_00e2b1a4

    // Zero remaining fields
    this->field_0x24 = 0;   // +0x24 (byte)
    this->field_0x80 = 0;   // +0x80 (byte)
    this->field_0x04 = 0;   // +0x04
    this->field_0x40 = 0;   // +0x40
    this->field_0x44 = 0;   // +0x44
    this->field_0x48 = 0;   // +0x48
    this->field_0x4c = 0;   // +0x4c
    this->field_0x9c = 0;   // +0x9c
    this->field_0xa0 = 0;   // +0xa0
    this->field_0xa4 = 0;   // +0xa4
    this->field_0xa8 = 0;   // +0xa8
    this->field_0xac = 0;   // +0xac
    this->field_0xb0 = 0;   // +0xb0
    this->field_0xb4 = 0;   // +0xb4
    this->field_0xb8 = 0;   // +0xb8
    this->field_0xbc = 0;   // +0xbc
    this->field_0xc0 = 0;   // +0xc0 (byte)
}