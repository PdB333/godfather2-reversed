// FUN_008febe0: ControllerManager::setControllerEnabled
void __thiscall ControllerManager::setControllerEnabled(bool enable)
{
    ushort flags = *(ushort *)(this + 0xd0); // +0xD0: controller flags
    if (enable) {
        flags |= 0x20;  // bit 5 = enabled/active
    } else {
        flags &= ~0x20;
    }
    *(ushort *)(this + 0xd0) = flags;

    // Check if active controller index changed
    int activeIdx = FUN_008fe480(); // Likely getActiveControllerIndex()
    if (activeIdx != *(int *)(this + 0xdc)) { // +0xDC: last known active controller index
        FUN_008fddc0(); // reset current controller state
        FUN_008fe5e0(activeIdx); // set new active controller
    }
}