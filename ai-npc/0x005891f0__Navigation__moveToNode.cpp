// FUNC_NAME: Navigation::moveToNode
// Address: 0x005891f0
// Role: Processes a movement request (pathfinding to a target node) and initiates movement if reachable.
// Uses a pathfinding query structure to check reachability, computes target position, and starts navigation.

char __thiscall Navigation::moveToNode(void *this, MovementRequest *request) {
    char result;
    PathQuery query; // local_58 structure
    int currentNodeId;
    int navGraphId;
    float accumulatedTime;
    float speed;
    undefined4 uVar1;
    float fVar6;

    result = validateMovementRequest(request); // FUN_00581f60
    if (result == '\0') {
        return '\0';
    }

    // Early exit if: request is flagged as done (request->flags & 0x1) OR object is in a state that blocks movement (this->blockedFlag at +0x30)
    if (request->isDone != '\0' || *(char *)(this + 0x30) != '\0') {
        return result;
    }

    // Initialize pathfinding query structure
    query.targetNode = request->targetNode;           // +0x00
    query.unknown1 = 0xfffffffe;                      // +0x04
    query.unknown2 = 0;                                // +0x08
    query.reachable = '\0';                            // +0x0C
    query.unknown3 = 0;                                // +0x10
    query.thisPtr = this;                              // +0x14

    int sampleResult = executePathQuery(&query); // FUN_00587a00 - samples navigation graph, sets query.reachable
    if (sampleResult < 0 || query.reachable == '\0') {
        return '\0';
    }

    // Compute target position from target node's position minus a constant (likely ground level offset)
    NavNode *node = request->targetNode;
    Vector3 targetPos;
    targetPos.x = node->position.x;                    // node->position.x? Actually uses node+0x24 float
    targetPos.y = node->position.y - GROUND_Y;        // DAT_00e2b1a4 (constant ground plane Y, possibly 0)
    targetPos.z = node->position.z;                    // assumed from context
    // The decompiled shows: local_3c = *(undefined4 *)(param_1 + 0x20); local_38 = *(float *)(iVar3 + 0x24) - DAT_00e2b1a4;
    // This likely extracts the target node's Y component and subtracts ground Y.
    // The function FUN_00581d70(&local_40) likely transforms the target position relative to the object's current orientation.
    // For reconstruction, we assume it fills a matrix or quaternion stored in local_30..local_58.
    // We'll represent as a 3D position and orientation.

    Vector3 orientation; // placeholder for the output orientation/matrix from FUN_00581d70
    computeTargetTransform(this, node, &targetPos, &orientation); // FUN_00581d70

    // Store computed target transform into object's movement target fields (offsets 0x40-0x5c)
    *(Vector3 *)(this + 0x40) = targetPos;
    *(float *)(this + 0x4C)   = orientation.x;  // some orientation component (e.g., rotation around Y)
    *(Vector3 *)(this + 0x50) = orientation;    // second vector? Actually decompiled shows two sets of 3 floats + 1 float each.

    // Get current navigation node ID
    int navNodeCurrent = getCurrentNavNode(); // FUN_00578280
    int navGraphIdx = getNavGraphIndex();     // FUN_005782a0
    if (navGraphIdx == -1) {
        navGraphIdx = navNodeCurrent;
    }

    // Retrieve current speed and a timer/accumulator from the object
    uVar1 = *(undefined4 *)(this + 0x1C); // unknown field, maybe a timer ID or modifier
    fVar6 = *(float *)(this + 0x24);       // accumulated time or speed factor

    // Attempt to start pathfinding/movement from current node to target node
    if (startMovement(node, navGraphIdx)) { // FUN_00581b30
        // Stop any existing movement behavior (FUN_00586a30)
        stopCurrentMovement(uVar1);

        // Update movement timers: set elapsed time (request->speed? actually request->field_8) plus previous accumulator
        *(float *)(this + 0x1C) = request->speed + fVar6;
        *(float *)(this + 0x20) = fVar6; // store previous accumulator as start time
        return '\x01';
    }

    return '\0';
}

// Helper definitions (not part of the original code, for clarity):
struct MovementRequest {
    NavNode *targetNode; // offset 0x00
    float speed;         // offset 0x08? Actually used at param_2[2] as float
    char isDone;         // offset 0x10? param_2[4] as char
    // ... other fields unknown
};

struct PathQuery {
    NavNode *targetNode;
    int unknown1;
    int unknown2;
    char reachable;
    int unknown3;
    void *thisPtr;
};

struct NavNode {
    // offset 0x24 holds Y position (float)
    float x, y, z;
};