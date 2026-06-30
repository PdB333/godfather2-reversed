// FUNC_NAME: CoverHintNode::evaluateCandidate
int __fastcall CoverHintNode::evaluateCandidate(CoverHintNode* this, float* targetPos, NodeData* nodeData, CandidateState* candidate, float currentDistance)
{
    // Add node's own travel cost (offset +0x4) to the accumulated distance
    currentDistance = nodeData->travelCost + currentDistance;

    // Get control flags from candidate state (byte at +0xA)
    uint8_t flags = candidate->flags;

    // If flags indicate candidate is not yet occupied (low 2 bits zero) OR current distance is better than stored best
    if (((flags & 3) == 0) || (currentDistance < (float)candidate->bestDistance))
    {
        // Update best distance and store this node as best candidate
        candidate->bestDistance = (int)currentDistance; // Truncate to int (float to int conversion)
        candidate->bestNode = nodeData;                 // Store pointer to node data

        // Clear bit 1 (0x02) – mark candidate as "evaluated" or "valid"
        candidate->flags = flags & 0xfd;

        // If bit 0 is clear (candidate not in "pending" state), evaluate path via other function
        if ((flags & 1) == 0)
        {
            return FUN_005f8a90(); // Likely finalizes or triggers path calculation
        }
        else
        {
            // Compute Euclidean distance from this node's position to target, add current distance, and update path
            float dx = this->position.x - targetPos[0];
            float dy = this->position.y - targetPos[1];
            float dz = this->position.z - targetPos[2];
            float distance = SQRT(dx*dx + dy*dy + dz*dz);
            FUN_005f8dc0(distance + currentDistance); // Likely updates search state or callback
        }
    }
    return 1; // Success
}