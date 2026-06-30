// FUNC_NAME: AIAgent::InitializeDefaults
void AIAgent::InitializeDefaults()
{
    // +0x8: some boolean flag (set to 0)
    *(uint8_t*)(this + 0x8) = 0;

    // +0xA8: field (int) initialized to 0
    *(int32_t*)(this + 0xA8) = 0;

    // +0xAC: field initialized to -1 (0xFFFFFFFF)
    *(int32_t*)(this + 0xAC) = -1;

    // +0xB0: field initialized to -103 (0xFFFFFF99)
    *(int32_t*)(this + 0xB0) = -103;

    // +0xB4: field initialized to 0
    *(int32_t*)(this + 0xB4) = 0;

    // +0xBC: field initialized to 0
    *(int32_t*)(this + 0xBC) = 0;

    // +0xC0: field initialized to 0
    *(int32_t*)(this + 0xC0) = 0;

    // +0xC4: field initialized to 0
    *(int32_t*)(this + 0xC4) = 0;

    // +0x10C: field initialized to 0
    *(int32_t*)(this + 0x10C) = 0;

    // +0xD0: field initialized to 0
    *(int32_t*)(this + 0xD0) = 0;
}