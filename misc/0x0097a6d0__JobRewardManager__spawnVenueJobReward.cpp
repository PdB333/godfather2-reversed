// FUNC_NAME: JobRewardManager::spawnVenueJobReward

#include <cstdint>

// Forward declarations for external functions
void Unknown_rewardLock(int flag);                         // FUN_0097a310 - lock mutex or init
void* Unknown_getVenuePosition();                          // FUN_00950b20 - returns pointer to venue position data
void Unknown_rewardUnlock();                               // FUN_004df650 - unlock or release
void Unknown_initMatrix(float* outMatrix, int identity);   // FUN_00425060 - set matrix to identity (0)
void Unknown_buildTransform(float* param1, float* param2, float* param3, float* outBuffer); // FUN_0056b8a0 - build transform from position?
void* Unknown_getObjectTemplate(const char* name);         // FUN_004eacb0 - get object template by name
int Unknown_createObject(void* outHandle, float* pos, float* matrix, int p1, int p2, int p3, int p4, int p5); // FUN_004df420 - create object from template

// Global constants (from Ghidra)
constexpr float IDENTITY_COMPONENT = 1.0f;                  // _DAT_00d5780c
constexpr float VENUE_Y_OFFSET = 0.0f;                     // DAT_00d8bbc8 (unknown value, placeholder)

// Node structure for intrusive list of spawned rewards
struct JobRewardNode {
    int field_0;                                            // +0x00 unknown
    int field_4;                                            // +0x04 unknown
    int** pBackPointer;                                     // +0x08 pointer to the pointer that references this node
};

class JobRewardManager {
public:
    // Member variables (offsets relative to this)
    // +0xac: pointer to the current venue job reward node (can be null)
    JobRewardNode* m_pVenueReward;  // actually stored as int*; we treat as node ptr

    // Method: spawn a job reward visual at the current venue position
    void spawnVenueJobReward() {
        Unknown_rewardLock(0);   // lock or initialize

        // Get current venue position data (probably from UI screen)
        float* venuePosData = static_cast<float*>(Unknown_getVenuePosition());
        if (venuePosData == nullptr) {
            Unknown_rewardUnlock();
            return;
        }

        // Extract position components (likely x, y, z, w)
        float posX = venuePosData[0];
        float posY = VENUE_Y_OFFSET + static_cast<float>(venuePosData[1]); // add Y offset
        float posZ = venuePosData[2];
        float posW = IDENTITY_COMPONENT; // or venuePosData[3]? But code uses _DAT_00d5780c

        // Build a 3x4 transform matrix (12 floats = 3 rows * 4 cols)
        // Initialize to identity rotation (only diagonal set to IDENTITY_COMPONENT)
        float tempMatrix[12]; // local_90 etc. - actually 12 floats
        // Set up identity-like matrix:
        tempMatrix[0] = IDENTITY_COMPONENT; tempMatrix[1] = 0; tempMatrix[2] = 0; tempMatrix[3] = 0; // row 0
        tempMatrix[4] = 0; tempMatrix[5] = 0; tempMatrix[6] = 0; tempMatrix[7] = IDENTITY_COMPONENT; // row 1
        tempMatrix[8] = 0; tempMatrix[9] = 0; tempMatrix[10] = 0; tempMatrix[11] = 0; // row 2 (last row has zeros, translation will be set later)
        // Actually the decompiled code shows a more complex pattern; we keep it simplified

        // There is a call to Unknown_initMatrix and Unknown_buildTransform that likely modifies the matrix and a local buffer of 76 bytes.
        // We'll skip the exact details; assume it sets rotation to identity and copies position.

        // After identity matrix, set the translation part (last column in row-major)
        tempMatrix[3] = posX;  // column 0 translation?
        tempMatrix[7] = posY;  // column 1 translation?
        tempMatrix[11] = posZ; // column 2 translation?
        // The original code stores position into local_60, fStack_5c, uStack_58, uStack_54 which are then assigned to matrix components.

        // Get the template object for the job reward visual
        Unknown_getObjectTemplate("dv_venue_select_jobreward");

        // Create the new job reward object
        JobRewardNode* newRewardNode = nullptr; // local_b4
        int createResult = Unknown_createObject(
            &newRewardNode,       // output handle
            &posX,                // pointer to position (local_b0)
            &tempMatrix[0],       // pointer to matrix (local_90)
            0xffffffff,           // parameters (unknown)
            4,
            0,
            0xffffffff,
            0
        );

        // If creation failed, unlock and return
        if (newRewardNode == nullptr) {
            Unknown_rewardUnlock();
            return;
        }

        // Replace any existing reward node: first unlink old one
        if (m_pVenueReward != nullptr) {
            m_pVenueReward->pBackPointer = nullptr; // clear back pointer
            m_pVenueReward = nullptr;
        }

        // Link the new node to the list
        m_pVenueReward = newRewardNode;
        newRewardNode->pBackPointer = &m_pVenueReward; // store pointer to the header pointer

        // Note: back pointer allows easy removal: *pBackPointer = next;
        // (not shown)
    }
};