// FUNC_NAME: FrameManager::updateFrameState
void FrameManager::updateFrameState(void)
{
    // Copy global frame time vector (x, y, z) to working buffer
    // Source: 0x011280f0, 0x011280f4, 0x011280f8 (likely frame delta, absolute time, etc.)
    // Destination: 0x01205380, 0x01205384, 0x01205388 (working copy for current frame)
    *(float*)0x01205380 = *(float*)0x011280f0;  // +0x00 copy x
    *(float*)0x01205384 = *(float*)0x011280f4;  // +0x04 copy y
    *(float*)0x01205388 = *(float*)0x011280f8;  // +0x08 copy z

    // Continue frame update processing
    FUN_0041e7e0(); // FrameManager::processFrameData (subsequent frame logic)
}