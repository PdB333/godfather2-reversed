// FUNC_NAME: PathFollower::updateCurrentPathNode
// Address: 0x005ffeb0
// Role: Updates the current path waypoint, advances to next node when reached within tolerance.
// Fields (relative to this):
// +0x40: bool bHasPath
// +0x44: PathNode* pCurrentNode (linked list head)
// +0x48: PathNode* pNextNode (internal list pointer?)
// +0x7c: int iOverrideMode (0 = use input path, !=0 = use override path from +0x84)
// +0x84: Vector4* pOverridePathData
// +0x88: void* pPathData (null when path is fresh)
// +0x90: Vector4* pAlternativePathData
// +0xb4: uint32 flags (bit 11 toggled on node reached / unreachable)
// +0x10: Vector3 currentWaypoint (x,y,z)
// +0x60: Vector3 targetPosition (x,y,z)
// +0xc0: float fTimer (set to 0 each update)
// +0xc4: float fDistanceToTarget
// +0xe0: int iCompletionFlag (0 = processing, non-zero = completed)

#include <cmath>

struct PathNode {
    PathNode* pPrev; // +0x00 (offset from node)
    PathNode* pNext; // +0x04
    float x;         // +0x08
    float y;         // +0x0C
    float z;         // +0x10
    // +0x14... possibly more
};

class PathFollower {
public:
    // +0x00: vtable? (not shown)
    bool bHasPath;                 // +0x40
    PathNode* pCurrentNode;        // +0x44
    PathNode* pNextNode;           // +0x48
    int iOverrideMode;             // +0x7C
    Vector4* pOverridePathData;    // +0x84
    void* pPathData;               // +0x88 (probably another list head)
    Vector4* pAlternativePathData; // +0x90
    uint32_t flags;                // +0xB4
    Vector3 currentWaypoint;       // +0x10 (x,y,z)
    Vector3 targetPosition;        // +0x60 (x,y,z)
    float fTimer;                  // +0xC0 (set to 0)
    float fDistanceToTarget;       // +0xC4
    int iCompletionFlag;           // +0xE0

    // Subroutines (declared externally, assumed to exist)
    int getNextPathNodeIndex(void* navSystem, int param2, PathNode* output, int param4, int searchParam); // FUN_005f6ee0
    PathNode* getPathNodeData(int* outHandle, void* navSystem, int param2, int handle, int param4, int unknown, int bitfield, int extra); // FUN_005f6ae0
    void releasePathNode(int* handle); // FUN_004daf90
    void releaseVector4(Vector4* vec); // FUN_005fd8d0 (deallocate a 4-float vector)
    float getRandomFloat(); // FUN_005fe710 (returns a random float)
};

