// FUNC_NAME: BNKStreamManager::BNKStreamManager

// Reconstructed constructor for BNKStreamManager (EA EARS engine audio bank stream manager)
// Address: 0x008cfb70
// Called from 0x008d06a0

BNKStreamManager::BNKStreamManager(undefined4 param_2)
{
    // Call base class initializer (likely sets up internal reference or parent)
    // FUN_0046c590
    BaseClass::init(param_2);

    // Set vtable pointer for this class
    this->vtable = &PTR_FUN_00d7ce50;

    // Initialize sub-object at offset +0x3C (param_1[0xf]) with its own vtable
    // This subobject handles stream read/write operations
    this->streamSubObject.vtable = &PTR_LAB_00d7ce40;

    // Initialize sub-object at offset +0x48 (param_1[0x12]) with its own vtable
    // Possibly a secondary stream or decoder
    this->decoderSubObject.vtable = &PTR_LAB_00d7ce3c;

    // Zero out internal fields
    this->field_0x50 = 0;          // param_1[0x14]
    this->flags_0x54 = 0;         // *(undefined2*)(param_1 + 0x15) – 2 bytes
    this->counter_0x56 = 0;       // *(undefined2*)((int)param_1 + 0x56) – 2 bytes
    this->field_0x58 = 0;         // param_1[0x16]
    this->field_0x5C = 0;         // param_1[0x17]
    this->field_0x60 = 0;         // param_1[0x18]

    // Base class constructor (likely initializes reference counting or virtual dispatch)
    // FUN_00446680
    BaseClass::constructor(this);

    // Load optional bank data from global pointers (if available)
    // Both calls load into the stream sub-object at offset +0x3C
    // Size 0x8000 (32KB) matches typical bank file size
    if (gBankData1 != 0) {
        // FUN_00408900 – loads raw data into stream buffer
        this->streamSubObject.loadData(&gBankData1, 0x8000);
    }
    if (gBankData2 != 0) {
        // Second bank data (e.g., streaming bank or additional sound effects)
        this->streamSubObject.loadData(&gBankData2, 0x8000);
    }

    return this;
}