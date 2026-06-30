// FUNC_NAME: SimNpc::constructor

// Constructor for SimNpc (or derived class). Initializes fields, registers with a manager list,
// and sets simulation flags on a target object obtained via parent virtual call.
// Global DAT_00d5ccf8 is some singleton pointer (e.g., SimManager).
// Global DAT_01131070 is another singleton used to retrieve a linked list root.

__thiscall SimNpc * SimNpc::constructor(SimNpc *this, uint param1, uint param2)
{
    int *piVar1;
    uint uVar2;
    uint uVar3;
    char cVar4;
    int iVar5;
    int *piVar6;
    uint retVal; // placeholder for virtual call result pointer

    // Call base class constructor (likely SimObject or Entity)
    SimObject::constructor(/* param1, param2 passed */ (void*)param1, (void*)param2);

    // Set vtable pointer (offset 0x00)
    this->vtable = &PTR_LAB_00d654e8;

    // Zero out fields at offsets 0x50-0x68
    this->field_0x50 = 0;   // +0x50: pointer to target object (set later)
    this->field_0x54 = 0;   // +0x54
    this->field_0x58 = 0;   // +0x58
    this->field_0x5C = 0;   // +0x5C
    this->field_0x60 = 0;   // +0x60
    this->field_0x64 = 0;   // +0x64
    this->field_0x68 = 0;   // +0x68
    this->field_0x6C = DAT_00d5ccf8; // +0x6C: some global pointer

    // Initialize linked list pointers at offsets 0x74 and 0x78
    this->listNext = 0;     // +0x74
    this->listPrev = 0;     // +0x78
    this->field_0x7C = 0;   // +0x7C
    this->field_0x80 = 0;   // +0x80

    // Check if parent pointer at offset 0x48 exists
    if (this->parentPtr != 0) {  // +0x48: pointer to parent (e.g., Sentient or Entity)
        piVar6 = (int*)(this->parentPtr - 0x48); // Get container object (e.g., the owning SimObject)
    } else {
        piVar6 = 0;
    }

    // Temporary output variable
    uint tempOut = 0;

    // Call virtual function #4 on the parent container (vtable index 4 = offset 0x10)
    // Magic constant 0x369ac561 likely a function ID or type code.
    cVar4 = (*(char (**)(uint, uint*))(*piVar6->vtable + 0x10))(0x369ac561, &tempOut);

    // Conditionally set field_0x50 based on result
    if (cVar4 != 0) {
        this->field_0x50 = tempOut;
    } else {
        this->field_0x50 = 0;
    }

    // Determine manager list from singleton
    if ((this->parentPtr == 0) || (this->parentPtr == (void*)0x48)) {
        iVar5 = 0;
    } else {
        iVar5 = FUN_0043b870(DAT_01131070); // Returns pointer to a manager (e.g., SimManager::instance())
    }
    this->field_0x70 = iVar5; // +0x70: store manager pointer

    // Get list head from manager at offset 0x14
    iVar5 = *(int*)(iVar5 + 0x14); // Dereference manager +0x14 -> reference to list head

    // Insert into linked list (uses listNext/listPrev at offsets 0x74/0x78)
    if (this->listNext != iVar5) {
        if (this->listNext != 0) {
            FUN_004daf90(&this->listNext); // Remove from current list (if any)
        }
        this->listNext = iVar5;
        if (iVar5 != 0) {
            this->listPrev = *(int*)(iVar5 + 4); // Set prev pointer
            *(int**)(iVar5 + 4) = &this->listNext; // Update neighbor's prev to point to this node
        }
    }

    // Allocate additional memory of size 0x44 (likely a sub-object)
    void *alloc = FUN_007f63e0(0x44); // returns allocated block

    // Access target object from field_0x50 and modify its flags
    iVar5 = this->field_0x50;
    uVar2 = *(uint*)(iVar5 + 0x5c4); // Read flags at offset +0x5C4
    this->field_0x7C = uVar2;        // Store original flags at +0x7C
    *(uint*)(iVar5 + 0x5c4) = uVar2 | 0xc08; // Set bits: 0x800 + 0x400 + 0x8? (likely simulation/network flags)
    *(uint*)(iVar5 + 0x564) |= 2;    // Set bit 1 at +0x564 (e.g., "isSlave" or "isGhost")

    return this;
}