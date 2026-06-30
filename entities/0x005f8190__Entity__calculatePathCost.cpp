// FUNC_NAME: Entity::calculatePathCost
#include <cfloat> // for FLT_MAX
#include <stdint.h>

struct NodeData {
    uint8_t pad_0x00[0x18];
    uint16_t flags; // +0x18
    uint8_t pad_0x1A[0x0A]; // total 0x24
};

struct EdgeData {
    float cost;        // +0x00
    uint16_t nextNodeIndex; // +0x04
    uint8_t pad_0x06[0x04];
    uint16_t extraFlags; // +0x0A
};

// The path graph manager
class PathGraph {
public:
    NodeData* getNodeArray() { return *(NodeData**)(this + 0x20); }
    EdgeData* getNextEdge(uint32_t nodeIndex); // FUN_005f60f0 - returns pointer to first edge from node, or null
};

// Entity class (player, NPC, etc.)
class Entity {
public:
    uint32_t m_entityFlags;   // +0x20
    uint16_t m_classFlags;    // +0x48
    uint32_t m_extraFlags;    // +0x4c
};

// Constants
static const float INF_COST = 1.0e30f; // DAT_00e2e50c

/**
 * Calculate the total cost of a path from startNode to goalNode,
 * considering entity flags that may block traversal.
 * @param this  The entity (player/NPC) whose flags are used.
 * @param graph The path graph containing nodes and edges.
 * @param startNode Pointer to the start node.
 * @param outCost   [out] Accumulated path cost, set to INF if blocked.
 * @param goalNode  Pointer to the target goal node.
 * @return 0 if startNode has no edges, 1 if path found, 2 if blocked.
 */
int Entity::calculatePathCost(PathGraph* graph, NodeData* startNode, float* outCost, NodeData* goalNode) {
    NodeData* currentNode = startNode;
    EdgeData* edge = graph->getNextEdge(currentNode);
    
    if (edge == nullptr) {
        *outCost = INF_COST;
        return 0;
    }
    
    bool notAtGoal = (startNode != goalNode);
    *outCost = 0.0f;
    int result = 1;
    
    if (notAtGoal) {
        // loop while not blocked
        while (true) {
            result = 1; // assume success
            
            // get next edge from current node
            edge = (EdgeData*)graph->getNextEdge(currentNode);
            // compute next node pointer from index
            uint16_t nextIdx = edge->nextNodeIndex;
            NodeData* nextNode = &graph->getNodeArray()[nextIdx];
            currentNode = nextNode; // update to next node
            
            // accumulate cost
            *outCost += edge->cost;
            
            // check if the edge or next node is blocked for this entity
            uint16_t edgeFlags = edge->extraFlags;
            uint32_t extraFlags = m_extraFlags; // +0x4c
            uint16_t classFlags = m_classFlags; // +0x48
            uint16_t nodeFlags = nextNode->flags; // +0x18 of node
            
            bool blockedByExtra = (extraFlags & edgeFlags) != 0;
            bool blockedByClass = (classFlags & nodeFlags) != 0;
            bool entityBlocked = (m_entityFlags & 0x800) != 0; // +0x20 bit 0x800
            
            if ((blockedByExtra || blockedByClass) && !entityBlocked) {
                result = 2;
                *outCost = INF_COST;
            }
            
            // check if we reached goal
            if (currentNode == goalNode) {
                return result;
            }
            
            // continue if not blocked
            if (result != 1) {
                break;
            }
        }
    }
    
    return result;
}