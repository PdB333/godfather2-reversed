// FUNC_NAME: TriggerManager::TriggerManager

// Constructor for TriggerManager class.
// Initializes internal state, sets vtable pointers, zeros data structures, and registers trigger message types.
// Offset comments indicate byte offsets from 'this'.

void* __thiscall TriggerManager::TriggerManager(TriggerManager* this, void* param_2)
{
    // Initialize memory block of size 0x4000 bytes at address param_2
    // param_2 likely points to a preallocated buffer for this object's dynamic data
    Mem::initBlock(param_2, 0x4000);  // FUN_0046e6b0

    // Set primary vtable pointer
    this->vtable = (int*)&TriggerManager_vtable;  // +0x00: PTR_FUN_00e35f80

    // Set interface vtable pointers (multiple inheritance / interface vtables)
    this->interfaceVtable1 = (int*)&TriggerManager_interface1; // +0x3C: PTR_LAB_00e360dc
    this->interfaceVtable2 = (int*)&TriggerManager_interface2; // +0x48: PTR_LAB_00e360ec
    this->interfaceVtable3 = (int*)&TriggerManager_interface3; // +0x50: PTR_LAB_00e360f0
    this->interfaceVtable4 = (int*)&TriggerManager_interface4; // +0x54: PTR_LAB_00e360f8
    this->interfaceVtable5 = (int*)&TriggerManager_interface5; // +0x58: PTR_LAB_00e36158

    // Zero out various members
    this->field_0x18C = 0;     // +0x18C (param_1[99])
    this->field_0x19C = 0;     // +0x19C (param_1[0x67])
    this->field_0x1AC = 0;     // +0x1AC (param_1[0x6b])

    // Store global value (DAT_00e2b1a4) into field at +0x1BC
    this->someGlobal = DAT_00e2b1a4; // +0x1BC (param_1[0x6f])

    // Zero next four DWORD fields
    this->field_0x1C0 = 0;     // +0x1C0
    this->field_0x1C4 = 0;     // +0x1C4
    this->field_0x1C8 = 0;     // +0x1C8
    this->field_0x1CC = 0;     // +0x1CC

    // Initialize trigger zone data (5 entries, each containing two shorts and one int)
    // Pattern for each entry: two 16-bit fields followed by one 32-bit field

    // Entry 0
    *(short*)((int)this + 0x1D0) = 0; // short at +0x1D0
    *(short*)((int)this + 0x1D2) = 0; // short at +0x1D2
    ((int*)this)[0x75] = 0;           // int at +0x1D4

    // Entry 1
    *(short*)((int)this + 0x1D8) = 0; // short at +0x1D8
    *(short*)((int)this + 0x1DA) = 0; // short at +0x1DA
    ((int*)this)[0x77] = 0;           // int at +0x1DC

    // Entry 2
    *(short*)((int)this + 0x1E0) = 0; // short at +0x1E0
    *(short*)((int)this + 0x1E2) = 0; // short at +0x1E2
    ((int*)this)[0x79] = 0;           // int at +0x1E4

    // Entry 3
    *(short*)((int)this + 0x1E8) = 0; // short at +0x1E8
    *(short*)((int)this + 0x1EA) = 0; // short at +0x1EA
    ((int*)this)[0x7B] = 0;           // int at +0x1EC

    // Entry 4
    *(short*)((int)this + 0x1F0) = 0; // short at +0x1F0
    *(short*)((int)this + 0x1F2) = 0; // short at +0x1F2
    ((int*)this)[0x7D] = 0;           // int at +0x1F4

    // Remaining fields after the 5 entries
    ((int*)this)[0x7E] = 0xFFFFFFFF;  // +0x1F8 - set to -1
    ((int*)this)[0x7F] = 0;           // +0x1FC
    ((int*)this)[0x80] = 0;           // +0x200
    ((int*)this)[0x81] = 0;           // +0x204
    ((int*)this)[0x82] = 0;           // +0x208
    ((int*)this)[0x83] = 0;           // +0x20C

    // Register two trigger message types in the global message system
    // FUN_004dafd0 inserts string into hash table, returns an ID
    // FUN_00408260 registers that ID with a global message list
    int msgId = StringTable::insert("iMsgTrigger");          // FUN_004dafd0
    MessageSystem::registerMessage(&g_iMsgTrigger, msgId);   // FUN_00408260(&DAT_012180f8, msgId)

    msgId = StringTable::insert("iMsgReverseTrigger");       // FUN_004dafd0
    MessageSystem::registerMessage(&g_iMsgReverseTrigger, msgId); // FUN_00408260(&DAT_012180f0, msgId)

    return this;
}