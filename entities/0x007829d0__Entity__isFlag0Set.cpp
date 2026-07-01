// FUNC_NAME: Entity::isFlag0Set
// Function at 0x007829d0: checks bit 0 of a flags field at offset 0x74
// Returns non-zero if bit0 is set, zero otherwise.
// +0x74 flags (uint32) – bit0 is some boolean property

uint __thiscall Entity::isFlag0Set() {
    return *(uint *)((char *)this + 0x74) & 1;
}