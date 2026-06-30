// FUNC_NAME: EasingCurve::evaluate
// Function at 0x004edf00: Evaluates a multi-segment easing curve with 3 keyframes (4 control points) and 6 states.
// The curve is defined by keyframe[0..4] (time thresholds) and keyframe[5..7] (values at those points).
// The state machine transitions through segments: wait, lerp to mid, hold, lerp to end, hold, loop/reset.
// Global variables: g_timestep (0xe2eff4) and g_oneMinusT (0xe2b1a4) used for lerp weighting.

void __thiscall EasingCurve::evaluate(float *thisState, float *keyframe, void *externalObj, bool resetFlag)
{
    // thisState[0] = currentTime
    // thisState[1] = currentValue (output)
    // thisState[2] = state (stored as float with integer values 1-6, represented as subnormal floats)
    // keyframe[0] = t0 (start first segment)
    // keyframe[1] = t1 (end first segment / start second)
    // keyframe[2] = t2 (end second / start third)
    // keyframe[3] = t3 (end third)
    // keyframe[4] = t4 (end hold? or final)
    // keyframe[5] = v0 (value at t0)
    // keyframe[6] = v1 (value at t1)
    // keyframe[7] = v2 (value at t2)
    // externalObj+0x44 is a float compared in state 5 (likely an external position or timer)

    float t = thisState[0];
    float &value = thisState[1];
    int state = reinterpret_cast<int &>(thisState[2]); // stored as float bits, but used as int enum

    switch (state)
    {
    case 1: // Wait until currentTime reaches keyframe[0]
        if (t <= keyframe[0])
        {
            value = keyframe[5];
            return;
        }
        if (g_timestep < keyframe[1]) // if first segment has positive duration
        {
            thisState[2] = 2.0f; // move to lerp state
            thisState[0] = 0.0f;
            return;
        }
        // if first segment duration is zero, skip to next
        if (keyframe[2] <= g_timestep) // check if second segment exists
        {
            // fall through to state 3 (hold at v1)
            goto setState3AndReset;
        }
        break; // else go to state 3? Actually the code falls through to state 3 after resetting time

    case 2: // Lerp from v0 to v1 over duration keyframe[1]
        {
            float duration = keyframe[1];
            if (t <= duration)
            {
                float ratio = (duration > 0.0f) ? (t / duration) : 0.0f;
                value = g_oneMinusT * keyframe[5] + ratio * keyframe[6]; // actually (1-ratio)*v0 + ratio*v1
                return;
            }
        }
        break; // exceeded duration, fall through to state 3

    case 3: // Hold at v1? (no interpolation, just set value = keyframe[6])
        if (t >= keyframe[2] && t != keyframe[2]) // if currentTime beyond keyframe[2] (not equal)
        {
            if (g_timestep < keyframe[3]) // if second segment has duration
            {
                thisState[2] = 4.0f;
                thisState[0] = 0.0f;
                return;
            }
            if (g_timestep < keyframe[4]) // if third segment has duration
            {
                thisState[2] = 5.0f;
                thisState[0] = 0.0f;
                return;
            }
            goto setState6AndReset; // no more segments, go to final state
        }
        value = keyframe[6]; // hold at middle value
        return;

    case 4: // Lerp from v1 to v2 over duration keyframe[3]
        {
            float duration = keyframe[3];
            if (t <= duration)
            {
                float ratio = (duration > 0.0f) ? (t / duration) : 0.0f;
                value = g_oneMinusT * keyframe[6] + ratio * keyframe[7];
                return;
            }
        }
        // exceeded duration, check if third segment exists
        if (g_timestep < keyframe[4])
        {
            thisState[2] = 5.0f;
            thisState[0] = 0.0f;
            return;
        }
        // else fall through to state 6
        goto setState6AndReset;

    case 5: // Hold at v2 until external condition is met
        {
            float externalVal = *(float *)((char *)externalObj + 0x44);
            if (externalVal <= keyframe[4] || externalVal == keyframe[4])
            {
                value = keyframe[7];
                return;
            }
        }
        // fall through to state 6
        goto setState6AndReset;

    case 6: // Reset/loop state
        if (!resetFlag)
            return;
        // Check if we should restart
        if (g_timestep < keyframe[0]) // restart from wait state
        {
            thisState[2] = 1.0f;
            // then set value = keyframe[5] (falls into label)
            goto setValue0;
        }
        if (g_timestep < keyframe[1])
        {
            // restart from lerp state
            float v0 = keyframe[5];
            thisState[2] = 2.0f;
            thisState[1] = v0;
            return;
        }
        if (keyframe[2] <= g_timestep) // if second segment is valid, go to state 3
        {
            thisState[2] = 3.0f;
        }
        // else stay in state 6? Actually the code falls through to set time=0 and return
        // default behavior: reset time and continue
        break;

    default:
        return;
    }

    // Common fallthrough: set state to 3 and reset time
setState3AndReset:
    thisState[2] = 3.0f;
setState3AndResetTime:
    thisState[0] = 0.0f;
    return;

setState6AndReset:
    thisState[2] = 6.0f;
    thisState[0] = 0.0f;
    return;

setValue0:
    value = keyframe[5];
    return;
}