// FUNC_NAME: SimObject::constructor
// Function address: 0x005f6300
// __thiscall Constructor for a base engine object. Calls an initialization routine and conditionally destroys based on a placement flag.
void* __thiscall SimObject::constructor(void* this, byte placementFlag) {
    this->initialize();                  // +0x0: Base initialization (calls FUN_005f8bc0)
    if (placementFlag & 1) {             // Bit 0: if set, run cleanup/destructor (calls FUN_009c8eb0)
        this->destroy();                 // +0x0: Destructor/cleanup
    }
    return this;                         // Return constructed this pointer
}