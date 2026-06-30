// FUNC_NAME: Manager::constructor
undefined4 * __thiscall Manager::constructor(undefined4 *this, int param2) {
    int *nodePtr;
    undefined4 tempVar;
    undefined4 zeroVal;
    
    tempVar = DAT_00d5e288;          // global value
    this[1] = 0;                     // +0x04: some flag
    *(undefined1 *)(this + 2) = 0;   // +0x08: byte field
    this[3] = 0xff;                  // +0x0C: mask/limit
    *this = &PTR_FUN_00d5f5b0;       // vtable
    this[4] = 0;                     // +0x10: head pointer (list)
    this[5] = 0;                     // +0x14: tail or previous next pointer
    this[8] = tempVar;               // +0x20
    nodePtr = this + 4;              // pointer to head field
    this[9] = _DAT_00d5780c;         // +0x24
    tempVar = _DAT_00d5cf70;         // +0x28
    this[10] = _DAT_00d5cf70;        // +0x28
    this[0xb] = tempVar;             // +0x2C (same as above)
    this[0xf] = 0;                   // +0x3C
    this[0xe] = 0;                   // +0x38
    this[0xd] = 0;                   // +0x34
    this[0xc] = 0;                   // +0x30
    this[0x10] = 0;                  // +0x40
    
    if (param2 == 0) {
        param2 = 0;
    } else {
        param2 = param2 + 0x48;       // offset to embedded node
    }
    
    // Update the intrusive list head
    if (*nodePtr != param2) {
        if (*nodePtr != 0) {
            FUN_004daf90(nodePtr);     // free old head
        }
        *nodePtr = param2;
        if (param2 != 0) {
            this[5] = *(undefined4 *)(param2 + 4); // save original next
            *(int **)(param2 + 4) = nodePtr; // node points back to head pointer
        }
    }
    
    zeroVal = 0;
    FUN_006da2b0();                   // additional init
    tempVar = _DAT_00d5780c;
    this[0x14] = this[9];            // +0x50 copy from +0x24
    *(undefined1 *)(this + 2) = 0;   // +0x08 reset byte
    this[0x15] = tempVar;            // +0x54
    this[0x16] = zeroVal;            // +0x58
    return this;
}