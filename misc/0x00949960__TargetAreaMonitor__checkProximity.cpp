// FUNC_NAME: TargetAreaMonitor::checkProximity
// Address: 0x00949960
// Role: Checks if a target position is within a maximum distance from a source position,
// and toggles an internal flag (bit 25 at +0x11c) and calls associated notification functions.

void __thiscall TargetAreaMonitor::checkProximity(float *sourcePos, float *targetPos)
{
    // +0x124: maximumDistanceSquared (float) - squared threshold for "close enough"
    float maxDistSq = *(float *)(this + 0x124);
    
    // Global constant: likely a very large sentinel value (e.g., infinity)
    // Not resetting distance check if maxDistSq <= infinity
    if ((maxDistSq <= _DAT_00d577a0) ||
        // Compute squared distance between targetPos and sourcePos
        ((targetPos[2] - sourcePos[2]) * (targetPos[2] - sourcePos[2]) +
         (targetPos[1] - sourcePos[1]) * (targetPos[1] - sourcePos[1]) +
         (targetPos[0] - sourcePos[0]) * (targetPos[0] - sourcePos[0]) <= maxDistSq))
    {
        // If within range, and currently flagged as out-of-range (bit 25 set),
        // call the "entered range" notification and clear the flag.
        if ((*(uint *)(this + 0x11c) >> 0x19 & 1) != 0)  // check bit 25
        {
            FUN_00949850();  // notifyEnterRange()
            *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) & 0xfdffffff;  // clear bit 25
        }
    }
    else
    {
        // If out of range and currently flagged as in-range (bit 25 clear),
        // call the "exited range" notification and set the flag.
        if ((*(uint *)(this + 0x11c) >> 0x19 & 1) == 0)  // bit 25 not set
        {
            FUN_00949800();  // notifyExitRange()
            *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) | 0x2000000;  // set bit 25
        }
    }
    return;
}