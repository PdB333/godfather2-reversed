// FUNC_NAME: AICarBehavior::evaluateSteeringDecision
// Address: 0x00765ec0
// Role: Determines steering direction relative to path segments using cross-product test.
// Returns a 32-bit value with low byte indicating turn direction (1=left, 0=right/straight)
uint __fastcall AICarBehavior::evaluateSteeringDecision( int this )
{
    // +0x5c likely m_pWorld or m_pPhysics
    int worldPtr = *(int *)(this + 0x5c);
    // +0x24cc: probably pointer to current path segment or obstacle list
    int pathSegment = *(int *)(worldPtr + 0x24cc);
    if ( pathSegment == 0 ) {
        pathSegment = 0;
    } else {
        pathSegment -= 0x48; // offset to start of segment structure
    }
    // +0x21dc: pointer to some state object (e.g., vehicle state)
    uint statePtr = *(uint *)(worldPtr + 0x21dc);
    char stateFlag = *(char *)(statePtr + 0x88); // +0x88: e.g., steering state (1=stop,2=left,4=right,8=straight)
    if ( stateFlag != 8 && stateFlag != 1 ) {
        // If not stopping or going straight
        if ( pathSegment != 0 ) {
            // Read target direction vector from state object (positions at +0x30, +0x38, +0x40)
            double targetX = *(double *)(statePtr + 0x38); // actually stored as double, cast to float
            float targetY = *(float *)(statePtr + 0x40);
            // Get two additional points from global waypoint system
            int waypointA = FUN_00471610(); // returns pointer to current waypoint segment A
            int waypointB = FUN_00471610(); // returns pointer to next waypoint segment B
            float fTargetX = (float)targetX;
            // Cross product: (targetX * (By - Ay)) - ((Bx - Ax) * targetY)
            float cross = fTargetX * ( *(float *)(waypointB + 0x38) - *(float *)(waypointA + 0x38) )
                         - ( *(float *)(waypointB + 0x30) - *(float *)(waypointA + 0x30) ) * targetY;
            if ( stateFlag == 4 ) {
                // Right turn: need to be above threshold
                if ( g_steeringThreshold <= cross ) {
                    goto setTurnLeft;
                }
            } else if ( stateFlag == 2 ) {
                // Left turn: need to be below zero
                if ( cross <= 0.0f ) {
                    // Set low byte to 1 (left turn indicator)
                    return (statePtr & 0xFFFFFF00) | 1;
                }
            }
            // If not satisfying turn conditions, return original with cleared low byte (no turn)
            return statePtr & 0xFFFFFF00;
        }
    }
setTurnLeft:
    // state is stop/straight, or cross condition satisfied for right turn: force low byte to 1
    return (statePtr & 0xFFFFFF00) | 1;
}