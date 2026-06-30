// FUN_NAME: PathEngine::lineOfSight

// Address: 0x005ff960
// Recursive raycast / line-of-sight function on a navigation mesh.
// Checks if the straight line segment from startPos to endPos is unobstructed by
// polygonal cells. Returns true (1) if clear, false (0) if blocked.
// The function uses a recursive subdivision approach: it finds the cell containing
// the segment, projects intermediate points onto cell boundaries, and recurses on
// subsegments up to a fixed depth.

#pragma once

#include <cmath>

// Forward declarations of helper functions (assumed to be members of the same class)
// int PathEngine::findContainingCell(float* start, float* end, int flag0, float unknown, float cellHeight);
// float* PathEngine::getIntermediatePoint(float* out, float* start, float* end, int cellIdx, float unknown, int flag1, bool useExact, int flag2);

bool __thiscall PathEngine::lineOfSight(
    float* startPos,          // param_2: 2D start point (x,y)
    float* endPos,            // param_3: 2D end point (x,y)
    int startCell,            // param_4: index or handle of the cell containing startPos? (has float at +0x04)
    float* outPos,            // param_5: output intermediate position (4 floats)
    float* resultPos,         // param_6: output final position (copied from outPos on success)
    int maxDepth,             // param_7: recursion depth limit
    bool useExact,            // param_8: flag indicating exact/snapping mode
    float unknown             // param_9: some engine constant (passed through)
)
{
    // Find the cell that contains the line segment
    int cellIdx = findContainingCell(startPos, endPos, 0, unknown, *(float*)(startCell + 4));
    if (cellIdx == 0)
    {
        // No containing cell found; perform a virtual validation
        bool valid = (**(bool (__thiscall**)(PathEngine*, int, float*))(this + 0xa8))(this, startCell, outPos);
        if (!valid)
        {
            // The segment is not obstructed: copy outPos to resultPos
            resultPos[0] = outPos[0];
            resultPos[1] = outPos[1];
            resultPos[2] = outPos[2];
            resultPos[3] = outPos[3];
            return true;
        }
    }
    else if (maxDepth > 0)
    {
        // Compute distances from endPos to the cell's center
        float dx = endPos[0] - *(float*)(cellIdx + 0x10);
        float dy = endPos[1] - *(float*)(cellIdx + 0x14);
        float radiusSq = *(float*)(cellIdx + 0x18) * *(float*)(cellIdx + 0x18);
        bool insideRadius = (dx*dx + dy*dy) <= radiusSq;

        // Get the intermediate point on the cell boundary
        float intermediate[2];
        float* pIntermediate = getIntermediatePoint(
            (float*)&intermediate,
            startPos,
            endPos,
            cellIdx,
            unknown,
            0,
            useExact,
            0
        );
        float midX = pIntermediate[0];
        float midY = pIntermediate[1];

        float cellHeight = *(float*)(startCell + 4);  // +0x04: height or distance threshold?
        float heightDiff = (float)outPos[1] - cellHeight; // param_5[1] is the original? Might be output z?

        // Global constants for height clamping (likely min/max height difference)
        extern const float HEIGHT_MIN;  // DAT_00e2eff4
        extern const float HEIGHT_MAX;  // DAT_00e2b1a4

        if (heightDiff > HEIGHT_MAX || heightDiff < HEIGHT_MIN)
        {
            // Adjust the intermediate point proportionally based on distances
            float dy = startPos[1] - endPos[1];
            float dx = startPos[0] - endPos[0];
            float dy2 = startPos[1] - midY;
            float dx2 = startPos[0] - midX;
            float ratio = sqrtf((dx2*dx2 + dy2*dy2) / (dx*dx + dy*dy));
            cellHeight = ratio * heightDiff + cellHeight;
        }

        // Recursively check subsegments
        float subStart[2] = { midX, midY };
        float subEnd[2] = { midX, midY }; // Actually subEnd is the same point? The code passes &local_20 as end for first recursive call, which is a copy of subStart?
        // Looking at the assembly: local_20 = local_30; local_18 = local_2c; so both subStart and subEnd are the same point!
        // This is likely a bug or a trick: the function is called with start=mid, end=mid (zero-length), which might be an early-out condition.
        // We'll replicate the logic exactly.

        bool blocked = false;
        if (insideRadius)
        {
            // First subsegment: (mid -> endPos)  (actually call with start = mid, end = mid??)
            blocked = !lineOfSight(
                &midX,
                endPos,
                &midX,          // startCell? This is weird, passing &midX as the cell pointer
                outPos,
                resultPos,
                maxDepth - 1,
                !useExact,      // param_8 toggled
                unknown
            );
        }
        if (!blocked)
        {
            // Second subsegment: (startPos -> mid)
            blocked = !lineOfSight(
                startPos,
                &midX,
                startCell,      // original cell handle
                &midX,          // outPos? Actually third argument is the cell handle, but code passes &midX as param_4?
                resultPos,
                maxDepth - 1,
                !useExact,
                unknown
            );
        }
        if (blocked)
        {
            // Recursion failed; try alternative projection without snapping
            pIntermediate = getIntermediatePoint(
                (float*)&intermediate,
                startPos,
                endPos,
                cellIdx,
                unknown,
                0,
                !useExact,      // toggled useExact
                0
            );
            midX = pIntermediate[0];
            midY = pIntermediate[1];
            subStart[0] = midX;
            subStart[1] = midY;
            subEnd[0] = midX;
            subEnd[1] = midY;

            if (insideRadius)
            {
                blocked = !lineOfSight(
                    &midX,
                    endPos,
                    &midX,
                    outPos,
                    resultPos,
                    maxDepth - 1,
                    useExact,       // original useExact (not toggled)
                    unknown
                );
                if (blocked)
                    return false;
            }
            blocked = !lineOfSight(
                startPos,
                &midX,
                startCell,
                &midX,
                resultPos,
                maxDepth - 1,
                useExact,
                unknown
            );
            if (blocked)
                return false;
        }
        // If we reach here, both subsegments passed
        return true;
    }
    return false;
}