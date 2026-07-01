// FUNC_NAME: GameObject::commonInit
// Function address: 0x008b3ad0
// Role: Initialize object state flags and process associated asset handle.
// This is likely called during initialization to set the "initialized" bit and clear the "active" bit,
// then triggers common init and handles the asset/data pointer at offset 0x94.

void __thiscall GameObject::commonInit()
{
    // +0x188: m_flags (uint32_t)
    // Set bit 4 (0x10) - typically indicates "initialized" or "ready"
    *(uint32_t *)(this + 0x188) = *(uint32_t *)(this + 0x188) | 0x10;
    // Clear bit 0 (0x01) - typically indicates "active" or "enabled"
    *(uint32_t *)(this + 0x188) = *(uint32_t *)(this + 0x188) & 0xfffffffe;

    // Global common initialization function (could be a static singleton)
    FUN_008ae0d0();

    // Process the data handle stored at +0x94 (e.g., asset ID, model pointer)
    // This is passed as an integer (could be a handle or pointer)
    FUN_0094db00(*(int32_t *)(this + 0x94));
}