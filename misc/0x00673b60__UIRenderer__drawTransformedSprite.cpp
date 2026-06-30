// FUNC_NAME: UIRenderer::drawTransformedSprite
void UIRenderer::drawTransformedSprite(UIRenderer* renderer, uint textureId, void* parentSprite, char dx, char dy, bool isRecursive, uint flags) {
    bool doClip = (flags & 0x80) != 0;
    int clipState = 0;
    bool clipEnabled = true;

    if (doClip) {
        int* renderDevice = *(int**)(renderer + 0x180);
        int clipMin = renderDevice ? *(int*)(renderDevice + 0x28) : 0;
        if (clipMin && (*(short*)(clipMin + 0x38) > 1999 && *(short*)(clipMin + 0x38) < 0x7D3)) {
            clipEnabled = false;
        }
        if (clipEnabled || *(int*)(renderDevice + 0x20) != 0) {
            clipState = 1;
        }
        flags = (flags & 0xFF7E);
        doClip = false;
    }

    uint originalTextureId = *(ushort*)(renderer + 0x17C);
    FUN_00673ad0(1); // pushMatrix
    *(int*)(*(int*)(renderer + 0x180) + 0x94) = *(int*)(renderer + 0x148);
    *(int*)(*(int*)(renderer + 0x180) + 0x98) = *(int*)(renderer + 0x15C);

    int* sprite = nullptr;
    int spriteX = 0, spriteY = 0;

    if ((flags & 8) == 0) {
        textureId = FUN_00675740(); // getTextureId??
        textureId &= 0xFFFF;
        int* surface = *(int**)(*(int*)(renderer + 0x180) + 0x20);
        spriteX = 0;
        spriteY = 0;
        if (surface) {
            sprite = FUN_0067aba0(surface, textureId, &spriteX, &spriteY);
        } else {
            int* pool = *(int**)(*(int*)(renderer + 0x180) + 0xB4);
            sprite = FUN_00678100(pool, 0, 0, 0);
        }
    } else {
        int* surface = *(int**)(*(int*)(renderer + 0x180) + 0x20);
        spriteX = 0;
        spriteY = 0;
        if (surface) {
            sprite = FUN_0067aba0(surface, textureId, &spriteX, &spriteY);
        } else {
            int* pool = *(int**)(*(int*)(renderer + 0x180) + 0xB4);
            sprite = FUN_00678100(pool, 0, 0, 0);
        }
    }

    *(short*)(sprite + 0x76) = (short)textureId;
    if (parentSprite == nullptr) {
        *(short*)(renderer + 0x108) = (short)textureId;
    }
    *(int*)(renderer + 0x104) = (int)sprite;

    if (*(short*)(sprite + 0x36) < 0) { // negative indicates a sprite group?
        // Process child sprites (clip list)
        uint childFlags = *(uint*)(sprite + 100);
        ushort* childList = *(ushort**)(sprite + 0x58);
        *(int*)(sprite + 0x58) = 0;
        *(int*)(sprite + 100) = 0;
        int childSome = *(int*)(sprite + 0x68);
        *(int*)(sprite + 0x68) = 0;

        // Save parent state
        int savedX = *(int*)(renderer + 8);
        int savedY = *(int*)(renderer + 0x10);
        int savedZ = *(int*)(renderer + 0x124);
        int savedW = *(int*)(renderer + 0x128);
        int savedH = *(int*)(renderer + 0x14);
        int savedV = *(int*)(renderer + 0x14);

        uint localFlags = (byte)flags & 0x9D | 0xC;
        uint* childPtr = 0;
        if (*(int*)(renderer + 0x174) == 2) {
            localFlags = localFlags & 0xFDFE;
        }

        ushort* currentChild = childList;
        uint accumulatedMask = 0;
        int recursionCount = 0;

        do {
            ushort childWord = *currentChild;
            uint childData0 = (uint)childWord;
            uint childData1 = (uint)currentChild[1];
            accumulatedMask |= childData0;

            int offsetA, offsetB, offsetC, offsetD;
            if ((childWord & 1) == 0) {
                currentChild += 3;
            } else {
                currentChild += 4;
            }

            if ((childWord & 8) == 0) {
                if ((childWord & 0x40) == 0) {
                    if ((char)childWord >= 0) {
                        offsetA = 0x10000;
                        goto computeOffsets;
                    }
                    offsetA = (short)*currentChild * 4;
                    offsetB = (short)currentChild[1] * 4;
                    offsetC = (short)currentChild[2] * 4;
                    offsetD = (short)currentChild[3] * 4;
                    currentChild += 4;
                } else {
                    offsetA = (short)*currentChild * 4;
                    offsetC = 0;
                    offsetB = 0;
                    offsetD = (short)currentChild[1] * 4;
                    currentChild += 2;
                }
            } else {
                offsetA = (short)*currentChild * 4;
                currentChild += 1;
computeOffsets:
                offsetB = 0;
                offsetC = 0;
                offsetD = offsetA;
            }

            *(int*)(renderer + 8) = offsetA;
            *(int*)(renderer + 0xC) = offsetC;
            *(int*)(renderer + 0x10) = offsetB;
            *(int*)(renderer + 0x14) = offsetD;

            if ((offsetA == 0x10000) && (offsetC == 0) && (offsetB == 0) && (offsetD == 0x10000)) {
                *(int*)(renderer + 0x1C) = 1;
            } else {
                *(int*)(renderer + 0x1C) = 0;
            }

            // Recursive call for child sprite
            drawTransformedSprite(renderer, childData1, (void*)(childData0 + 1), dx, dy, 0, localFlags);

            // Restore parent state
            *(int*)(renderer + 8) = savedX;
            *(int*)(renderer + 0xC) = savedY;
            *(int*)(renderer + 0x10) = savedZ;
            *(int*)(renderer + 0x14) = savedW;

            if ((savedX == 0x10000) && (savedY == 0) && (savedZ == 0) && (savedW == 0x10000)) {
                *(int*)(renderer + 0x1C) = 1;
            } else {
                *(int*)(renderer + 0x1C) = 0;
            }

            *(int*)(renderer + 0x124) = savedZ;
            *(int*)(renderer + 0x128) = savedW;

            if (*(int*)(renderer + 0x104) != 0) {
                FUN_00678240(); // free sprite
            }
            *(int*)(renderer + 0x104) = 0;

            recursionCount++;
        } while ((childData0 & 0x20) != 0);

        // Cleanup batch
        int* batch = *(int**)(renderer + 4);
        *(int*)(renderer + 0x104) = 0;
        sprite = 0;

        if (_DAT_00000064 == *(uint*)(batch + 0x40)) {
            *(int*)(batch + 0x78) = 1;
        } else if (_DAT_00000064 != 0) {
            int temp = _DAT_00000064 - 0x10;
            *(int*)(*(int*)(batch + 0xC) + *(int*)(_DAT_00000064 - 8) * 4) = 0;
            *(int*)(batch + 4) = *(int*)(batch + 4) - 1;
            (*DAT_01206694)(temp); // free
        }
        _DAT_00000064 = childFlags;
        _DAT_00000068 = childSome;

        batch = *(int**)(renderer + 4);
        if (childList != 0) {
            *(int*)(*(int*)(batch + 0xC) + *(int*)(childList + -4) * 4) = 0;
            int* count = (int*)(batch + 4);
            *count = *count - 1;
            (*DAT_01206694)(childList - 8); // free
        }

        int* vertexBuffer = _DAT_00000054;
        int vertexCount = _DAT_00000050;
        int vertexIndex = (int)_DAT_00000038;

        if ((accumulatedMask & 0x200) == 0) {
            *(short*)(_DAT_00000044 + vertexIndex * 2) = 0;
            *(short*)(_DAT_00000044 + 2 + vertexIndex * 2) = 
                 *(short*)(_DAT_00000044 + *(short*)(*(int*)(renderer + 0x104) + 0x38) * 2) + (short)spriteX;
            *(int*)(_DAT_00000050 + 4 + vertexIndex * 4) = 0;
            if ((flags & 0x81) != 0) {
                *(int*)(_DAT_00000050 + 4 + vertexIndex * 4) += 0x20;
                *(int*)(_DAT_00000050 + 4 + vertexIndex * 4) &= 0xFFFFFFC0;
            }
            *(int*)(_DAT_00000050 + vertexIndex * 4) = 0;
        }

        if ((flags & 0x80) != 0) {
            uint r1 = FUN_00676090();
            uint r2 = FUN_00676090();
            int idx = (int)_DAT_00000038;
            int j = 0;
            if (idx != -4 && idx + 4 >= 0) {
                int delta = (int)vertexBuffer - vertexCount;
                do {
                    uint val = FUN_00676010();
                    short sVal = FUN_00676010();
                    vertexCount += 4;
                    *(short*)(_DAT_00000044 + j * 2) = sVal;
                    *(short*)(_DAT_00000048 + j * 2) = (short)val;
                    j++;
                } while (j < idx + 4);
            }
        }
    } else {
        // Not a group; handle single sprite transform
        int vertexCount = *(short*)(sprite + 0x38);
        int* xBuffer = *(int**)(sprite + 0x50);
        int* yBuffer = *(int**)(sprite + 0x54);
        int currentIdx = vertexCount;

        if (!doClip || (flags & 0x10) != 0 || currentIdx < 1) {
            FUN_006733a0(*(int*)(sprite + 0x44), xBuffer); // free xBuffer
            FUN_006733a0(*(int*)(sprite + 0x48), yBuffer); // free yBuffer
            if ((flags & 0x10) != 0) {
                if (dx != 0 && currentIdx > 0) {
                    for (int i = 0; i < currentIdx; i++) {
                        xBuffer[i] += dx;
                    }
                }
                if (dy != 0 && currentIdx > 0) {
                    for (int i = 0; i < currentIdx; i++) {
                        yBuffer[i] -= dy;
                    }
                }
            }
        }
    }

    // Final adjustments and matrix multiply
    int* xBuf = (int*)xBuffer;
    *(int*)(renderer + 0xD8) = spriteX << 16;
    *(int*)(renderer + 0xDC) = 0;
    *(int*)(renderer + 0xF8) = spriteY << 16;
    *(int*)(renderer + 0xF4) = 0;

    if (parentSprite == nullptr) {
        bool adjustCenter = false;
        if (((flags & 0x140) == 0) || (doClip && (adjustCenter = true) )) {
            adjustCenter = false;
        }
        int lastX = xBuf[currentIdx];
        if (lastX != 0) {
            for (int i = 0; i < currentIdx + 4; i++) {
                xBuf[i] -= lastX;
            }
        }
        uint lastY = yBuffer[currentIdx];
        if (lastY != 0) {
            for (int i = 0; i < currentIdx + 4; i++) {
                yBuffer[i] -= lastY;
            }
        }
        if ((flags & 0x10) == 0) {
            int lastXval = xBuf[currentIdx];
            int lastXplus = xBuf[currentIdx + 1];
            uint aligned0 = (lastXval + 0x20) & 0xFFFFFFC0;
            int aligned1 = ((lastXplus - lastXval) + 0x20) & 0xFFFFFFC0;
            xBuf[currentIdx] = aligned0;
            xBuf[currentIdx + 1] = aligned0 + aligned1;
            if (adjustCenter && currentIdx > 0) {
                int halfDelta = ((aligned0 + aligned1 - lastXplus - lastXval) + 0x20) >> 1;
                if (halfDelta != 0) {
                    for (int i = 0; i < currentIdx; i++) {
                        xBuf[i] += halfDelta;
                    }
                }
            }
        }
    }

    uint sx = *(int*)(renderer + 0xD8);
    uint scaleX = *(int*)(renderer + 0x134);
    sx = signMagnitudeMul(sx, scaleX, &(renderer + 0xD8));

    uint sy = *(int*)(renderer + 0xF8);
    uint scaleY = *(int*)(renderer + 0x138);
    sy = signMagnitudeMul(sy, scaleY, &(renderer + 0xF8));

    // Scale coordinates up by 1024
    xBuf[currentIdx]     <<= 10;
    yBuffer[currentIdx]  <<= 10;
    xBuf[currentIdx + 1] <<= 10;
    yBuffer[currentIdx + 1] <<= 10;
    xBuf[currentIdx + 2] <<= 10;
    yBuffer[currentIdx + 2] <<= 10;
    xBuf[currentIdx + 3] <<= 10;
    yBuffer[currentIdx + 3] <<= 10;

    if (*(int*)(renderer + 0x1C) == 0) {
        uint u0 = *(int*)(renderer + 0xC);
        uint v0 = *(int*)(renderer + 8);
        uint u1 = *(int*)(renderer + 0x10);
        uint v1 = *(int*)(renderer + 0x14);

        if (u0 == 0 && u1 == 0) {
            // Simple dot product with UV
            for (int i = 0; i < currentIdx + 4; i++) {
                int tx = *(int*)((int)xBuf - (int)yBuffer + (int)(&yBuffer[i]));
                int ty = yBuffer[i];
                yBuffer[i] = signMagnitudeMul(v0, tx) + signMagnitudeMul(v1, ty);
                xBuf[i] = signMagnitudeMul(v0, ty) + signMagnitudeMul(v1, tx); // Note: might be swapped
            }
        } else {
            // Full 2x2 transformation
            for (int i = 0; i < currentIdx + 4; i++) {
                int tx = *(int*)((int)xBuf - (int)yBuffer + (int)(&yBuffer[i]));
                int ty = yBuffer[i];
                int newX = signMagnitudeMul(v0, tx) + signMagnitudeMul(u0, ty);
                int newY = signMagnitudeMul(v1, tx) + signMagnitudeMul(u1, ty) + newX; // likely error in decompilation
                xBuf[i] = newX;
                yBuffer[i] = newY;
            }
        }
    }

    // Apply final scaling (multiply by scale factor)
    uint sxFinal = *(int*)(renderer + 0xD8);
    sxFinal = signMagnitudeMul(sxFinal, v0);
    *(int*)(renderer + 0xD8) = sxFinal;

    sxFinal = signMagnitudeMul(sxFinal, u1);
    *(int*)(renderer + 0xDC) = sxFinal;

    uint syFinal = *(int*)(renderer + 0xF8);
    syFinal = signMagnitudeMul(syFinal, u0);
    *(int*)(renderer + 0xF4) = syFinal;

    syFinal = signMagnitudeMul(syFinal, v1);
    *(int*)(renderer + 0xF8) = syFinal;

    // Store extents
    *(int*)(renderer + 0xD0) = xBuf[currentIdx + 1] - xBuf[currentIdx];
    *(int*)(renderer + 0xD4) = yBuffer[currentIdx + 1] - yBuffer[currentIdx];
    *(int*)(renderer + 0xEC) = xBuf[currentIdx + 2] - xBuf[currentIdx + 3];
    *(int*)(renderer + 0xF0) = yBuffer[currentIdx + 2] - yBuffer[currentIdx + 3];

    // Scale back
    xBuf[currentIdx] >>= 10;
    yBuffer[currentIdx] >>= 10;
    xBuf[currentIdx + 1] >>= 10;
    yBuffer[currentIdx + 1] >>= 10;
    xBuf[currentIdx + 2] >>= 10;
    yBuffer[currentIdx + 2] >>= 10;
    xBuf[currentIdx + 3] >>= 10;
    yBuffer[currentIdx + 3] >>= 10;

    // Reset accumulated values
    *(int*)(renderer + 0x11C) = 0;
    *(int*)(renderer + 0x118) = 0;
    *(int*)(renderer + 0x114) = 0;
    *(int*)(renderer + 0x10C) = 0;
    *(int*)(renderer + 0x110) = 0;
    *(int*)(renderer + 0xE0) = 0;
    *(int*)(renderer + 0xE4) = 0;
    *(int*)(renderer + 0xFC) = 0;
    *(int*)(renderer + 0x100) = 0;

    *(byte*)(sprite + 0x74) = 1;
    if (*(int*)(renderer + 0x124) > 255) {
        *(byte*)(sprite + 0x74) = 0;
    }

    if ((flags & 2) != 0 && *(short*)(sprite + 0x38) > 0) {
        int* resultBuffer = 0;
        if (*(int*)(sprite + 0xC) < 1) {
            ushort texId = *(ushort*)(renderer + 0x108);
            uint texIndex = (uint)texId;
            byte spriteFlag = *(byte*)(sprite + 0x74);

            bool useAlpha = (texId < 0x800) && *(int*)(renderer + 0x1C) && spriteFlag && (flags & 0x100) == 0;
            uint alphaMask = 0;
            uint colorMask = 0;
            if (useAlpha) {
                byte bit = (byte)(1 << (texId & 7));
                if (*(byte*)((texId >> 3) + *(int*)(*(int*)(renderer + 0x18) + 0x10)) & bit) {
                    alphaMask = 0x100; // example
                }
                if (*(byte*)((texId >> 3) + *(int*)(*(int*)(renderer + 0x18) + 0x14)) & bit) {
                    colorMask = 0x100;
                }
            }

            uint flagA = (flags & 0x100) ? 1 : 0;
            resultBuffer = FUN_00677120(*(int*)(renderer + 4), *(int*)(sprite + 0x3C), *(int*)(sprite + 0x40),
                                        xBuf, yBuffer, *(int*)(sprite + 0x4C), *(byte*)(sprite + 0x34), alphaMask, colorMask, clipState,
                                        *(int*)(renderer + 0x164));

            int srcX, srcY, clipX, clipY;
            if (*(int*)(renderer + 0x28) == 0) {
                srcX = *(int*)(renderer + 0x4C);
                srcY = *(int*)(renderer + 0x48);
                clipX = 0;
                clipY = 0;
            } else {
                srcX = *(int*)(renderer + 0x4C);
                srcY = *(int*)(renderer + 0x48);
                clipX = *(int*)(renderer + 0x20);
                clipY = *(int*)(renderer + 0x24);
            }
            FUN_00677360(resultBuffer, flags & 0x20, clipX, clipY, srcY, srcX, flagA);

            *(int*)(renderer + 0x30) = resultBuffer[8];
            *(int*)(renderer + 0x10C) = resultBuffer[1] - resultBuffer[0];
            *(int*)(renderer + 0x110) = resultBuffer[3] - resultBuffer[2];
            *(int*)(renderer + 0xE0) = resultBuffer[4];
            *(int*)(renderer + 0xE4) = resultBuffer[5];
            *(int*)(renderer + 0xFC) = resultBuffer[4];
            *(int*)(renderer + 0x100) = resultBuffer[5];
            *(int*)(renderer + 0x114) = resultBuffer[6];

            if (isRecursive == 0 && *(int*)(renderer + 0x1C) && (flags & 0x20) == 0) {
                ushort tid = (ushort)texIndex;
                if (resultBuffer[0x883] == 0 && tid < 0x800) {
                    byte* alphaByte = (byte*)((texIndex & 0xFFFF) >> 3) + *(int*)(*(int*)(renderer + 0x18) + 0x10);
                    *alphaByte |= (byte)(1 << (texIndex & 7));
                }
                if (resultBuffer[0x884] == 0 && tid < 0x800) {
                    byte* colorByte = (byte*)((texIndex & 0xFFFF) >> 3) + *(int*)(*(int*)(renderer + 0x18) + 0x14);
                    *colorByte |= (byte)(1 << (texIndex & 7));
                }
            }
        }
        *(int*)(renderer + 0x100) -= *(int*)((int)xBuf + 8 + currentIdx * 4);
        *(int*)(renderer + 0xFC) -= yBuffer[currentIdx + 2];
        if (*(int*)(sprite + 0xC) < 1) {
            *(int*)(renderer + 0x118) = resultBuffer[7];
            resultBuffer[7] = 0;
            *(int*)(renderer + 0x11C) = 0;
        }
        if (xBuf[currentIdx] != 0) {
            *(int*)(renderer + 0xE4) -= xBuf[currentIdx];
        }
        if (yBuffer[currentIdx] != 0) {
            *(int*)(renderer + 0xE0) -= yBuffer[currentIdx];
        }
        *(int*)(renderer + 0xE4) &= 0xFFFFFFC0;
        *(int*)(renderer + 0xE0) &= 0xFFFFFFC0;
        FUN_00677d00(); // finalize batch
    }

    if ((flags & 4) == 0) {
        FUN_00678240(); // release sprite
        *(int*)(renderer + 0x104) = 0;
    }
}