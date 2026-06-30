// FUNC_NAME: ActionNode::init
void __thiscall ActionNode::init(uint32_t value) {
    // +0x10: actionType (4 bytes)
    *(uint32_t*)((uint8_t*)this + 0x10) = 9;   // e.g., ACTION_TYPE_CHASE
    // +0x14: state (1 byte)
    *(uint8_t*)((uint8_t*)this + 0x14) = 2;    // e.g., STATE_IDLE
    // +0x18: targetId (4 bytes)
    *(uint32_t*)((uint8_t*)this + 0x18) = value;
}