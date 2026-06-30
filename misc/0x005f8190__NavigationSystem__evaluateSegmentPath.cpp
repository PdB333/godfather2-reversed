// FUNC_NAME: NavigationSystem::evaluateSegmentPath
// Address: 0x005f8190
// This function iterates over a sequence of navigation segments (or waypoints), accumulating a total distance/cost.
// It checks per-segment and per-node flags for blocking conditions and returns status:
//   0 = immediate failure (segment not found)
//   1 = path clear
//   2 = path blocked by condition flags
// Parameters:
//   this       - NavigationSystem instance (subject to flag checks at +0x20, +0x48, +0x4C)
//   segments   - pointer to a segment list/manager container (with a data array offset at +0x20)
//   startIndex - index of the first segment in the list
//   outCost    - output total accumulated cost (float)
//   endIndex   - index of the last segment (loop terminates when reached)
int NavigationSystem::evaluateSegmentPath(NavigationSystem* this, void* segments, int startIndex, float* outCost, int endIndex)
{
    int currentIndex = startIndex;
    int status = 1;
    float* segPtr;

    // Attempt to retrieve the first segment from the list
    segPtr = (float*)segmentLookup(segments, startIndex); // FUN_005f60f0
    if (segPtr == 0) {
        *outCost = FLT_INFINITY; // DAT_00e2e50c -> large positive constant
        return 0;
    }

    bool notAtEnd = (startIndex != endIndex);
    *outCost = 0.0f;
    status = 1;

    if (notAtEnd) {
        while (status == 1) {
            // Get current segment data pointer (result from segmentLookup)
            segPtr = (float*)segmentLookup(segments, currentIndex);
            // Compute the actual node/segment data offset (size 0x24 per entry)
            int nodeOffset = *(int*)((char*)segments + 0x20) + (uint)*(ushort*)((int)segPtr + 4) * 0x24;
            // (+4 from segPtr: probably an index field)
            uint agentFlags   = *(uint*)(this + 0x4C);
            ushort segFlags1  = *(ushort*)((int)segPtr + 10); // flags from the segment
            ushort nodeFlags  = *(ushort*)(nodeOffset + 0x18); // flags from the node data

            // Accumulate the distance/cost value (first float of the segment)
            *outCost += *segPtr;

            // Check if any blocking condition is met:
            // block if (agentFlags & segFlags1) or (agent's low flags & nodeFlags) and agent can be blocked
            bool blocked = ((agentFlags & segFlags1) != 0) ||
                           ((*(ushort*)(this + 0x48) & nodeFlags) != 0);
            if (blocked && ((*(uint*)(this + 0x20) & 0x800) == 0)) {
                status = 2;
                *outCost = FLT_INFINITY; // mark path as invalid
            }

            // Advance to next segment (the new offset becomes the next index)
            currentIndex = nodeOffset;

            // If we reached the target end index, return current status
            if (currentIndex == endIndex) {
                return status;
            }
        }
    }

    return status;
}