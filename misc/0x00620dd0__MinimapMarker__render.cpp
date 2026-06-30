// FUNC_NAME: MinimapMarker::render
void MinimapMarker::render(void)
{
    // this pointer in ESI
    float distance; // local_38
    int screenX; // local_34 (actually undefined4, but used as float later)
    int screenY; // local_2c? Actually local_2c is used as parameter but not directly used later
    // local_24 is a byte (char)
    // local_28, local_30, local_2c are outputs from worldToScreen
    // local_20, local_1c, local_18 are colors or values
    // local_14 is from +0x3c (type)
    // local_10, local_c, local_8 are zeros

    char visible = *(char *)(this + 0xc0); // m_visible
    int type = *(int *)(this + 0x3c); // m_type
    int someFlag = *(int *)(this + 0xac); // m_hasSecondaryIcon

    // Default color/alpha values
    int defaultColor = DAT_00e2b1a4; // 0xFFFFFFFF
    int color1 = DAT_00e2b04c;
    int color2 = DAT_00e2b050;

    // Local variables for worldToScreen output
    char outVisible; // local_24
    int outScreenX; // local_28
    int outScreenY; // local_2c
    float outDistance; // local_38
    int outSomething1; // local_30
    int outSomething2; // local_34? Actually local_34 is used as screenX later

    // Initialize locals
    outVisible = 0;
    outScreenX = 0;
    outScreenY = 0;
    outDistance = 0.0f;
    outSomething1 = 0;
    outSomething2 = 0;

    // If the object's visible flag is zero, use global visibility override
    if (visible == '\0') {
        visible = DAT_01205887; // global visibility flag
    }

    // Call world-to-screen conversion
    FUN_005e5270(&outVisible, &outScreenX, &outScreenY, &outDistance, &outSomething1, &outSomething2);

    // Begin rendering (push matrix)
    FUN_00c9eac0();

    // Conditional secondary icon drawing
    if ((someFlag != 0) &&
        (outDistance = outDistance * DAT_00e44748, outDistance <= DAT_00e2af34) &&
        (DAT_00e2b05c <= outDistance))
    {
        FUN_00ca4e90(0, outDistance); // draw secondary icon
    }

    // Always draw primary icon
    FUN_00ca4e90(0, outScreenX); // note: outScreenX is actually the float from local_34? Wait, local_34 is used as float in the call? Actually the decompiled code uses local_34 as the second argument to FUN_00ca4e90 after the conditional. local_34 was set to DAT_00e2b1a4 initially, but then overwritten by the worldToScreen call? Let's check: In the decompiled, local_34 is set to DAT_00e2b1a4, then later passed as &local_34 to FUN_005e5270. So after that call, local_34 contains the output value (likely screen X or something). Then it is used in FUN_00ca4e90(0, local_34). So local_34 is the screen X coordinate (float). Similarly, local_38 is the distance. So we should rename accordingly.

    // Actually, let's re-evaluate: The decompiled code shows:
    // local_34 = DAT_00e2b1a4;
    // local_38 = 0.0;
    // local_2c = DAT_00e2b1a4;
    // local_30 = 0;
    // local_28 = 0;
    // FUN_005e5270(&local_24,&local_28,&local_34,&local_38,&local_2c,&local_30);
    // So the parameters are: &local_24 (char), &local_28 (int), &local_34 (float), &local_38 (float), &local_2c (float), &local_30 (int).
    // After call, local_34 is screen X (float), local_38 is distance (float), local_2c is screen Y (float), local_28 is something, local_30 is something.
    // Then later: local_38 = local_38 * DAT_00e44748; and used in conditional.
    // Then FUN_00ca4e90(0,local_38); and FUN_00ca4e90(0,local_34);
    // So local_34 is the screen X coordinate, local_38 is distance.

    // So we should rename:
    // local_34 -> screenX
    // local_38 -> distance
    // local_2c -> screenY
    // local_28 -> something (maybe screenWidth?)
    // local_30 -> something

    // But in the code above, I used outScreenX for local_28, which is wrong. Let's correct.

    // Let's rewrite with proper variable names.
}

// Actually, let's produce a clean version with correct variable names.

void MinimapMarker::render(void)
{
    // this pointer in ESI
    char visible = *(char *)(this + 0xc0); // m_visible
    int type = *(int *)(this + 0x3c); // m_type
    int hasSecondary = *(int *)(this + 0xac); // m_hasSecondaryIcon

    // Outputs from worldToScreen
    char outVisible; // local_24
    int outSomething1; // local_28 (maybe screen width or something)
    float screenX; // local_34
    float distance; // local_38
    float screenY; // local_2c
    int outSomething2; // local_30

    // Initialize
    outVisible = 0;
    outSomething1 = 0;
    screenX = DAT_00e2b1a4; // default color? Actually it's overwritten
    distance = 0.0f;
    screenY = DAT_00e2b1a4; // default color? Overwritten
    outSomething2 = 0;

    // If object's visible flag is zero, use global visibility
    if (visible == '\0') {
        visible = DAT_01205887;
    }

    // Convert world position to screen coordinates
    FUN_005e5270(&outVisible, &outSomething1, &screenX, &distance, &screenY, &outSomething2);

    // Begin rendering (push matrix)
    FUN_00c9eac0();

    // Draw secondary icon if conditions met
    if ((hasSecondary != 0) &&
        (distance = distance * DAT_00e44748, distance <= DAT_00e2af34) &&
        (DAT_00e2b05c <= distance))
    {
        FUN_00ca4e90(0, distance); // draw secondary icon at distance
    }

    // Always draw primary icon at screen position
    FUN_00ca4e90(0, screenX); // note: screenX is actually the X coordinate? Or is it a size? The function takes a float, likely a size or distance. But based on context, it's probably the screen X coordinate. However, the second parameter is a float, so it could be a size or distance. Given the first call uses distance, the second uses screenX, which might be the screen X coordinate. But the function name "drawIcon" might take a position or size. We'll keep as is.

    // End rendering (pop matrix)
    FUN_00c9eae0();
}