// FUNC_NAME: Entity::checkAndSendPositionUpdate
// Address: 0x007ffdf0
// This function determines if an entity's position needs to be replicated to other players.
// It compares the current position (from a global player transform) with the last sent position,
// and if the difference exceeds a threshold or a timeout has elapsed, it builds a network packet
// and inserts the entity into a global update list.

#include <cmath>
#include <cstdint>

// Global constants
extern uint32_t g_gameFrameCount; // DAT_01205224
extern float g_positionUpdateDistanceThreshold; // DAT_00d5c458
extern uint32_t g_floatSignMask; // DAT_00e44680 (likely 0x7FFFFFFF, for fast fabs)
extern float g_packFormatArg; // DAT_00d92d14

// Forward declarations of helper functions (assumed from EA EARS network layer)
extern void* getLocalPlayerTransform(); // FUN_00471610
extern void networkMessageBeginWrite(void* msgBuilder, int param1, uint32_t msgType, uint32_t flags, int param2); // FUN_009a4380
extern void packPositionIntoBuffer(const float* position, void* buffer, float formatArg); // FUN_005fcf80
extern UpdateNode* getGlobalUpdateListHead(); // FUN_009a3d70
extern void removeNodeFromList(UpdateNode* node); // FUN_004daf90
extern void networkMessageEndWrite(); // FUN_009a4440

// Represents a node in the global replication update list.
struct UpdateNode {
    UpdateNode* pNext; // +0x00
    UpdateNode* pPrev; // +0x04
    int data;          // +0x08 (used as "object ID" or similar)
};

// Assumed entity class layout (partial)
// The function is __thiscall, so 'this' is the entity.
struct Entity {
    // ... other members ...
    int m_networkConnection; // +0x3d4 (pointer to some network object? used as flag)
    uint8_t m_messageBuilder[?]; // +0x3c0 (network message buffer)
    int m_messageParam1; // +0x5f0
    int m_messageParam2; // +0x5c4

    // Replication update state
    UpdateNode m_updateNode; // +0x1ba8 (embedded node for the global update list)
    uint32_t m_lastUpdateFrame; // +0x1bb4
    float m_lastPosition[3]; // +0x1bb8 (x, y, z)

    // Member functions
    int checkAndSendPositionUpdate();
};

int Entity::checkAndSendPositionUpdate()
{
    // Get the current player/camera transform (the source for replication)
    void* transformBase = getLocalPlayerTransform();
    float* currentPosition = (float*)((uint8_t*)transformBase + 0x30); // +0x30 is position start

    // Determine if an update is needed.
    // Condition: either no previous update, or too many frames elapsed,
    // or any axis moved more than the threshold.
    bool needsUpdate = false;

    if (m_lastUpdateFrame == 0)
    {
        needsUpdate = true;
    }
    else if ((g_gameFrameCount - m_lastUpdateFrame) > 500)
    {
        needsUpdate = true;
    }
    else
    {
        // Fast absolute difference using integer operations (mask sign bit)
        auto fastAbsDiff = [](float a, float b) -> float {
            uint32_t ia = reinterpret_cast<uint32_t&>(a);
            uint32_t ib = reinterpret_cast<uint32_t&>(b);
            uint32_t diff = (ia - ib) & g_floatSignMask;
            return reinterpret_cast<float&>(diff);
        };

        if (fastAbsDiff(currentPosition[0], m_lastPosition[0]) > g_positionUpdateDistanceThreshold ||
            fastAbsDiff(currentPosition[1], m_lastPosition[1]) > g_positionUpdateDistanceThreshold ||
            fastAbsDiff(currentPosition[2], m_lastPosition[2]) > g_positionUpdateDistanceThreshold)
        {
            needsUpdate = true;
        }
    }

    // Only proceed if update is needed and the network connection is valid.
    if (needsUpdate && m_networkConnection != 0)
    {
        // Build a network message (likely a position update packet)
        networkMessageBeginWrite(
            &m_messageBuilder,
            m_messageParam1,
            0x40102,        // message type identifier
            0x2000000,      // flags
            m_messageParam2
        );

        // Pack the current position into the message buffer
        uint8_t tempBuffer[100];
        packPositionIntoBuffer(currentPosition, tempBuffer, g_packFormatArg);

        // Update the global replication update list: ensure this entity's node is at the front.
        UpdateNode* headNode = getGlobalUpdateListHead();
        UpdateNode* thisNode = &m_updateNode;

        if (thisNode != headNode)
        {
            if (thisNode->pNext != headNode->pNext)
            {
                if (thisNode->pNext != nullptr)
                {
                    removeNodeFromList(thisNode);
                }
                thisNode->pNext = headNode->pNext;
                if (headNode->pNext != nullptr)
                {
                    thisNode->pPrev = headNode->pNext->pPrev; // should be headNode
                    headNode->pNext->pPrev = thisNode;
                }
            }
        }

        // Store the head's data (likely a global pointer) into this node's data field
        thisNode->data = headNode->data; // Actually headNode->data is at offset +0x08, but code uses piVar4[2] which is headNode->data

        // Record the current frame and position for next check
        m_lastUpdateFrame = g_gameFrameCount;
        m_lastPosition[0] = currentPosition[0];
        m_lastPosition[1] = currentPosition[1];
        m_lastPosition[2] = currentPosition[2];

        // Finish building the message (send it)
        networkMessageEndWrite();
    }

    // Return the pointer to the embedded update node (used by caller)
    return reinterpret_cast<int>(&m_updateNode);
}