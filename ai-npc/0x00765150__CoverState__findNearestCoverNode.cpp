// FUNC_NAME: CoverState::findNearestCoverNode
// Function at 0x00765150: Searches backwards through CoverHintNodeManager's node list for the highest-index node within search radius.
// Returns the index of the nearest cover node (or -1 if none found). Caches result in this+0xB8.

class CoverHintNode {
public:
    // +0x00: likely vtable or next/prev pointers
    // +0x08: position (three floats: x, y, z)
    float x;      // +0x08
    float y;      // +0x0C
    float z;      // +0x10
};

class CoverHintNodeManager {
public:
    virtual int getCount();          // vtable+0x08
    virtual CoverHintNode* getItem(int index); // vtable+0x0C
    // ... other virtuals
};

class CoverState {
public:
    // Offset 0x54: squared search radius
    float searchRadiusSq;   // +0x54
    // Offsets 0x58,0x5C,0x60: current position (world coords)
    float posX;             // +0x58
    float posY;             // +0x5C
    float posZ;             // +0x60
    // Offset 0xB8: cached index of nearest cover node (-1 if none)
    int nearestCoverIndex;  // +0xB8

    // Find nearest cover node within searchRadiusSq from current position.
    // Iterates backwards through manager's nodes; stops at first valid node within range.
    // Returns index (cached for subsequent calls until reset).
    int findNearestCoverNode(CoverHintNodeManager* manager) __thiscall {
        if (nearestCoverIndex == -1) {
            int count = manager->getCount();
            for (int i = count - 1; ; i--) {
                CoverHintNode* node;
                do {
                    node = manager->getItem(i);
                    i--;
                } while (node == nullptr);  // skip null entries
                // Compute squared distance to this node
                float* nodePos = &node->x;  // offset +0x08
                float dx = nodePos[0] - posX;
                float dy = nodePos[1] - posY;
                float dz = nodePos[2] - posZ;
                float distSq = dx*dx + dy*dy + dz*dz;
                if (distSq <= searchRadiusSq) {
                    nearestCoverIndex = i;   // note: i was decremented an extra time in do-while; this stores the index of the valid node (the one that passed null check)
                    break;
                }
            }
        }
        return nearestCoverIndex;
    }
};