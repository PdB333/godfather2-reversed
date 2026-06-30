// FUNC_NAME: GameManager::update
void __thiscall GameManager::update(void)
{
    // 0x00490b20: Pre-update (input handling, physics, etc.)
    inputUpdate();

    // Check if sub-component (e.g., active effect or controller) exists at offset +0x1c0
    if (*(uint *)((int)this + 0x1c0) != 0)
    {
        // Update sub-component with its ID (+0x14), pointer (+0x1c0), and data buffer (+0x1d0)
        processSubComponent(
            *(uint *)((int)this + 0x14),        // Sub-component identifier
            *(uint *)((int)this + 0x1c0),        // Sub-component pointer
            (void *)((int)this + 0x1d0)           // Sub-component data buffer
        );
    }

    // 0x00492190: Post-update (rendering, network sync, etc.)
    renderUpdate();
}

void inputUpdate(void);
void processSubComponent(uint id, uint ptr, void *buffer);
void renderUpdate(void);