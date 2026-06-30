// FUNC_NAME: PathFollower::computePath
// Function address: 0x007270a0
// This function computes a path from a set of waypoints stored in the object.
// It manages a path result object and flags.

#include <cstdint>

// Constants (likely defined elsewhere)
constexpr float FLOAT_SENTINEL = DAT_00d5ccf8; // Sentinal value for no path timer
constexpr float FLOAT_THRESHOLD = DAT_01205228; // Threshold for path timer
constexpr float FLOAT_OFFSET = _DAT_00e5185c; // Offset for timer comparison

class PathFollower {
public:
    // +0x00 ... vtable
    // +0x04 ... other members

    // +0xb4 : short numWaypoints
    // +0xc4 : array of waypoint descriptors (8 bytes each: first int is pointer to node data, second int unknown)
    // +0x104: float pathTimer
    // +0x108: int* pPathResult (pointer to a path result object)
    // +0x10c: int* pPrevPathResult (linked list previous)
    // +0x110: uint flags
    // +0x114: byte pathFlags
    // +0x130: pathFinder (some path finder object)
    // +0x134: pathFinderExtra (extra data for path finder)

    // Returns: true if path is valid (or matches param_2), false otherwise.
    bool computePath(int targetNodeIndex, char force) {
        // Check if path computation is allowed
        uint flags = *(uint*)((uintptr_t)this + 0x110);
        bool flagBit17 = (flags >> 17) & 1;
        float pathTimer = *(float*)((uintptr_t)this + 0x104);
        bool timerExpired = (pathTimer == FLOAT_SENTINEL) ||
                            (pathTimer + FLOAT_OFFSET < FLOAT_THRESHOLD);

        if (!flagBit17 && (timerExpired || force != 0)) {
            // Reset timer to threshold
            *(float*)((uintptr_t)this + 0x104) = FLOAT_THRESHOLD;

            short numWaypoints = *(short*)((uintptr_t)this + 0xb4);
            int waypointData[4] = {0}; // max 4 waypoints

            if (numWaypoints > 0) {
                short maxWaypoints = *(short*)((uintptr_t)this + 0xb4);
                int* waypointArray = (int*)((uintptr_t)this + 0xc4);
                int idx = 0;
                do {
                    int* waypointPtr = waypointArray;
                    if (*waypointPtr == 0) {
                        waypointData[idx] = 0;
                    } else {
                        // Subtract 0x48 (header size) to get the actual node address
                        waypointData[idx] = *waypointPtr - 0x48;
                    }
                    idx++;
                    waypointArray += 2; // Each entry is 8 bytes
                } while (idx < maxWaypoints);
            }

            // Prepare parameters for path find call
            void* pathFinder = (void*)((uintptr_t)this + 0x130);
            // local_14 points to waypointData array
            int* waypointDataPtr = waypointData;
            // local_c is some constant (likely a path finder flag)
            uint32_t pathFinderFlag = DAT_00d5d7b8;
            // local_10 is number of waypoints
            int numWaypointsForCall = (int)numWaypoints;
            // Unknown extra data from +0x134
            uint32_t extraData = *(uint32_t*)((uintptr_t)this + 0x134);

            int pathResult = FUN_005f6e80(pathFinder, pathFinder, 0, &waypointDataPtr,
                                          extraData);

            if (pathResult == 0) {
                // Path finding failed
                *(uint8_t*)((uintptr_t)this + 0x114) &= ~0x08; // Clear path flag
                if (*(int*)((uintptr_t)this + 0x108) != 0) {
                    FUN_004daf90((undefined4*)((uintptr_t)this + 0x108));
                    *(int*)((uintptr_t)this + 0x108) = 0;
                }
            } else {
                // Path found
                *(uint8_t*)((uintptr_t)this + 0x114) |= 0x08; // Set path flag

                int* newPathBase = nullptr;
                if (*(int*)(pathResult + 0x24) == 0) {
                    newPathBase = nullptr;
                } else {
                    newPathBase = (int*)(*(int*)(pathResult + 0x24) - 0x48);
                }

                int* currentPath = *(int**)((uintptr_t)this + 0x108);
                int* newPath = nullptr;
                if (newPathBase != nullptr) {
                    newPath = newPathBase + 0x48; // Re-add header
                }

                if (currentPath != newPath) {
                    if (currentPath != nullptr) {
                        FUN_004daf90((undefined4*)currentPath);
                    }
                    *(int**)((uintptr_t)this + 0x108) = newPath;
                    if (newPath != nullptr) {
                        *(uint32_t*)((uintptr_t)this + 0x10c) = *(uint32_t*)(newPath + 4);
                        *(int**)(newPath + 4) = (int*)((uintptr_t)this + 0x108);
                    }
                }
            }
        }

        // Check if path is valid and matches target
        if ((*(uint8_t*)((uintptr_t)this + 0x114) & 0x08) != 0) {
            if (targetNodeIndex == 0) {
                return true;
            }
            int* currentPath = *(int**)((uintptr_t)this + 0x108);
            int pathBase = 0;
            if (currentPath != nullptr) {
                pathBase = (int)currentPath - 0x48;
            }
            if (pathBase != targetNodeIndex) {
                return true;
            }
        }
        return false;
    }

    // External functions (declared elsewhere)
    extern int FUN_005f6e80(void* obj1, void* obj2, int param3, int** waypoints, uint32_t extra);
    extern void FUN_004daf90(undefined4* ptr); // Likely release/delete
};