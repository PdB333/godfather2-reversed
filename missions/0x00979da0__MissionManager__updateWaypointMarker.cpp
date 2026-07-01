// FUNC_NAME: MissionManager::updateWaypointMarker

#include <cmath>

// Global constants
extern float DAT_00e44620;  // Distance threshold (approximately 2.0f?)
extern float DAT_011302e0;  // Default stop position X? (0.0f)
extern float DAT_01130458;  // Default stop position X? (0.0f)
extern unsigned int _DAT_00d5780c; // Some packed int/float

// Forward declarations of called functions
void __fastcall getCurrentPosition(float* outPos);                   // FUN_004df780
void __fastcall destroyEntity(int entityHandle);                     // FUN_0094b0e0
void* __fastcall findInHashTable(unsigned int* key);                  // FUN_006b4d50
int __fastcall spawnEntity(unsigned int type, float* pos, ...);       // FUN_0094ca20 (parameters unknown)
void __fastcall playSoundOrEffect(float* pos, int effectID);         // FUN_00408a00
void __fastcall registerEntity(int entityHandle);                    // FUN_009c8f10
void __fastcall notifyWaypointState(char active);                    // FUN_00979900

char __fastcall MissionManager::updateWaypointMarker(int thisPtr)
{
    char isTargetReached = 0;

    // Check if a target exists (e.g., mission objective is active)
    if (*(int*)(thisPtr + 0xF8) != 0)
    {
        float currentPos[4]; // Actually a 4-component vector? Engine uses (X,Y,Z,1?) type
        getCurrentPosition(currentPos);

        // Copy current position into a local that can be modified later
        float goalPos[4]; // [0]=X, [1]=Y, [2]=Z, [3]=w?
        goalPos[0] = currentPos[0];
        goalPos[1] = currentPos[1];
        goalPos[2] = currentPos[2];
        goalPos[3] = currentPos[3];

        isTargetReached = 1;

        // If waypoint is already active, check if we are close enough to stop
        if ((*(char*)(thisPtr + 0xB4) != 0) &&
            (sqrt( (currentPos[0] - *(float*)(thisPtr + 0xA4)) * (currentPos[0] - *(float*)(thisPtr + 0xA4)) +
                   (currentPos[1] - *(float*)(thisPtr + 0xA8)) * (currentPos[1] - *(float*)(thisPtr + 0xA8)) +
                   (currentPos[2] - *(float*)(thisPtr + 0xAC)) * (currentPos[2] - *(float*)(thisPtr + 0xAC)) ) <= DAT_00e44620))
        {
            isTargetReached = 0; // Within threshold, stop following the waypoint
        }

        // Remove any previously spawned marker entity (e.g., an actual 3D object)
        if (*(int*)(thisPtr + 0xB8) != 0)
        {
            destroyEntity(*(int*)(thisPtr + 0xB8));
            *(int*)(thisPtr + 0xB8) = 0;
        }

        if (isTargetReached == 0)
        {
            // Target reached – clear waypoint
            *(char*)(thisPtr + 0xB4) = 0;       // Inactive flag
            *(int*)(thisPtr + 0xA0) = 0;         // Target ID? (set to 0)
            goalPos[0] = DAT_011302e0;           // Reset to a default position
            goalPos[1] = 0.0f;
            goalPos[2] = (float)((unsigned int)goalPos[2] & 0xFFFFFF00); // Clear low bits (alignment?)
            playSoundOrEffect(&goalPos[0], 0);   // Play a “stopped” sound/effect
        }
        else
        {
            // Update stored target position and flag
            *(float*)(thisPtr + 0xA4) = goalPos[0];
            *(float*)(thisPtr + 0xA8) = goalPos[1];
            *(float*)(thisPtr + 0xAC) = goalPos[2];
            *(char*)(thisPtr + 0xB4) = 1;        // Mark as active

            // Select the target ID based on some internal state
            unsigned int targetID;
            if ((*(int*)(thisPtr + 0x14C) == 1) || (1 < *(int*)(thisPtr + 0x14C) - 3U))
            {
                targetID = *(unsigned int*)(thisPtr + 0x140);
            }
            else
            {
                targetID = *(unsigned int*)(thisPtr + 0x144);
            }
            *(unsigned int*)(thisPtr + 0xA0) = targetID;

            // Spawn the visual waypoint marker (entity type 0x26)
            int outEntityArray[3] = {0, 0, 0}; // Used to receive the spawned entity handle
            unsigned int key = targetID;
            void* hashEntry = findInHashTable(&key);
            if (hashEntry != nullptr)
            {
                *(unsigned int*)hashEntry = targetID; // Store target ID in hash? (some update)
            }

            // Build a spawn structure with position and orientation (?)
            // The following fields likely represent a transformation matrix or similar
            // (simplified: just copy from a global template)
            float spawnPos[4] = { goalPos[0], goalPos[1], goalPos[2], * reinterpret_cast<float*>(&_DAT_00d5780c) };
            // Additional matrix rows or parameters (unknown, but copied from globals)
            float spawnData[12] = { /* ... */ };
            // Actually the decompiled code does a complicated copy of global data (probably a quaternion or rotation)
            // We'll represent it as a simplified struct for clarity.

            // Simplified call: spawn entity type 0x26 at position
            int spawnedEntity = spawnEntity(0x26, spawnPos, 0, 8, 0, 1, 2, outEntityArray, 0, 0, 0, 0);
            *(int*)(thisPtr + 0xB8) = spawnedEntity;

            // Reset the goal position to a default? (e.g., stop triggering sound)
            goalPos[0] = DAT_01130458;
            goalPos[1] = 0.0f;
            goalPos[2] = (float)((unsigned int)goalPos[2] & 0xFFFFFF00);
            playSoundOrEffect(&goalPos[0], 0); // Play a “starting” sound/effect

            // If we got a valid entity back, register it
            if (outEntityArray[0] != 0)
            {
                registerEntity(outEntityArray[0]);
            }
        }

        // Notify other systems about the current waypoint state
        notifyWaypointState(*(char*)(thisPtr + 0xB4));
    }

    return isTargetReached;
}