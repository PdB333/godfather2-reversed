// FUNC_NAME: TransitionEffect::processEvent

// Function at 0x007469c0 - Handles transition effect events (color fade, timing)
// Class: TransitionEffect (derived from EffectBase)
// Member offsets: +0x30 = m_currentTime (float), +0x50 = m_startValue, +0x54 = m_endValue,
//                 +0x58 = m_state (int), +0x5c = m_flags (int)
// Global constants: kFadeParam1 (DAT_00e44564), kFadeParam2 (DAT_00e4461c),
//                   kColorRampA (_DAT_00e518ec), kColorRampB (_DAT_00e518f0),
//                   kColorRampC (_DAT_00e518f4), kFadeThreshold1 (_DAT_00d63e78),
//                   kFadeThreshold2 (_DAT_00d5780c), kColorFactorA (_DAT_00d5f704)

unsigned char __thiscall TransitionEffect::processEvent(int thisPtr, int param2, int param3, int eventId, int param5)
{
    unsigned char result = 0;

    switch (eventId - 10) {
    case 0: // eventId == 10: likely EVENT_CHECK_START
        if ((*(int *)(thisPtr + 0x5c) == 0) ||                // m_flags == 0 (inactive)
            (*(int *)(thisPtr + 0x5c) == 0x48) ||             // m_flags == 0x48 (paused)
            ((int result1 = FUN_007079a0(),                    // some state query
              result1 != 0) &&
             ((int result2 = FUN_007079a0(),
               result2 != *(int *)(thisPtr + 0x58)))))        // state mismatch
        {
            return 1; // return true to allow transition
        }
        break;

    case 1: // eventId == 11: calculate color/channel 1
        result = FUN_00746920(
            DAT_00e44564 - *(float *)(thisPtr + 0x50),         // start offset
            *(float *)(thisPtr + 0x54) * DAT_00e4461c,        // end scaled
            _DAT_00e518ec);                                    // ramp curve A
        return result;

    case 2: // eventId == 12: calculate color/channel 2
        result = FUN_00746920(
            *(float *)(thisPtr + 0x54) * DAT_00e4461c,        // end scaled
            *(float *)(thisPtr + 0x54) * _DAT_00d5f704,       // end scaled by factor A
            _DAT_00e518f0);                                    // ramp curve B
        return result;

    case 3: // eventId == 13: calculate color/channel 3
        result = FUN_00746920(
            *(float *)(thisPtr + 0x54) * _DAT_00d5f704,       // end scaled by factor A
            *(float *)(thisPtr + 0x54),                        // end value
            _DAT_00e518f4);                                    // ramp curve C
        return result;

    case 4: // eventId == 14: time threshold check (fade in)
        if (_DAT_00d63e78 <= *(float *)(thisPtr + 0x30)) {
            return 1; // transition complete
        }
        break;

    case 5: // eventId == 15: time threshold check (fade out)
        if (_DAT_00d5780c <= *(float *)(thisPtr + 0x30)) {
            return 1; // transition complete
        }
        break;

    default:
        // Fallback to base class handler for unknown events
        result = FUN_004ac640(param2, param3, eventId, param5);
        break;
    }

    return result;
}