int PathFollower::updateCurrentPathNode(void* navSystem, int param2, Vector4* inputPositions, int param4) {
    int iVar1;
    PathNode* puVar2;
    int iVar6;
    bool bUsingAlternative;
    float fRandom;
    float fSqDistCurrent;
    float fSqDistNode;

    // Get next path node index
    iVar6 = getNextPathNodeIndex(navSystem, param2, 0, param4, inputPositions->w); // param_3[1] is inputPositions->w

    if (iVar6 != 0) {
        bHasPath = true;

        iVar1 = pCurrentNode; // +0x44 (stored as pointer, cast to int for comparison)
        if (iVar1 != iVar6) {
            if (iVar1 != 0) {
                releasePathNode(&pCurrentNode); // Actually release the old node? FUN_004daf90 takes pointer to pointer?
            }
            pCurrentNode = iVar6;
            pNextNode = *(PathNode**)(iVar6 + 4); // Store the node's next pointer
            // Insert node at head: set node's next to point to the list head field address
            *(int**)(iVar6 + 4) = &pCurrentNode;
        }

        // Determine source position for waypoint data
        Vector4* sourcePos;
        bUsingAlternative = (pPathData == 0);
        if (bUsingAlternative) {
            sourcePos = 0;
        } else {
            sourcePos = pAlternativePathData;
        }

        Vector4 localPos;
        if (iOverrideMode == 0) {
            // Use input positions directly
            localPos.x = inputPositions->x;
            localPos.y = inputPositions->y;
            localPos.z = inputPositions->z;
            localPos.w = inputPositions->w;
        } else {
            // Use override path data
            sourcePos = pOverridePathData; // +0x84
            localPos.x = sourcePos->x;
            localPos.y = sourcePos->y;
            localPos.z = sourcePos->z;
        }

        if (bUsingAlternative) {
            // Use input positions again
            localPos.x = inputPositions->x;
            localPos.y = inputPositions->y;
            localPos.z = inputPositions->z;
            localPos.w = inputPositions->w;
        } else {
            // Use alternative path data
            localPos.x = sourcePos->x;
            localPos.y = sourcePos->y;
            localPos.z = sourcePos->z;
        }

        // Build bitfield for getPathNodeData call
        uint32 bitfield = (flags >> 11) & 0xFF; // Extract bits 11-18? Actually only bit 11 used
        bitfield = (bitfield & 0xFFFFFF01) | 0; // Clear low byte? Complex manipulation

        // Get a path node data from the system
        PathNode* newNodeData = getPathNodeData(&iVar6, navSystem, param2, pCurrentNode, param4, 0, bitfield, 0);
        Vector4 nodePos;
        nodePos.x = *((float*)&newNodeData[0]); // first float
        float fNodeY = *((float*)&newNodeData[1]);
        nodePos.y = fNodeY;
        nodePos.z = *(float*)(pCurrentNode + 0xC);
        nodePos.x = *((float*)&newNodeData[0]);
        nodePos.y = fNodeY;
        nodePos.z = fNodeY; // This may be a typo, but decompiled shows local_3c = fVar10, etc.

        // Actually the decompiled code is messy: 
        // puVar7 = FUN_005f6ae0(...)
        // local_4c = *puVar7;        // x
        // fVar10 = (float)puVar7[1]; // y
        // local_40 = *(undefined4 *)(iVar6 + 0xc); // z from node
        // local_48 = fVar10;          // copy y
        // local_44 = local_4c;        // copy x
        // local_3c = fVar10;          // duplicate?
        // Then calls FUN_005f6ee0 with &local_4c (which is a Vector4 structure: local_4c, local_48, local_40, local_3c)
        // So we need a Vector4 with x,y,z and something else.

        Vector4 tempVec;
        tempVec.x = nodePos.x; // Actually the first float from node data
        tempVec.y = fNodeY;
        tempVec.z = *(float*)(pCurrentNode + 0xC); // z from the node itself
        tempVec.w = tempVec.z; // or something

        // Get next node index from the resulting position
        int iNextNode = getNextPathNodeIndex(navSystem, &tempVec, 0, param4, inputPositions->w);
        if (iNextNode == 0) {
            releaseVector4(&tempVec);
            fSqDistCurrent = fNodeY * fNodeY; // weird: using square of y as distance? Might be a mistake.
        } else {
            fSqDistCurrent = 0.0f;
        }

        fRandom = getRandomFloat();
        float fThreshold = fRandom * fRandom;

        if ((iNextNode != 0) || (fThreshold < fSqDistCurrent)) {
            // Toggle flag bit 11
            if ((flags >> 11) & 1) {
                flags &= ~0x800;
            } else {
                flags |= 0x800;
            }

            // Re-get node data with updated flag
            bitfield = (flags >> 11) & 0xFF;
            bitfield = (bitfield & 0xFFFFFF01) | 0;
            PathNode* newNodeData2 = getPathNodeData(&iVar6, navSystem, param2, pCurrentNode, param4, 0, bitfield, 0);
            Vector4 tempVec2;
            tempVec2.x = *((float*)&newNodeData2[0]);
            float fNodeY2 = *((float*)&newNodeData2[1]);
            tempVec2.y = fNodeY2;
            tempVec2.z = *(float*)(pCurrentNode + 0xC);
            tempVec2.w = fNodeY2;

            iVar6 = getNextPathNodeIndex(navSystem, &tempVec2, 0, param4, inputPositions->w);
            if (iVar6 != 0) {
                goto LAB_COMPLETED;
            }

            releaseVector4(&tempVec2);
            if (!(fThreshold < fNodeY2)) {
                // Node not reached, continue
                // Fall through to update position
            } else {
                goto LAB_COMPLETED;
            }
        }

        // Update current waypoint position to the node's position
        currentWaypoint.x = tempVec.x;
        currentWaypoint.y = tempVec.y;
        currentWaypoint.z = tempVec.z; // from node+0xC? Or tempVec?

        // Store target position (inputPositions or override)
        targetPosition.x = inputPositions->x;
        targetPosition.y = inputPositions->y;
        targetPosition.z = inputPositions->z;
        targetPosition.w = inputPositions->w;

        // Calculate distance to target
        float dx = targetPosition.x - currentWaypoint.x;
        float dy = targetPosition.y - currentWaypoint.y;
        float dz = targetPosition.z - currentWaypoint.z;
        fDistanceToTarget = sqrtf(dx*dx + dy*dy + dz*dz);

        fTimer = 0.0f;
        iCompletionFlag = 0;
    }

    return 1; // Still processing

LAB_COMPLETED:
    iCompletionFlag = 0;
    return 2; // Path completed
}