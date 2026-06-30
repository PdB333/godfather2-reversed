// FUNC_NAME: UIRenderer::drawSpriteWithShadow

void __thiscall UIRenderer::drawSpriteWithShadow(
    int thisPtr,                    // +0x00 this
    float x,                        // param_2: screen X
    float y,                        // param_3: screen Y
    unsigned int width,             // param_4: sprite width (pass-through)
    unsigned int height,            // param_5: sprite height (pass-through)
    float scaleOrAlpha,             // param_6: requested scale/alpha (multiplied by internal scale +0x44)
    const char* textureName,        // param_7: texture path or name
    unsigned int colorOrHandle,     // param_8: maybe color or shader handle
    float* outlineHalfSize,         // param_10: pointer to (offsetX, offsetY) for outline/shadow
    bool drawOutline,               // param_11: if true, draw outline with multiple copies
    const unsigned int* outlineColor, // param_12: optional pointer to ARGB color for outline
    unsigned int param13,           // param_13: pass-through to draw
    unsigned int param14,           // param_14: pass-through
    unsigned int param15,           // param_15: pass-through
    unsigned int param16,           // param_16: pass-through
    unsigned int param17            // param_17: pass-through
)
{
    // +0x44: internal scale factor applied to scaleOrAlpha
    float scaledAlpha = *(float*)(thisPtr + 0x44) * scaleOrAlpha;

    // +0x1c: some handle (e.g., a context or render target)
    // +0x54: flag whether to push/pop state
    // +0x58: some identifier for state push/pop
    // +0x40: function pointer to resolve texture name

    if (*(int*)(thisPtr + 0x1c) != 0 && textureName != NULL)
    {
        // Push state if not already inside a push
        if (*(int*)(thisPtr + 0x54) == 0)
        {
            FUN_00489bc0(*(unsigned char*)(thisPtr + 0x58)); // push state
        }

        // Resolve texture name via callback (e.g., path conversion)
        if (*(void (__stdcall**)(const char*, char*, int, int))(thisPtr + 0x40) != NULL)
        {
            char resolvedName[2052]; // 0x804 bytes
            char success = (**(int (__stdcall**)(const char*, char*, int, int))(thisPtr + 0x40))
                (textureName, resolvedName, 0x800, 0);
            if (success != 0)
            {
                textureName = resolvedName;
            }
        }

        // Save current global vertex colors (for four corners)
        unsigned int savedColor0 = g_vertexColors[0]; // DAT_01163d98
        unsigned int savedColor1 = g_vertexColors[1]; // DAT_01163d9c
        unsigned int savedColor2 = g_vertexColors[2]; // DAT_01163da0
        unsigned int savedColor3 = g_vertexColors[3]; // DAT_01163da4

        // If outline half-size provided and non-zero
        if (outlineHalfSize != NULL && (outlineHalfSize[0] != 0.0f || outlineHalfSize[1] != 0.0f))
        {
            float offsetX = outlineHalfSize[0] + x;
            float offsetY = outlineHalfSize[1];

            if (outlineColor == NULL)
            {
                // No specific outline color: set vertex colors to opaque black (shadow)
                g_vertexColors[0] = 0xFF000000;
                g_vertexColors[1] = 0xFF000000;
                g_vertexColors[2] = 0xFF000000;
                g_vertexColors[3] = 0xFF000000;
            }
            else
            {
                // Use provided outline color for all corners
                g_vertexColors[0] = *outlineColor;
                g_vertexColors[1] = *outlineColor;
                g_vertexColors[2] = *outlineColor;
                g_vertexColors[3] = *outlineColor;
            }

            if (!drawOutline)
            {
                // Single sprite draw (no outline copies)
                FUN_0048aa50(
                    thisPtr,
                    *(unsigned int*)(thisPtr + 0x1c),
                    offsetX, y,
                    width, height, scaledAlpha, textureName, colorOrHandle, 1,
                    param13, param14, param15, param16, param17
                );
            }
            else
            {
                // Draw outline copies: 4 cardinal directions
                float dx = outlineHalfSize[0];
                float dy = outlineHalfSize[1];
                float diag = 0.70710678f; // approx sqrt(2)/2, kHalfSqrt2

                // Right
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), x + dx, y, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);
                // Left
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), x - dx, y, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);
                // Down
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), x, y + dy, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);
                // Up
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), x, y - dy, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);

                // Diagonal directions (scaled by 0.7071)
                float dxDiag = dx * diag;
                float dyDiag = dy * diag;
                // Down-Right
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), x + dxDiag, y - dyDiag, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);
                // Up-Left
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), x - dxDiag, y + dyDiag, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);
                // Down-Left
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), x + dxDiag, y + dyDiag, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);
                // Up-Right
                offsetX = x - dxDiag;
                offsetY = dyDiag;
                FUN_0048aa50(thisPtr, *(unsigned int*)(thisPtr + 0x1c), offsetX, y - offsetY, width, height, scaledAlpha, textureName, colorOrHandle, 1, param13, param14, param15, param16, param17);
            }
        }

        // Restore saved vertex colors for the main sprite
        g_vertexColors[0] = savedColor0;
        g_vertexColors[1] = savedColor1;
        g_vertexColors[2] = savedColor2;
        g_vertexColors[3] = savedColor3;

        // Draw the main sprite at original position (with 0 = no outline effect)
        FUN_0048aa50(
            thisPtr,
            *(unsigned int*)(thisPtr + 0x1c),
            x, y,
            width, height, scaledAlpha, textureName, colorOrHandle, 0,
            param13, param14, param15, param16, param17
        );

        // Pop state if we pushed earlier
        if (*(int*)(thisPtr + 0x54) == 0)
        {
            FUN_00489d60(*(unsigned char*)(thisPtr + 0x58)); // pop state
        }
    }
}