// FUNC_NAME: NodeLinkManager::establishLink
// Address: 0x00805810
// Role: Establish a link between two nodes based on link type and state flags.

__thiscall int NodeLinkManager::establishLink(uint this, char linkType, void* param3, void* param4)
{
    uint sourceNode; // local_4
    uint targetNode; // local_8
    uint sourceActionId; // uVar1, used later
    char flagCheck; // cVar2
    char uniqueTag; // uVar3
    int actionId; // uVar4

    // Determine sourceNode based on slot flag at +0xff8
    sourceNode = this;
    if (*(char*)(this + 0xff8) != 0x01) // not connector type 1
    {
        if (*(int*)(this + 0xff0) == 0)
            sourceNode = 0;
        else
            sourceNode = *(int*)(this + 0xff0) - 0x48; // get base from pointer
    }

    // Determine targetNode based on slot flag at +0xff8
    targetNode = this;
    if (*(char*)(this + 0xff8) != 0x02) // not connector type 2
    {
        if (*(int*)(this + 0xff0) == 0)
            targetNode = 0;
        else
            targetNode = *(int*)(this + 0xff0) - 0x48;
    }

    if (sourceNode == 0 || targetNode == 0)
        return 0;

    // Validate that the two connectors are compatible
    flagCheck = validateNodeConnection(targetNode, sourceNode, targetNode + 0xff0, sourceNode + 0xff0);
    if (flagCheck != 0)
    {
        // If linkType is 0, ensure both connectors have a valid tag (not -1)
        if (linkType == 0)
        {
            if (*(char*)(targetNode + 0xff9) == -1 || *(char*)(sourceNode + 0xff9) == -1)
            {
                uniqueTag = assignConnectionTag();
                *(char*)(targetNode + 0xff9) = uniqueTag;
                *(char*)(sourceNode + 0xff9) = uniqueTag;
            }
        }

        // Determine action ID based on linkType
        // Map linkType (0-17) to internal action IDs (mostly ASCII codes)
        switch (linkType)
        {
        case 0:  actionId = 0; break;
        case 1:  actionId = 0x4c; break; // 'L'
        case 2:  actionId = 0x2f; break; // '/'
        case 3:  actionId = 0x30; break; // '0'
        case 4:  actionId = 0x31; break; // '1'
        case 5:  actionId = 0x32; break; // '2'
        case 6:  actionId = 0x33; break; // '3'
        case 7:  actionId = 0x34; break; // '4'
        case 8:  actionId = 0x35; break; // '5'
        case 9:  actionId = 0x36; break; // '6'
        case 10: actionId = 0x37; break; // '7'
        case 11: actionId = 0x38; break; // '8'
        case 12: actionId = 0x39; break; // '9'
        case 13: actionId = 0x3a; break; // ':'
        case 14: actionId = 0x3b; break; // ';'
        case 15: actionId = 0x3b; break;
        case 16: actionId = 0x3b; break;
        case 17: actionId = 0x3b; break;
        }

        // Store source node for later
        sourceNode = sourceNode; // Already have it
        // Read the action parameter from source node based on tag: use +0x6f0 for certain case
        uint sourceParam = *(uint*)(sourceNode + 0x6f0); // reinterpret as uint
        // Determine param2 (originally linkType) based on target node's tag at +0xff9
        uint param2;
        if (*(char*)(targetNode + 0xff9) == 0)
            param2 = *(uint*)(targetNode + 0x6f8);
        else
            param2 = *(uint*)(targetNode + 0x6f4);

        // Apply the link action
        applyLinkEvent(sourceNode, targetNode, &sourceParam, &param2, actionId, actionId, param3, param4, DAT_00d5f520);
        return 1;
    }
    return 0;
}