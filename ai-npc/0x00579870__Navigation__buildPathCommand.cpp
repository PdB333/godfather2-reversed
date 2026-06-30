// FUNC_NAME: Navigation::buildPathCommand
// Address: 0x00579870
// Role: Builds a path movement command from path data and AI state.

struct PathCommand {
    void* owner;           // +0x00: pointer to the NPC/entity
    void* pathData;        // +0x04: pointer to path data structure
    int speedOrDirection;  // +0x08: value from owner+0x18 (e.g., speed or direction index)
    int nodeIndex;         // +0x0C: current node index (from pathData[5] or [7])
    int targetNodeId;      // +0x10: target node ID (-1 if none)
    char flags;            // +0x14: bit0 = edi==3, bit1 = pathData[0xb] bit2
    int state;             // +0x18: state (0=move,3=arrived,5=continue)
};

struct PathData {
    int nodeCount;         // +0x00: number of nodes (or index)
    int field_04;
    int field_08;
    int nodeA;             // +0x14 (index 5)
    int field_18;
    int nodeB;             // +0x1C (index 7)
    int field_20;
    int field_24;
    int flagsByte;         // +0x2C (offset 0xb): bit5 = has alternate, bit2 = something
    int altNodeCount;      // +0x30 (offset 0xc)
    int* altNodeArray;     // +0x34 (offset 0xd)
    int* nodeArray;        // +0x38 (offset 0xe)
    int field_40;          // +0x40 (offset 0x10) - target node ID?
};

void __fastcall Navigation::buildPathCommand(PathCommand* outCmd, PathData* pathData)
{
    // Registers: ESI = this (Navigation instance), EDI = state param (0=move,3=arrived)
    // In actual __thiscall, ESI would be ECX, but decompiler shows ESI.
    int* thisObj = (int*)unaff_ESI;
    int state = unaff_EDI;

    outCmd->owner = thisObj;
    outCmd->pathData = pathData;
    outCmd->speedOrDirection = *(int*)((char*)thisObj + 0x18);

    // Choose current node index based on alternate flag and node count
    if ((*(char*)pathData + 0xb) & 0x20) == 0 || pathData->nodeCount < 2) {
        outCmd->nodeIndex = pathData->nodeA;
    } else {
        outCmd->nodeIndex = pathData->nodeB;
    }

    // If a "target acquired" flag is set in this object, set targetNodeId to -1
    if ((*(uint*)((char*)thisObj + 0x10) >> 9) & 1) {
        outCmd->targetNodeId = -1;
        goto setFlags;
    }

    // Determine which node array to use for next target
    if ((pathData->flagsByte & 0x20) == 0 || pathData->nodeCount < 3) {
        if ((pathData->flagsByte & 0x20) != 0 && pathData->nodeCount == 2) {
            outCmd->targetNodeId = pathData->field_40;  // +0x10
            goto setFlags;
        }
        if (pathData->altNodeCount == 0) {
            int* nextPtr = pathData->altNodeArray;  // +0xd
            goto assignCheck;
        }
    } else {
        int* nextPtr = pathData->nodeArray;  // +0xe
        assignCheck:
        if (nextPtr != nullptr) {
            outCmd->targetNodeId = *nextPtr;
            goto setFlags;
        }
    }
    outCmd->targetNodeId = -1;

setFlags:
    outCmd->flags = (char) ((pathData->flagsByte >> 2) & 1) | (state == 3);

    if (outCmd->targetNodeId != -1 && state == 0) {
        outCmd->state = 5;  // continue moving
    } else {
        outCmd->state = state;
    }
}