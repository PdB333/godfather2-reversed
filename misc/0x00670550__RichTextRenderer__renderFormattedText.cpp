// FUNC_NAME: RichTextRenderer::renderFormattedText
int RichTextRenderer::renderFormattedText(RichTextRenderer* thisPtr, int fontIndex, int fontSize, int* outWidth, int* outHeight, byte* destBuffer, int wrapMode, int maxWidth, int align, int maxLines, float scaleX, float scaleY)
{
    // References to global constants for font scaling
    const float FONT_SIZE_SCALE = DAT_00e2cd54; // 0x00e2cd54
    const float SMALL_FONT_SCALE = DAT_00e2b1a4; // 0x00e2b1a4

    int textHeight = 0;
    int totalLines = 0;
    int maxLineWidth = 0;

    if (thisPtr[4] != fontIndex || thisPtr[2] == 0) {
        int result = FUN_00671510(thisPtr[1], (short)thisPtr[fontIndex * 5 + 10], &textHeight);
        thisPtr[2] = result;
    }

    float fontSizeScale = FONT_SIZE_SCALE;
    if (fontSize < 0x40) {
        fontSizeScale = SMALL_FONT_SCALE;
    }
    thisPtr[4] = fontIndex;

    int scaledFontSize = (int)((float)(fontSize << 16) * fontSizeScale);
    int color = 0;
    int unused1 = 0;
    FUN_006735d0(thisPtr[2], 0x48, &scaledFontSize);

    int gfxSurface = thisPtr[0];
    *(int*)(gfxSurface + 0x2c) = 0;
    *(int*)(gfxSurface + 0x30) = 0;
    *(char*)(gfxSurface + 0x1c) = (char)fontSize;

    int fontData = thisPtr[2];
    int baselineY = *(int*)(fontData + 0x6c) + 0x28000;
    int lineY = 0;
    int charCount = 0;

    // Pointer to the input string (global or member)
    ushort* inputStr = &DAT_0119dac0; // actual string pointer, likely from thisPtr or global
    int maxLineWidthIn = *outWidth;
    if (maxWidth < *outWidth) {
        maxLineWidthIn = maxWidth;
    }

    bool isFirstLine = true;
    int currentLineWidth = 0;
    int lineHeight = 0;
    int lineSpacing = (int)((float)((*(int*)(fontData + 0x7c) / 3 - *(int*)(fontData + 0x74)) + *(int*)(fontData + 0x6c)) * scaleX);
    thisPtr[0x68] = -1;
    thisPtr[0x69] = -1;
    bool skipRest = false;
    int penX = 0x20000; // initial X offset

    do {
        ushort currentChar = *inputStr;
        ushort lineBuffer[0x100]; // local_402 size? actually 513 ushorts
        lineBuffer[0] = 0;
        int linePos = 0;

        while (currentChar != 0) {
            // Handle newline characters
            if (currentChar == 0xd) {
                inputStr++;
                if (*inputStr == 10) {
                    inputStr++;
                }
                break;
            }
            if (currentChar == 0x5c && inputStr[1] == 0x6e) { // "\n"
                inputStr += 2;
                break;
            }
            if (currentChar == 10) {
                inputStr++;
                if (*inputStr == 0xd) { // LF+CR
                    inputStr++;
                }
                break;
            }

            // Check for <font ...> tag
            if (currentChar == 0x3c && inputStr[1] == 0x66 && inputStr[2] == 0x6f &&
                inputStr[3] == 0x6e && inputStr[4] == 0x74 && inputStr[5] == 0x20) {
                lineBuffer[linePos] = 0;
                inputStr += 1; // skip past '<'
                isFirstLine = false;
                break;
            }

            // Check for "font " (without '<')? Actually looking for "font " sequence
            if (currentChar == 0x66 && inputStr[1] == 0x6f && inputStr[2] == 0x6e &&
                inputStr[3] == 0x74 && inputStr[4] == 0x20) {
                ushort* tagPtr = inputStr + 5;
                do {
                    // Parse "name=" attribute
                    while (*tagPtr == 0x6e && tagPtr[1] == 0x61 && tagPtr[2] == 0x6d &&
                           tagPtr[3] == 0x65 && tagPtr[4] == 0x3d) {
                        tagPtr += 5;
                        // Search for matching font name in font list
                        for (int i = 0; i < thisPtr[5]; i++) {
                            ushort fontName[0x40];
                            FUN_00670490(fontName);
                            int cmpLen = 0;
                            ushort* testPtr = tagPtr;
                            while (true) {
                                ushort testChar = fontName[cmpLen];
                                if (testChar == 0 && (*testPtr == 0x20 || *testPtr == 0x3e)) {
                                    tagPtr += cmpLen;
                                    // Found matching font, change font
                                    if (thisPtr[4] != i || thisPtr[2] == 0) {
                                        int result = FUN_00671510(thisPtr[1], (short)thisPtr[i * 5 + 10], &textHeight);
                                        thisPtr[2] = result;
                                    }
                                    float tmpScale = FONT_SIZE_SCALE;
                                    if (fontSize < 0x40) {
                                        tmpScale = SMALL_FONT_SCALE;
                                    }
                                    thisPtr[4] = i;
                                    scaledFontSize = (int)((float)(fontSize << 16) * tmpScale);
                                    FUN_006735d0(thisPtr[2], 0x48, &scaledFontSize);
                                    gfxSurface = thisPtr[0];
                                    *(int*)(gfxSurface + 0x2c) = 0;
                                    *(int*)(gfxSurface + 0x30) = 0;
                                    *(char*)(gfxSurface + 0x1c) = (char)fontSize;
                                    fontIndex = i;
                                    goto continueTagParse;
                                }
                                if (*testPtr != testChar) break;
                                cmpLen++;
                                testPtr++;
                            }
                        }
                        continueTagParse:
                        // Skip past the value until space or '>'
                        while (*tagPtr != 0 && *tagPtr != 0x20 && *tagPtr != 0x3e) {
                            tagPtr++;
                        }
                    }
                    // Parse "size=" attribute
                    if (*tagPtr != 0x73 || tagPtr[1] != 0x69 || tagPtr[2] != 0x7a ||
                        tagPtr[3] != 0x65 || tagPtr[4] != 0x3d) {
                        goto doneTagParse;
                    }
                    ushort digitChar = tagPtr[5];
                    tagPtr += 5;
                    int newSize = 0;
                    if (digitChar != 0x20) {
                        while (true) {
                            if (digitChar == 0x3e) break;
                            if (digitChar > 0x2f && digitChar < 0x3a) {
                                newSize = (digitChar - 0x30) + newSize * 10;
                            }
                            digitChar = tagPtr[1];
                            tagPtr++;
                        }
                        if (newSize > 0x40) {
                            newSize = newSize * 2;
                        }
                    }
                    fontSize = (int)((float)newSize / scaleY);
                    tagPtr++;
                    float tmpScale = FONT_SIZE_SCALE;
                    if (fontSize < 0x40) {
                        tmpScale = SMALL_FONT_SCALE;
                    }
                    scaledFontSize = (int)((float)(fontSize << 16) * tmpScale);
                    FUN_006735d0(thisPtr[2], 0x48, &scaledFontSize);
                    gfxSurface = thisPtr[0];
                    *(char*)(gfxSurface + 0x1c) = (char)fontSize;
                    *(int*)(gfxSurface + 0x2c) = 0;
                    *(int*)(gfxSurface + 0x30) = 0;
                } while (true);
                doneTagParse:
                break; // exit outer loop after processing tag
            }

            // Handle word wrap: if wrapping enabled and space is found
            if (wrapMode != 0 && currentChar == 0x20) {
                inputStr++;
                lineBuffer[linePos++] = 0x20;
                ushort nextChar = *inputStr;
                // Accumulate rest of word
                while (linePos < 0x100 && nextChar != 0 && nextChar != 0xd && nextChar != 10) {
                    if (nextChar == 0x5c && inputStr[1] == 0x6e) break;
                    if (nextChar == 0x20 && inputStr[1] != 0x21 && inputStr[1] != 0x3f) break;
                    inputStr++;
                    lineBuffer[linePos++] = nextChar;
                    nextChar = *inputStr;
                }
                lineBuffer[linePos] = 0;
                int wordWidth = FUN_00670f30(thisPtr, lineBuffer);
                if (maxLineWidthIn - 4 <= wordWidth + 2) {
                    lineBuffer[0] = 0; // wrap, break line
                    break;
                }
            } else {
                // Normal character
                if (currentChar == 0x1f) {
                    lineBuffer[linePos] = 0x5c; // replacement?
                } else {
                    lineBuffer[linePos] = currentChar;
                }
                linePos++;
                ushort* bufPtr = lineBuffer + linePos;
                *bufPtr = 0;
                if (wrapMode != 0) {
                    int textWidth = FUN_00670f30(thisPtr, lineBuffer);
                    if (maxLineWidthIn - 4 <= textWidth) {
                        lineBuffer[linePos-1] = 0;
                        if (linePos == 1) {
                            return charCount;
                        }
                        break;
                    }
                }
            }
        }

        charCount++;
        lineBuffer[linePos] = 0;
    } while (charCount < maxLines);

    // Measure the actual line width
    int lineWidth = FUN_00670f30(thisPtr, lineBuffer);
    if (maxLineWidth < lineWidth) {
        maxLineWidth = lineWidth;
    }

    // Compute alignment offset
    int alignOffset = 0;
    if (align == 1) {
        alignOffset = ((maxWidth - lineWidth) + -4) * 0x10000;
    } else if (align == 2) {
        alignOffset = ((maxWidth - lineWidth) + -4) * 0x8000;
    }
    if (alignOffset < 0) {
        alignOffset = 0;
    }

    if (skipRest) {
        skipRest = false;
    } else {
        penX = alignOffset + 0x20000;
    }

    // Render each glyph of the line
    ushort* glyphStr = lineBuffer;
    int glyphIndex = 0;
    int totalGlyphs = 0;
    if (lineBuffer[0] != 0) {
        int currentGlyph = (ushort)lineBuffer[0];
        int* fontTable = thisPtr + fontIndex * 5 + 10;
        int skipFrom = thisPtr[0x66];
        int skipTo = thisPtr[0x67];
        do {
            ushort glyph = lineBuffer[glyphIndex & 0xffff];
            int* fontPtr = thisPtr + 2;
            short kerning = FUN_00672900((short)*fontTable, fontPtr, glyph);
            if (kerning == 0) {
                ushort renderChar = 0x42;
                if (destBuffer == 0) {
                    renderChar = DAT_01127e58;
                }
                FUN_00672750((short)*fontTable, fontPtr, glyph, renderChar, &textHeight);
            }
            int fontData2 = *fontPtr; // font glyph data pointer
            int glyphWidth = (*(int*)(fontData2 + 0xe4) + (penX >> 10)) >> 6;
            int glyphHeight = (baselineY >> 10) - *(int*)(fontData2 + 0xe0) >> 6;
            if (glyphHeight < 0) {
                glyphHeight = 0;
            }
            int glyphPitch = *(int*)(fontData2 + 0x10c);
            int destX = glyphPitch;
            if (maxLineWidthIn < glyphPitch + glyphWidth) {
                destX = maxLineWidthIn - glyphWidth;
            }
            int destY = *(int*)(fontData2 + 0x110) + glyphHeight;
            if (*outHeight < destY) {
                // clamp
            }
            // Update line width/height extremes
            if (currentLineWidth < destX + glyphWidth) {
                currentLineWidth = destX + glyphWidth;
            }
            if (lineHeight < destY + glyphHeight) {
                lineHeight = destY + glyphHeight;
            }

            bool drawGlyph = (destBuffer != 0);
            if (destBuffer != 0) {
                // Check if the current character is '_' (underscore) - skip draw
                if ((short)currentGlyph == 0x5f) {
                    drawGlyph = false;
                }
            }

            // Apply skip range filter
            if (skipFrom >= 1) {
                totalLines++;
                if (totalLines <= skipFrom || skipTo < totalLines) {
                    // Draw the glyph
                    if (drawGlyph) {
                        byte* srcAlpha = *(byte**)(fontData2 + 0x118);
                        int width = *outWidth;
                        byte* dest = (byte*)(width * glyphHeight + destX + destBuffer);
                        for (int y = 0; y < destY; y++) {
                            int x = destX;
                            while (x >= 0) {
                                *dest |= alphaLookup[*srcAlpha]; // DAT_01205178
                                srcAlpha++;
                                dest++;
                                x--;
                            }
                            srcAlpha += (glyphPitch - destX);
                            dest += (width - destX);
                        }
                    }
                }
            } else {
                if (drawGlyph) {
                    // similar drawing code
                }
            }

            // Advance penX by glyph advance
            fontData2 = thisPtr[2];
            if (*(int*)(fontData2 + 100) != 0) {
                penX += *(int*)(fontData2 + 0xd0);
            }
            if (*(int*)(fontData2 + 0xa0) != 0) {
                baselineY += *(int*)(fontData2 + 0xd4);
            }

            glyphIndex++;
            ushort nextGlyph = lineBuffer[glyphIndex];
            currentGlyph = nextGlyph;
            totalGlyphs++;
        } while (nextGlyph != 0);
    }

    if (isFirstLine) {
        if (totalGlyphs != 0) {
            baselineY += lineSpacing;
        }
    } else {
        skipRest = true;
        isFirstLine = true;
    }

    if (*inputStr == 0) {
        if (currentLineWidth < 1) {
            lineWidth = 0;
        } else {
            int w = currentLineWidth;
            if (currentLineWidth < maxLineWidthIn && w + 1 < maxLineWidthIn) {
                w = currentLineWidth + 2;
            }
            lineWidth = lineHeight;
            currentLineWidth = w;
            if (lineHeight < *outHeight && lineHeight + 1 < *outHeight) {
                lineHeight = lineHeight + 2;
            }
        }
        *outWidth = currentLineWidth;
        *outHeight = lineHeight;
        if (destBuffer != 0 && thisPtr[0x66] >= 0) {
            thisPtr[0x67] = thisPtr[0x66];
        }
        return charCount;
    }

    // Continue to next line
    goto start; // loop back (simplified)
}