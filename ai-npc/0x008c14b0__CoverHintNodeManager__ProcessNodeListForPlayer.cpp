// FUNC_NAME: CoverHintNodeManager::ProcessNodeListForPlayer

// Structure representing an internal node list (pointer + count) at this+0x1a4/0x1a8
struct NodeList {
    int** nodes;    // +0x1a4: pointer to array of pointers to CoverHintNode
    int   count;    // +0x1a8: number of nodes
};

// Structure representing a CoverHintNode
struct CoverHintNode {
    int   type;             // +0x04: node type (e.g., 7 = special)
    int   nodeId;           // +0x08: unique identifier
    int   flags;            // +0x0C
    int   unknown;          // +0x10
    int   unknown2;         // +0x14
    int   ownerPlayerId;    // +0x18: player ID that currently owns this node
};

// Input list structure: pointer to IDs and count
struct NodeIdList {
    int* ids;   // param_2[0] – array of node IDs
    int  count; // param_2[1] – number of IDs
};

// Forward declarations of called functions
void   SetNodeDirty(int flag);                                      // FUN_008c8a80(1)
int    GetCurrentPlayerId();                                        // FUN_00791320()
void   NodeShow(int playerId);                                     // FUN_008c8d00
void   NodeHide(int playerId);                                     // FUN_008c80d0
void   LogMessage(int severity, const char* message);               // FUN_008c8a20

void __thiscall CoverHintNodeManager::ProcessNodeListForPlayer(NodeIdList* nodeList, int playerId)
{
    uint idx = 0;

    if (nodeList->count != 0) {
        do {
            // Search for the current node ID in the internal list
            uint localIdx = 0;
            CoverHintNode* foundNode = nullptr;

            if (this->m_nodeList.count != 0) {
                CoverHintNode** nodePtr = this->m_nodeList.nodes;
                do {
                    // Compare node ID (+0x08) with the ID from the incoming list
                    if ((*nodePtr)->nodeId == nodeList->ids[idx]) {
                        if ((int)localIdx >= 0) {
                            foundNode = this->m_nodeList.nodes[localIdx];
                            goto LAB_FOUND;
                        }
                        break;
                    }
                    localIdx++;
                    nodePtr++;
                } while (localIdx < (uint)this->m_nodeList.count);
            }

            // Not found
            foundNode = nullptr;

LAB_FOUND:
            // If the node's current owner does not match the target player, mark it dirty
            if (foundNode->ownerPlayerId != playerId) {
                SetNodeDirty(1);  // FUN_008c8a80(1)
            }

            int currentPlayerId = GetCurrentPlayerId(); // FUN_00791320

            if (currentPlayerId == playerId) {
                // This is the active player -> show the node
                NodeShow(playerId); // FUN_008c8d00
            }
            else if (foundNode->type != 7) {
                // Not the active player and node is not a special type -> hide it
                NodeHide(playerId); // FUN_008c80d0
                LogMessage(4, DAT_00d5d7b8); // FUN_008c8a20 (severity 4, global string)
            }

            idx++;
        } while (idx < (uint)nodeList->count);
    }
    return;
}