// FUN_NAME: GameObject::checkPendingDestroy
// Address: 0x004b7010
// Role: Checks a flag at +0x28 bit 0 (1) and if set, calls destruction clean-up routine (FUN_004b6c20).
// Called from: 0x008cc3d0 (likely main update loop or destruction manager)

void __thiscall GameObject::checkPendingDestroy(void)
{
    // +0x28: flags/status byte. Bit 0 (0x01) indicates pending destruction.
    if ((*(byte *)(this + 0x28) & 1) != 0) {
        // FUN_004b6c20: presumed destroy/cleanup handler
        this->performDestroyCleanup();  // placeholder name for FUN_004b6c20
    }
    return;
}