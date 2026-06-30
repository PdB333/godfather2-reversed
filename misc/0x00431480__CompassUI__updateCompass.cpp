// FUNC_NAME: CompassUI::updateCompass
void CompassUI::updateCompass(void *thisPtr, float alpha, int x, int y, int w, int h) // approximate signature
{
    // 0x00431480
    // This function updates the compass overlay: calculates angle to target, sets rendering params, draws compass arc and pointer.

    // Push render state
    FUN_0041fee0();

    // Check if compass element is enabled (bit test at offset 0x3af8)
    bool compassEnabled = (*(uint *)((int)thisPtr + 0x3af8) >> 4) & 1;
    uint distanceToTarget;
    if (compassEnabled)
    {
        // Compute distance to target from vectors at offsets +0x28 (player pos) and +0x38 (target pos)
        distanceToTarget = FUN_0042cd20((int)thisPtr, (int)thisPtr + 0x28, (int)thisPtr + 0x38, 1);
    }
    else
    {
        distanceToTarget = 0xffffffff;
    }

    // Save previous colors
    int prevColor1 = DAT_011f38f0;
    int prevColor2 = DAT_011f38f4;

    // Determine texture to use: normally defaultTexture, but if special condition use alternative
    int currentTexture = DAT_012118c0; // default compass texture
    if (*(int *)(*(int *)(DAT_012233a8 + 4) + 0x39f8) != 0) // check some global state
    {
        currentTexture = DAT_0120536c; // alternative texture (maybe for certain missions)
    }

    // Set new colors to 0 (transient)
    DAT_011f38f4 = 0;
    DAT_011f38f0 = currentTexture; // store texture as color? Possibly texture ID packed

    // Set base color (RGBA) for the compass
    FUN_00609340(0, prevColor1, prevColor2); // restore or set

    // Some flag: whether target is very near (distance < 49)
    bool targetNear = (distanceToTarget < 0x31);

    // Draw background of compass with some alpha and color
    float alphaVal = (targetNear) ? 0.0f : *(float *)&DAT_00e2b1a4; // if near, use 0 alpha; else use global value
    FUN_00609730(1.0f, alphaVal, 1.0f, 1.0f, 1.0f, 0.0f); // set blend color (RGBA + unknown)
    FUN_00609810(0xf); // set blend mode

    // Draw the compass background arc (semi-transparent)
    FUN_00609730(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Store current texture for later
    DAT_012058f4 = currentTexture;

    // If there is a user-defined compass callback, call it
    if ((DAT_012058e8 != 0) && (*(int *)(DAT_012058e8 + 0xa0) != 0))
    {
        FUN_006063b0(); // likely user callback
    }

    // Clamp compass area top and bottom
    if (DAT_012058d0 < 7)
        DAT_012058d0 = 7;
    if (DAT_00f15988 < 7)
        DAT_00f15988 = 7;
    DAT_011f39f4 = 0;
    if (DAT_012058d0 < 22)
        DAT_012058d0 = 22;
    if (DAT_00f15988 < 22)
        DAT_00f15988 = 22;
    DAT_011f3a30 = 1;

    // Get current target data (angle/distance) from game
    int targetAngle = 0;
    int targetDistance = 0;
    FUN_00431280(&targetAngle, &targetDistance, (int *)&alpha, (int)thisPtr); // parameters: &outAngle, &outDist, &someFlag, this

    // Determine if compass pointer should be drawn (if within range)
    bool pointerVisible = false;
    if ((DAT_01205358 != 0) || (*(int *)((int)thisPtr + 0x39f8) == 1))
    {
        int distanceFromPlayer = FUN_0042cd20((int)thisPtr, (int)thisPtr + 4, (int)thisPtr + 0x14, 0);
        if ((*(int *)((int)thisPtr + 0x24) + distanceFromPlayer) >= 0x500)
        {
            pointerVisible = true;
        }
    }

    // Update alpha flag with pointer visibility
    int renderFlags = (int)alpha;
    renderFlags = (renderFlags & 0xffffff00) | (pointerVisible ? 1 : 0);

    // Draw the compass elements
    if ((!targetNear) && (DAT_012053c9 == 0))
    {
        // Full compass draw (arc + pointer)
        FUN_0042aca0(); // push transform
        FUN_00431320(x, y, w, h, currentTexture, 0, targetAngle, 1, 0); // draw arc
        FUN_00619210(); // pop transform? or restore?
        FUN_0042aca0(); // push again
        FUN_00431320(x, y, w, h, currentTexture, 0, targetAngle, 0, 0); // draw pointer
        // note: seems reversed? but okay
    }
    else
    {
        if (pointerVisible)
        {
            FUN_0042ac10(); // some different push
        }
        FUN_00431320(x, y, w, h, currentTexture, targetNear, targetAngle, 0, 0);
        if (pointerVisible)
        {
            FUN_00619210(); // pop
        }
    }

    // Clamp compass area left and right (first pass)
    if (DAT_012058d4 < 168)
        DAT_012058d4 = 168;
    if (DAT_00f1598c < 168)
        DAT_00f1598c = 168;
    DAT_011f3c78 = 15;

    // Second pass: wider area
    if (DAT_012058d4 < 190)
        DAT_012058d4 = 190;
    if (DAT_00f1598c < 190)
        DAT_00f1598c = 190;
    DAT_011f3cd0 = 15;

    // Finalize rendering
    FUN_00609890(1);

    // Draw compass border or additional elements
    FUN_0042b5d0(currentTexture, DAT_00e2e638, DAT_0110ac34, *(int *)&DAT_00e2e63c, 1, 1, renderFlags);

    // Restore compass area bounds
    if (DAT_012058d0 < 22)
        DAT_012058d0 = 22;
    if (DAT_00f15988 < 22)
        DAT_00f15988 = 22;
    DAT_011f3a30 = 2;

    if (DAT_012058d0 < 7)
        DAT_012058d0 = 7;
    DAT_011f39f4 = 1;
    if (DAT_00f15988 < 7)
        DAT_00f15988 = 7;
}