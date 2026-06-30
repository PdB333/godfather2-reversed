// FUNC_NAME: TrailEffect::renderRibbon

void __thiscall TrailEffect::renderRibbon(void *this, void *pScene, char *pMaterial)
{
    // Early out if material is invalid or ribbon is disabled
    if (((*pMaterial == '\0') || (*(int *)(pMaterial + 4) == 0)) ||
        (*(char *)(*(int *)(pMaterial + 4) + 0x1e) != '\0'))
    {
        // Retrieve render data block (offset +0x20 in this)
        void *pRenderData = *(void **)((int)this + 0x20);
        uint flags = *(uint *)((int)pRenderData + 0x14); // +0x14: flags

        // Index into animation frame table using scene data (+0x16c)
        void *pAnimFrame = nullptr;
        if (*(uint *)((int)pScene + 0x16c) < 0x1000)
        {
            pAnimFrame = &DAT_011a0f28 + *(uint *)((int)pScene + 0x16c) * 0x38;
        }

        float scaleX, scaleY, baseAngle;
        if ((flags & 8) == 0)
        {
            // Standard material-driven scaling
            baseAngle = *(float *)((int)pRenderData + 0x30); // +0x30: some angle offset
            scaleX = *(float *)(pMaterial + 0x28);          // +0x28: material scale X
            scaleY = *(float *)(pMaterial + 0x2c);          // +0x2c: material scale Y
        }
        else
        {
            // Animation frame-driven scaling
            scaleX = (float)*(unsigned short *)((int)pAnimFrame + 2) * (DAT_00e44564 - _DAT_01218dc0);
            scaleY = (float)*(unsigned short *)((int)pAnimFrame + 4) * DAT_01218dd4;
            baseAngle = DAT_00e2cd54;
        }

        // Compute ribbon size
        float sizeX = scaleX * baseAngle;
        float sizeY = scaleY * baseAngle;

        // Compute ribbon start and end positions from material and render data
        float posX = *(float *)(pMaterial + 0x20) * *(float *)((int)pRenderData + 0x2c) + *(float *)(pMaterial + 0x18);
        float posY = *(float *)(pMaterial + 0x24) * *(float *)((int)pRenderData + 0x2c) + *(float *)(pMaterial + 0x1c);

        // Compute width scaling from this object's width factor and material width
        float width = *(float *)((int)this + 0x28) * *(float *)(pMaterial + 0xc); // +0x28: object width multiplier
        if ((*(byte *)((int)pRenderData + 0x14) & 0x10) != 0)
        {
            width *= *(float *)(pMaterial + 0x10); // additional material width mod
        }
        if ((flags & 0x20) != 0)
        {
            width *= *(float *)(pMaterial + 0x14); // another width mod
        }

        // Skip if width is below threshold
        if (DAT_00e2af44 < width)
        {
            // Build initial color from render data (+0x28)
            uint color1 = *(uint *)((int)pRenderData + 0x28); // +0x28: base color (RGBA uint)

            // Angle for twisting/ribbon orientation
            float twistAngle = *(float *)((int)pRenderData + 0x38) * *(float *)(pMaterial + 8) +
                               *(float *)((int)pRenderData + 0x34) * DAT_00e445c8;

            // Alpha scaled by width (alpha from render data +0x2b)
            uint alpha = (uint)(*(byte *)((int)pRenderData + 0x2b) * width);
            color1 = alpha | ((color1 << 0x10 | color1 & 0xff00 | color1 >> 0x10 & 0xff) << 8);

            // Check ribbon type (single vs multi-segment)
            if (*(char *)((int)pRenderData + 0x10) == '\0')
            {
                // Single segment (simple line/quad)
                if (*(int *)((int)this + 0x24) != 0) // texture present
                {
                    // Premultiply colors by global factor
                    float colR = (float)(color1 >> 0x18) * DAT_00e44640;
                    float colG = (float)(color1 >> 0x10 & 0xff) * DAT_00e44640;
                    float colB = (float)(color1 >> 8 & 0xff) * DAT_00e44640;
                    float colA = (float)(color1 & 0xff) * DAT_00e44640;

                    // Call the simple render function
                    FUN_005071d0(&colR, posX, posY, 0x3f800000, 0x3f800000, twistAngle,
                                 *(float *)((int)pRenderData + 0x20) * sizeX,
                                 *(float *)((int)pRenderData + 0x20) * sizeY,
                                 *(int *)((int)this + 0x24), flags >> 7 & 0xffffff01);
                }
            }
            else
            {
                // Multi-segment ribbon
                uint color2 = *(uint *)((int)pRenderData + 0x24); // +0x24: secondary color

                // Compute segment count from render data byte at +0x11
                float segCount;
                if (*(byte *)((int)pRenderData + 0x11) < 4)
                {
                    segCount = 4.2039e-45f; // effectively zero
                }
                else if (*(byte *)((int)pRenderData + 0x11) < 0x20)
                {
                    segCount = (float)*(byte *)((int)pRenderData + 0x11);
                }
                else
                {
                    segCount = 4.48416e-44f; // effectively zero
                }

                if (*(char *)((int)pRenderData + 0x10) == '\x02')
                {
                    segCount = (float)((int)segCount + 1U & 0xfffffffe); // make even
                }

                // Setup render state for ribbon
                FUN_00536800();

                // Set global effect parameters from this object's +0x1e (two 4-bit values)
                _DAT_0121a2a0 = (float)(*(byte *)((int)this + 0x1e) & 0xf) * DAT_00e2e638;
                _DAT_0121a2a4 = (float)(*(byte *)((int)this + 0x1e) >> 4) * DAT_00e2e638;
                _DAT_0121a2a8 = 0;
                _DAT_0121a2ac = 0;

                // Set ribbon orientation offsets
                float offsetX = DAT_01218e44 * DAT_00e2b04c;
                float offsetY = DAT_01218e48 * DAT_00e2b04c;

                // Save position and size for vertex generation
                float startX = posX;
                float startY = posY;
                float sizeXcopy = sizeX;
                float sizeYcopy = sizeY;

                // Process material texture if available
                if (*pMaterial != '\0')
                {
                    void *pMatData = *(void **)(pMaterial + 4);
                    float texU = ((float)*(byte *)((int)pMatData + 0x1c) + DAT_00e2cd54) * DAT_00e445e4;
                    float texV = ((float)*(byte *)((int)pMatData + 0x1d) + DAT_00e2cd54) * DAT_00e2ee80;
                    if (DAT_0120575b == '\0')
                    {
                        _DAT_0121a300 = *(undefined4 *)((int)pMatData + 0x24);
                    }
                    else
                    {
                        FUN_00536990();
                    }
                }

                FUN_00536ad0();
                FUN_00536550();

                // Allocate vertex buffer: (segmentCount*2 + 2) vertices, each 6 floats (color, width, angle)*2
                int vertexCount = (int)segCount * 2 + 2;
                float *pVertexBuffer = (float *)FUN_0060cd00(5, vertexCount, 0, 1, 0);
                if (pVertexBuffer != nullptr)
                {
                    // Global constants for angle clamping
                    float angleMin = DAT_00e44934;
                    float angleMax = DAT_00e44930;
                    float angleRange = DAT_00e44760;

                    float angleStep = angleRange / (int)segCount;
                    uint idx = 0;
                    float *pVert = pVertexBuffer + 2; // skip allocation header? (iVar3 + 8)
                    do
                    {
                        float angle = twistAngle;
                        if ((0 < idx) && ((int)idx < (int)segCount))
                        {
                            angle = (float)idx * angleStep + twistAngle;
                        }

                        // Wrap angle into valid range
                        if (angleMin <= angle)
                        {
                            if (angleMax < angle)
                            {
                                angle -= angleRange;
                            }
                        }
                        else
                        {
                            angle += angleRange;
                        }

                        // Determine widths for this ribbon segment (alternating based on flag)
                        pRenderData = *(void **)((int)this + 0x20);
                        float width1, width2;
                        if (*(char *)((int)pRenderData + 0x10) == '\x02')
                        {
                            width1 = 0.0f;
                            if ((idx & 1) != 0)
                            {
                                width2 = *(float *)((int)pRenderData + 0x20); // +0x20: secondary width
                            }
                            else
                            {
                                width1 = *(float *)((int)pRenderData + 0x1c); // +0x1c: primary width
                            }
                        }
                        else
                        {
                            width1 = *(float *)((int)pRenderData + 0x1c);
                            width2 = *(float *)((int)pRenderData + 0x20);
                        }

                        // Set vertex data: two vertices per segment
                        // Vertex 1: color (swapped), width1, angle
                        *(uint *)&pVert[-2] = (color2 & 0xff0000 | color2 >> 0x10) >> 8 |
                                              (color2 << 0x10 | color2 & 0xff00) << 8;
                        pVert[-1] = width1;
                        pVert[0] = angle;

                        // Vertex 2: color (swapped), width2, angle
                        *(uint *)&pVert[1] = (color1 & 0xff0000 | color1 >> 0x10) >> 8 |
                                              (color1 & 0xff00 | color1 << 0x10) << 8;
                        pVert[2] = width2;
                        pVert[3] = angle;

                        idx++;
                        pVert += 6; // two vertices (6 floats) per iteration
                    } while ((int)idx <= (int)segCount);
                }

                FUN_0060cde0(); // free allocated buffer?
                FUN_00612e00(); // submit draw call
                // Clear temporary globals
                _DAT_0121a310 = 0;
                _DAT_0121a314 = 0;
                _DAT_0121a318 = 0;
            }
        }
    }
    return;
}