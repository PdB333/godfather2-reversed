// FUNC_NAME: Entity::shutdown
void __thiscall Entity::shutdown(Entity* this) {
    // Check if the "initialized" flag (bit 1, value 0x02) is set at offset +0x40
    if ((*(byte *)((int)this + 0x40) & 2) != 0) {
        // Call internal cleanup/sub-shutdown
        FUN_004b66a0();
        // Clear the flag by masking with 0xFD (11111101b)
        *(byte *)((int)this + 0x40) = *(byte *)((int)this + 0x40) & 0xfd;
    }
}