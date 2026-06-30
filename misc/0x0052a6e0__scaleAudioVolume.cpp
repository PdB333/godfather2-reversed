// FUNC_NAME: scaleAudioVolume
// Function address: 0x0052a6e0
// Role: Applies a master volume ratio to four channel volumes (likely left, right, surround, center).
// Global variables:
//   g_masterVolumeTarget   (0x00e2b1a4) - current target master volume
//   g_masterVolumeReference (0x01125240) - base reference volume
//   g_channelVolume[0..3]   (0x01125230..0x0112523c) - per-channel volumes

void scaleAudioVolume(void) {
    float volumeRatio = g_masterVolumeTarget / g_masterVolumeReference;
    
    // Scale all four channel volumes by the ratio
    g_channelVolume[0] *= volumeRatio; // +0x00 (left)
    g_channelVolume[1] *= volumeRatio; // +0x04 (right)
    g_channelVolume[2] *= volumeRatio; // +0x08 (surround)
    g_channelVolume[3] *= volumeRatio; // +0x0C (center)
}