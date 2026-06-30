// FUNC_NAME: GameManager::runFrame
uint GameManager::runFrame(void)
{
    uint result;

    // Call virtual preFrameUpdate (vtable +0xb8)
    (*(void (__thiscall **)(void))(*(uint *)DAT_01223510 + 0xb8))();

    // Call virtual frameUpdate (vtable +0xc4)
    (*(void (__thiscall **)(void))(*(uint *)DAT_01223510 + 0xc4))();

    // Update physics subsystem (e.g., Havok world step)
    FUN_005e1ee0();

    // Update entity manager with input controller state (DAT_012234bc = controller manager pointer)
    FUN_005e4d30(DAT_012234bc);

    // Update input processing (keyboard/mouse, XInput)
    FUN_005e43d0();

    // Render frame, return status (DAT_01223508 = renderer singleton)
    result = FUN_005dc2f0(DAT_01223508);

    // Mask low byte (except bit 0) to keep error flag
    return result & 0xffffff01;
}