// FUNC_NAME: CameraManager::setCameraTarget
class CameraManager {
public:
    // Offsets:
    // +0x1038: m_pTransitionPath1
    // +0x1040: m_pTransitionPath2
    // +0x1044: m_pTransitionData
    // +0x104c: m_pTransitionData2
    // +0xf28: m_flags (bit 0x20000000 = transition active)

    int __thiscall setCameraTarget(void* pCameraController, void* pTransitionInfo, void* pNewTarget, void* pExtraParam) {
        // Release previous transition data
        if (m_pTransitionData != nullptr) {
            releaseObject(m_pTransitionData);
            m_pTransitionData = nullptr;
        }
        m_pTransitionData2 = nullptr;
        if (m_pTransitionPath1 != nullptr) {
            releaseObject(m_pTransitionPath1);
            m_pTransitionPath1 = nullptr;
        }
        m_pTransitionPath2 = nullptr;

        // Validate all parameters are non-null
        if (pCameraController && pNewTarget && pTransitionInfo && pExtraParam) {
            if (pCameraController != pNewTarget) {
                // New target differs -> setup a transition
                createCameraTransition(pNewTarget, pExtraParam);  // FUN_005f5c20
                int buffer[3];
                int path = getTransitionPath(pTransitionInfo, buffer); // FUN_005f5f20
                setCameraPath(pCameraController, path); // FUN_00860750
                m_flags |= 0x20000000; // Set transition active flag
                if (buffer[0] != 0) {
                    releaseObject(buffer); // likely cleanup of local buffer
                }
                return 1;
            } else {
                // Same target -> direct cut
                int directValue = getDirectTarget(pTransitionInfo, pExtraParam); // FUN_005f5ec0
                setCameraDirectTarget(pCameraController, directValue); // FUN_008606d0
                m_flags &= ~0x20000000; // Clear transition active flag
                return 1;
            }
        }
        return 0;
    }

private:
    void releaseObject(void* ptr);      // FUN_004daf90
    void createCameraTransition(void* target, void* extra); // FUN_005f5c20
    int getTransitionPath(void* info, int* buffer); // FUN_005f5f20
    void setCameraPath(void* controller, int path); // FUN_00860750
    int getDirectTarget(void* info, void* extra); // FUN_005f5ec0
    void setCameraDirectTarget(void* controller, int value); // FUN_008606d0

    // Fields (unspecified size)
    void* m_pTransitionPath1;   // +0x1038
    void* m_pTransitionPath2;   // +0x1040
    void* m_pTransitionData;    // +0x1044
    void* m_pTransitionData2;   // +0x104c
    uint32_t m_flags;           // +0xf28
};