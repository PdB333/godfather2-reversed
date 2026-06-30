// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

void __fastcall GodfatherGameManager::GodfatherGameManager(
    this,                      // EDI: pointer to new object (implicit this)
    int param_1,               // ECX: parent object with ref count at +0x10
    byte param_2,              // EDX: some byte flag
    bool param_3,              // on stack: bool for bit2 flag
    int param_4                // on stack: some value stored at +0x64
)
{
    // Initialize vtable and core fields (offsets relative to this)
    this->field_0x04 = 1;                // +0x04: ref count or flag
    this->field_0x08 = 0;                // +0x08: probably some state
    this->field_0x0C = &PTR_LAB_00e39174; // +0x0C: vtable pointer (first)
    // Store global singleton
    g_pGodfatherGameManager = this;       // DAT_01223480

    this->field_0x1C = param_1;          // +0x1C: store parent pointer
    this->vtable = &PTR_FUN_00e39160;    // +0x00: main vtable
    this->field_0x0C = &PTR_LAB_00e39170; // +0x0C: second vtable (overwrite)
    this->field_0x14 = 0;                // +0x14: some pointer
    this->field_0x18 = 0;                // +0x18: some pointer
    this->field_0x20 = 0;                // +0x20: some value
    this->field_0x24 = 0;                // +0x24: some value
    this->byteField_0x28 = param_2;      // +0x28: byte stored
    this->field_0x2C = 0;                // +0x2C: some int

    // Call global engine initialization
    InitEngine(1);                       // FUN_00ab6540(1)

    this->field_0x60 = DAT_00e44940;     // +0x60: constant from data
    this->field_0x40 = 0;                // +0x40: some pointer
    this->field_0x44 = 0;                // +0x44: some pointer
    this->field_0x48 = 0;                // +0x48: some pointer
    this->field_0x54 = 0;                // +0x54: some value
    this->field_0x5C = 0;                // +0x5C: some value
    this->field_0x64 = param_4;          // +0x64: store param_4
    this->field_0x868 = 0;               // +0x868: some int (big offset)
    this->byteField_0x86C = 0;           // +0x86C: byte after int

    // Increment reference count on parent object (at offset 0x10)
    *(int*)((char*)param_1 + 0x10) += 1;

    if (param_3) {
        this->field_0x5C |= 2;            // +0x5C: set bit 1 (0x2)
    }

    // Post-constructor initialization
    InitSubsystem();                     // FUN_0053f930()

    if (g_SomeGlobalFlag1 != 0) {        // DAT_0120679c
        CreateSomeObject();              // FUN_00407e60()
    }
    if (g_SomeGlobalFlag2 != 0) {        // DAT_01206770
        CreateSomeObject();              // FUN_00407e60()
    }

    // Allocate child object of size 24 (0x18)
    int* childObj = (int*)AllocateMemory(0x18); // FUN_009c8e50
    if (childObj != nullptr) {
        InitChildAlloc(childObj);              // FUN_009c8f80()
        int subObj = CreateSubObject();        // FUN_0054a4f0()
        this->field_0x50 = subObj;            // +0x50: store created object
        FinalizeInit();                        // FUN_0053fb10()
    } else {
        this->field_0x50 = 0;
        FinalizeInit();                        // FUN_0053fb10()
    }
}