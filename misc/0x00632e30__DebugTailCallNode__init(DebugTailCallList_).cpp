// FUNC_NAME: DebugTailCallNode::init(DebugTailCallList*)
void __thiscall DebugTailCallNode::init(DebugTailCallList* list) {
    // Initialize vtable-type pointers to static debug tables
    this->vtable1 = &DAT_00e2f044;      // +0x04
    this->vtable2 = &DAT_00e2f044;      // +0x08
    this->blockStart = &DAT_00e41ec0;   // +0x0c
    this->label = "=(tail call)";       // +0x10
    this->prevBlock = -1;               // +0x14
    this->nextBlock = -1;               // +0x1c
    this->pad = 0;                      // +0x18

    // Copy debug string to internal buffer at +0x20
    setDebugString(this->debugBuffer, "=(tail call)"); // +0x20

    // Clear the next pointer of the list head (or some linked list anchor)
    *reinterpret_cast<int**>(list + 8) = 0; // list->headNode = nullptr
}