// FUN_NAME: CameraManager::SetOrientation
// Function address: 0x005399a0
// Role: Stores a 4-float orientation (likely a quaternion) into a temporary buffer,
// then conditionally applies it to the current camera mode if the camera manager is active.
// The camera manager is expected to be at a fixed global address (s_defaultManager).
// The current mode is identified by a pointer (m_pCurrentMode), compared against
// two mode objects: chase mode and free-look mode.

// Includes for clarity (not actual game headers)
// #include <cstdint>

class CameraMode; // Forward declaration

class CameraManager {
public:
    // Static data (based on global addresses)
    static CameraManager* s_pCurrentManager;   // 0x012058e8 (points to s_defaultManager)
    static CameraManager s_defaultManager;     // 0x0121b740 (the actual instance)
    static float s_tempOrientation[4];         // 0x0121b800 (temporary storage)

    // Offsets relative to s_defaultManager (0x0121b740):
    CameraMode* m_pCurrentMode;     // +0x14 (0x0121b754) - pointer to currently active camera mode
    // +0x258 (0x0121b998) - unknown data (used as second arg in ApplyOrientation)
    // +0x2A0 (0x0121b9e0) - unknown data (used as second arg for free-look)
    CameraMode* m_chaseMode;        // +0x470 (0x0121bbb0) - pointer to chase camera mode object
    CameraMode* m_freeLookMode;     // +0x478 (0x0121bbb8) - pointer to free-look camera mode object

    // Static method that sets the temporary orientation and conditionally applies it.
    // orientation: pointer to 4 floats (quaternion)
    static void SetOrientation(const float orientation[4]);
    
    // Static method called to apply the orientation to a specific mode.
    // First arg: camera mode object; second: associated data; third: orientation array.
    static void ApplyOrientation(CameraMode* mode, void* modeData, const float orientation[4]); // 0x0060add0
};

// Implementation
void CameraManager::SetOrientation(const float orientation[4]) {
    // Store the incoming orientation into the temporary global buffer.
    s_tempOrientation[0] = orientation[0];
    s_tempOrientation[1] = orientation[1];
    s_tempOrientation[2] = orientation[2];
    s_tempOrientation[3] = orientation[3];

    // Check if the current camera manager pointer is the default instance.
    if (s_pCurrentManager == &s_defaultManager) {
        // If the current mode is the chase camera mode ...
        if (s_pCurrentManager->m_pCurrentMode == s_pCurrentManager->m_chaseMode) {
            ApplyOrientation(s_pCurrentManager->m_chaseMode,
                             (void*)0x0121b998,   // hardcoded offset reference: chase mode data
                             s_tempOrientation);
        }
        // If the current mode is the free-look camera mode ...
        if (s_pCurrentManager->m_pCurrentMode == s_pCurrentManager->m_freeLookMode) {
            ApplyOrientation(s_pCurrentManager->m_freeLookMode,
                             (void*)0x0121b9e0,   // hardcoded offset reference: free-look mode data
                             s_tempOrientation);
        }
    }
    // Note: The second if condition includes a redundant outer check in the decompiled code;
    // it is preserved here as-is to match the original logic.
}