// FUNC_NAME: proximityCheckAndTrigger
void proximityCheckAndTrigger(float* triggerPosition)
{
    // Get pointer to local player object (position at offsets +0x30, +0x34, +0x38)
    int* playerObj = reinterpret_cast<int*>(FUN_00471610());
    float dx = *reinterpret_cast<float*>(playerObj + 0x30 / sizeof(float)) - triggerPosition[0];
    float dy = *reinterpret_cast<float*>(playerObj + 0x34 / sizeof(float)) - triggerPosition[1];
    float dz = *reinterpret_cast<float*>(playerObj + 0x38 / sizeof(float)) - triggerPosition[2];
    float distSq = dx*dx + dy*dy + dz*dz;
    
    // Global distance thresholds (min and max squared distance)
    // DAT_00d62bd4 = gMinDistSq, DAT_00d62bd0 = gMaxDistSq
    if (DAT_00d62bd4 < distSq && distSq < DAT_00d62bd0) {
        int playbackHandle = FUN_006fbc40(0, 0); // e.g., AudioManager::playSoundEffect(0, 0)
        FUN_007f96a0(0, 0x3d, playbackHandle, 0); // e.g., NetworkManager::sendEvent(playerIndex, 0x3d, playbackHandle, 0)
        FUN_006fbc70(); // e.g., AudioManager::stopSoundEffect(playbackHandle)
    }
}