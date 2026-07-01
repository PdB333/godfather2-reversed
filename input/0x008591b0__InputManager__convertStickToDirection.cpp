// FUNC_NAME: InputManager::convertStickToDirection
// Address: 0x008591b0
// Role: Converts analog stick input to an 8‑way direction (returns 0–7).
// Calls: InputManager::update (vtable+0x1c), InputManager::getStickNormalized (at 0x858ae0)

// Global thresholds (likely configurable deadzone/sensitivity values)
extern float DAT_00d58cbc;     // initial deadzone margin
extern float DAT_00d5f6e8;     // scaling factor for y-axis
extern float DAT_00d64bfc;     // scaling factor for x-axis
extern float DAT_00d6bfe4;     // edge threshold multiplier
extern float _DAT_00d577a0;    // upper bound for neutral state

// Returns direction as:
// 0 = neutral, 1 = up, 2 = up-right, 3 = right, 4 = down-right,
// 5 = down, 6 = down-left, 7 = left
// (or similar enumeration based on the game's rotation convention)
int InputManager::convertStickToDirection(int controllerIndex)
{
    int *vtablePtr;
    float x, y, edgeX, edgeY;
    float rawStick[5]; // output buffer from getStickNormalized

    vtablePtr = (int *)InputManager::getInstance(); // FUN_00546760 returns singleton
    rawStick[0] = DAT_00d58cbc; // initialize deadzone

    // Call virtual update function (vtable+0x1c) — probably InputManager::tick
    (*(void (**)(void *))(vtablePtr[0] + 0x1c))((void *)0x11397d0);

    // Retrieve normalized stick components (x,y?) into rawStick array
    InputManager::getStickNormalized(controllerIndex, &rawStick);

    // rawStick[0] = deadzone threshold? rawStick[1..4] = ??
    // Based on usage, assume:
    //   rawStick[0] = local_48  (x magnitude?)
    //   rawStick[1] = fStack_3c (edge threshold?)
    //   rawStick[2] = fStack_34 (y? or something)
    //   rawStick[3] = fStack_2c (x? or something)
    //   rawStick[4] = fStack_24 (y? or something)

    // unaff_ESI is a float that likely comes from the rawStick array,
    // probably y-component (rawStick[4]?). The decompiler aliased it.
    // Re‑introduce register variable for clarity.
    float yComponent = rawStick[4];        // unaff_ESI
    float xComponent = rawStick[3];        // fStack_2c? Or rawStick[0]?
    // But the code uses both rawStick[3] and rawStick[0] in comparisons.

    // First dead‑zone check: if yComponent * DAT_00d5f6e8 < yComponent? Hit condition always true?
    if (rawStick[4] * DAT_00d5f6e8 < yComponent)
    {
        return 0; // neutral
    }

    if (rawStick[2] * DAT_00d5f6e8 <= yComponent)
    {
        // Check x‑component against positive axis
        if (rawStick[3] * _DAT_00d64bfc < rawStick[0])
        {
            // Positive x side
            if (rawStick[4] * DAT_00d6bfe4 < yComponent)
            {
                return 1; // up (or up‑right)
            }
            if (rawStick[1] * DAT_00d6bfe4 <= yComponent)
            {
                return 3; // right
            }
            return 5; // down‑right
        }

        // Check x‑component against negative axis
        if (rawStick[0] < rawStick[1] * _DAT_00d64bfc)
        {
            // Negative x side
            if (rawStick[4] * DAT_00d6bfe4 < yComponent)
            {
                return 2; // up‑left
            }
            if (rawStick[1] * DAT_00d6bfe4 <= yComponent)
            {
                return 4; // left
            }
            return 6; // down‑left
        }

        // Inside central band – possibly neutral/up zone
        if (_DAT_00d577a0 <= yComponent)
        {
            return 0; // neutral (high y threshold)
        }
    }

    return 7; // fallback – down? (or other direction)
}