// FUNC_NAME: PlayerSM::PlayerSM
undefined4* __thiscall PlayerSM::PlayerSM(undefined4* this, undefined4 param2, undefined4 param3)
{
    int* nodePtr;
    char flagCheck;
    int newNode;

    // Call base class constructor
    BaseClass::BaseClass(param2, param3);

    // Set up vtable pointers for multiple inheritance
    // Primary vtable at offset 0
    *this = &PTR_LAB_00d68390;
    // Secondary vtable at offset 0x70 (this[0x1c])
    this[0x1c] = &PTR_FUN_00e2f19c;
    // ++0x74: some initial state
    this[0x1d] = 1;
    // ++0x78: counter/flag
    this[0x1e] = 0;
    // ++0x80: pointer
    this[0x20] = 0;
    // ++0x7c: secondary vtable pointer (overwrites later)
    this[0x1f] = &PTR_LAB_00d58278;
    // Primary vtable again? Possibly setup
    *this = &PTR_LAB_00d68390;
    // ++0x70: another vtable pointer
    this[0x1c] = &PTR_LAB_00d68380;
    // ++0x7c: function pointer for dynamic dispatch
    this[0x1f] = &PTR_FUN_00d6836c;

    // Node pointer at offset 0x88 (this[0x22])
    nodePtr = (int*)(this + 0x22);
    *nodePtr = 0;
    // ++0x8c: next pointer in linked list
    this[0x23] = 0;
    // ++0x90: state flags
    this[0x24] = 0;
    // ++0xac: some other state
    this[0x2b] = 0;

    // Get a new node from manager (e.g., render/update list)
    newNode = FUN_007ff880();
    if (newNode == 0) {
        newNode = 0;
    } else {
        newNode += 0x48; // advance to internal structure
    }

    // If the stored node pointer differs from the new node, perform list update
    if (*nodePtr != newNode) {
        if (*nodePtr != 0) {
            // Remove old node from list
            FUN_004daf90(nodePtr);
        }
        *nodePtr = newNode;
        if (newNode != 0) {
            // Insert new node: set its next pointer to point back to this object's node field
            this[0x23] = *(undefined4*)(newNode + 4);
            *(int**)(newNode + 4) = nodePtr;
        }
    }

    // Check a flag at offset 0x5c (this[0x17])
    flagCheck = FUN_00543050(this[0x17]);
    if (flagCheck != '\0') {
        // Set bit 4 in state flags (++0x90)
        this[0x24] |= 0x10;
    }

    // If node is present and not a specific type (0x48), perform additional setup
    if ((*nodePtr != 0) && (*nodePtr != 0x48)) {
        if ((*nodePtr != 0) && (*nodePtr != 0x48)) {
            FUN_0043b870(DAT_0112ded0); // Notify global manager
        }
        // Set flags on a secondary vtable area (offset 0x7c)
        FUN_009aefd0(this + 0x1f, 0x8000);
    }

    // Clear internal state block (6 ints) from offset 0x94 to 0xac
    this[0x25] = 0; // ++0x94
    this[0x26] = 0; // ++0x98
    this[0x27] = 0; // ++0x9c
    this[0x28] = 0; // ++0xa0
    this[0x29] = 0; // ++0xa4
    this[0x2a] = 0; // ++0xa8

    return this;
}