// FUNC_NAME: PlayerActionableInfo::initDefaults

void PlayerActionableInfo::initDefaults()
{
    // +0x08: active flag (bool)
    *(uint8_t*)(this + 0x8) = 0;

    // +0xa8: some counter or state
    *(uint32_t*)(this + 0xa8) = 0;

    // +0xac: target entity identifier (sentient handle?), -1 = invalid
    *(int32_t*)(this + 0xac) = -1;

    // +0xb0: action type (e.g., attack type, -103 = ACTION_NONE)
    *(int32_t*)(this + 0xb0) = -103;

    // +0xb4: modifier / sub-type
    *(uint32_t*)(this + 0xb4) = 0;

    // +0xbc: timer or cooldown
    *(uint32_t*)(this + 0xbc) = 0;

    // +0xc0: secondary timer
    *(uint32_t*)(this + 0xc0) = 0;

    // +0xc4: extra parameter
    *(uint32_t*)(this + 0xc4) = 0;

    // +0x10c: far offset – possibly a large field like attack path data pointer
    *(uint32_t*)(this + 0x10c) = 0;

    // +0xd0: some flag or result
    *(uint32_t*)(this + 0xd0) = 0;
}