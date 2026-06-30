// FUNC_NAME: ChaseCamera::updateTarget
// Address: 0x006d76c0
// Role: Update the chase camera's target, linked-list attachment, and orientation flip logic.
// This method is called when the camera target changes or during update.
// It uses an intrusive linked list to attach this camera controller to a target entity (e.g., vehicle).
// The orientation flip logic ensures the camera remains behind the player (yaw flip).

#include <math.h>

// Forward declarations of helper functions (reconstructed from callees)
void releaseReference(void* ptr);                 // FUN_004daf90
void getPositionByID(int id, float out[3]);       // FUN_00424fb0
void* getCameraTransform();                       // FUN_00471610 (returns a pointer to a transform matrix)

// Global constants (initialized elsewhere)
extern float DAT_00d5f37c;  // default FOV
extern float DAT_00d5f540;  // default distance
extern float DAT_00d5f53c;  // default range X
extern float DAT_00d5d740;  // default range Y? from globals
extern float DAT_00d5d934;  // default range Z?
extern float DAT_00d5f538;  // default pitch min
extern float DAT_00d5ccf8;  // default pitch max
extern float DAT_00d5f520;  // spring constant
extern float DAT_00d5ef88;  // damping constant
extern float DAT_00d5f534;  // threshold for camera flip detection
extern float DAT_00e44564;  // flip constant (likely PI or 2*PI)

// Intrusive list node structure (embedded in target entities at offset 0x48)
struct ListNode {
    ListNode* prev;  // points to the pointer that points to this node (or previous node's next)
};

// ChaseCamera class
class ChaseCamera {
public:
    // Fields (offsets relative to this)
    char unknown1[0x28];
    void* m_pPrevTarget;              // +0x28: previously attached target (released on new attach)
    ListNode* m_pTargetNode;          // +0x30: pointer to the attached node (points to target's node)
    ListNode** m_pTargetNodePrevPtr;  // +0x34: address of the pointer that points to m_pTargetNode (used as node->prev)
    float m_fov;                      // +0x38
    float m_yawAngle;                 // +0x3c (flipped under condition)
    float m_defaultDistance;          // +0x44
    float m_defaultPitchMin;          // +0x4c
    float m_defaultPitchMax;          // +0x50
    float m_defaultRangeX;            // +0x54
    float m_defaultRangeY;            // +0x58
    float m_defaultRangeZ;            // +0x5c
    char unknown2[0x18];              // gap until 0x74
    float m_springConstant;           // +0x74
    float m_dampingConstant;          // +0x78
    float m_offsetX;                  // +0x7c
    float m_offsetY;                  // +0x80
    float m_offsetZ;                  // +0x84
    unsigned int m_orientationData;   // +0x88 (param_4, probably orientation override)

    // Method
    void updateTarget(void* pTarget, bool bInit, unsigned int orientationData);
};

void ChaseCamera::updateTarget(void* pTarget, bool bInit, unsigned int orientationData) {
    // If this is an initialization request, set default camera parameters
    if (bInit) {
        m_fov = DAT_00d5f37c;
        m_defaultDistance = DAT_00d5f540;
        m_defaultRangeX = DAT_00d5f53c;
        m_defaultRangeY = DAT_00d5d740;
        m_defaultRangeZ = DAT_00d5d934;
        m_defaultPitchMin = DAT_00d5f538;
        m_defaultPitchMax = DAT_00d5ccf8;
        m_springConstant = DAT_00d5f520;
        m_dampingConstant = DAT_00d5ef88;
        m_offsetX = 0.0f;
        m_offsetY = 0.0f;
        m_offsetZ = 0.0f;
    }

    // Release previous target if any
    if (m_pPrevTarget != nullptr) {
        releaseReference(m_pPrevTarget);
        m_pPrevTarget = nullptr;
    }

    // Attach to new target via intrusive linked list
    // The target is expected to have a ListNode at offset 0x48
    ListNode* newTargetNode = nullptr;
    if (pTarget != nullptr) {
        newTargetNode = reinterpret_cast<ListNode*>(reinterpret_cast<char*>(pTarget) + 0x48);
    }

    if (m_pTargetNode != newTargetNode) {
        if (m_pTargetNode != nullptr) {
            releaseReference(m_pTargetNode);
        }
        m_pTargetNode = newTargetNode;
        if (newTargetNode != nullptr) {
            // Update the node's prev pointer to point to where we store it (for list maintenance)
            newTargetNode->prev = reinterpret_cast<ListNode*>(&m_pTargetNode);
        }
    }

    // Store orientation data (probably initial yaw/pitch offset)
    m_orientationData = orientationData;

    // If no specific target (pTarget == null), perform auto-orientation check
    if (pTarget == nullptr) {
        // Get the target point (e.g., player position) using some ID (0x2494)
        float targetPos[3];
        getPositionByID(0x2494, targetPos);  // returns 12 bytes: [x, y, z]
        float local_1c_x = targetPos[0];
        float local_1c_y = targetPos[1];
        float local_14 = targetPos[2];

        // Get the camera's transform (e.g., player vehicle or camera mount)
        float* transform = reinterpret_cast<float*>(getCameraTransform());

        // Compute vector from transform origin to target point
        float dx = transform[0x30 / 4] - local_1c_x;  // transform[12] (x position)
        float dy = transform[0x34 / 4] - local_1c_y;  // transform[13] (y position)
        float dz = transform[0x38 / 4] - local_14;    // transform[14] (z position)

        // Re-fetch transform pointer multiple times (same object)
        float* transform2 = reinterpret_cast<float*>(getCameraTransform());
        float* transform3 = reinterpret_cast<float*>(getCameraTransform());

        // Dot product with first row of transform (likely forward/right vector)
        // Accessing offsets: +0x00, +0x04, +0x08 (first row columns)
        float dot1 = transform[0x04 / 4] * dy + transform2[0x00 / 4] * dx + transform3[0x08 / 4] * dz;
        bool bBehind = (dot1 < 0.0f);

        // Get transform again for second dot product
        float* transform4 = reinterpret_cast<float*>(getCameraTransform());
        float* transform5 = reinterpret_cast<float*>(getCameraTransform());
        float* transform6 = reinterpret_cast<float*>(getCameraTransform());
        // Dot product with third row? Offsets: +0x20, +0x24, +0x28 (likely up vector)
        float dot2 = transform5[0x24 / 4] * dy + transform4[0x20 / 4] * dx + transform6[0x28 / 4] * dz;
        float distance = sqrtf(dx*dx + dy*dy + dz*dz);
        if (dot2 < distance * DAT_00d5f534) {
            bBehind = !bBehind;
        }

        // If the target is behind the camera, flip the yaw angle
        if (bBehind) {
            m_yawAngle = DAT_00e44564 - m_yawAngle;
        }
    }
}