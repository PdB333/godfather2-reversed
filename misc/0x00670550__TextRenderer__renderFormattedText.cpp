// FUNC_NAME: TextRenderer::renderFormattedText

/* Address: 0x00670550
 * Role: Renders a hardcoded styled text string (with <font> and <size> tags)
 *       into a pixel buffer. Handles line wrapping, character spacing,
 *       and per-character effects. Used for UI text layout.
 * Parameters:
 *   context      - pointer to render state structure
 *   fontIndex    - index into font list (when switching fonts via tag)
 *   baseFontSize - initial font height in points (or logical units)
 *   outWidth     - output width (updated to actual rendered width)
 *   outHeight    - output height (updated to actual rendered height)
 *   destPitch    - destination buffer pitch (bytes per row)
 *   wrapMode     - 0 = no word wrap, 1 = word wrap
 *   maxWidth     - maximum allowed width in pixels
 *   alignment    - 0 = left, 1 = center, 2 = right
 *   maxLines     - maximum number of lines to render
 *   lineSpacing  - multiplier for line height
 *   sizeScale    - divisor for converting <size> tag values to logical size
 *
 * The source text is read from a global buffer at 0x0119dac0.
 * Structure offsets for context (param_1):
 *   +0x00: pointer to pixel buffer (destination)
 *   +0x04: font handle array? (used to get font)
 *   +0x08: current font context (set by FUN_00671510)
 *   +0x10: current font index (cached)
 *   +0x14: number of fonts
 *   +0x28: font data per index: +0x28 + index*5 = font ID
 *   +0x198: (0x66*4) start render index for substring effect
 *   +0x19C: (0x67*4) end render index for substring effect
 *   +0x1A0: (0x68*4) previous start? (-1)
 *   +0x1A4: (0x69*4) previous end? (-1)
 * Buffer offsets (for destination pointer):
 *   +0x1c: font size (byte)
 *   +0x2c: color? (reset to 0)
 *   +0x30: another color? (reset to 0)
 *   +0xe0: something for glyph positioning
 *   +0xe4: something for glyph positioning
 *   +0x10c: line width?
 *   +0x110: line height?
 *   +0x118: glyph data pointer?
 */

int TextRenderer::renderFormattedText(
    int *context,
    int fontIndex,
    int baseFontSize,
    int *outWidth,
    int *outHeight,
    int destPitch,
    int wrapMode,
    int maxWidth,
    int alignment,
    int maxLines,
    float lineSpacing,
    float sizeScale)
{
    ushort *dstPtr;
    int iVar2, iVar9, iVar11, iVar12, iVar16;
    bool bVar3, bVar4, bVar5;
    ushort uVar6;
    short sVar7;
    undefined2 uVar8;
    byte *pbVar10, *pbVar13;
    ushort *puVar14, *puVar15, *puVar17, *puVar18;
    float fVar19, fVar20;
    int local_4e0;
    ushort *local_4dc;
    undefined4 local_4d4 = 0;
    int local_4d0, local_4cc, local_4c8 = 0x20000;
    int local_4c4 = 0;
    uint local_4c0;
    int local_4bc = 0, local_4b8 = 0;
    uint local_4b4;
    int local_4b0, local_4a4;
    undefined4 local_4ac = 0, local_4a8 = 0;
    int local_4a4_copy;
    ushort *local_4a0;
    float local_49c;
    int local_498 = 0;
    int *local_494;
    int local_490 = 0;
    int local_48c;
    int local_488;
    ushort local_484[64]; // temp buffer for name comparison
    undefined2 local_404;
    ushort local_402[513]; // word buffer for building lines

    // If the font index changed or no font is set, load new font
    if ((context[4] != fontIndex) || (context[2] == 0)) {
        iVar9 = FUN_00671510(context[1], (short)context[fontIndex * 5 + 10], &local_4d4);
        context[2] = iVar9;
    }

    // Select scaling factor based on size threshold (< 64 uses low-res scale)
    fVar19 = DAT_00e2cd54; // high-res scale
    fVar20 = DAT_00e2b1a4; // low-res scale
    context[4] = fontIndex;

    if (baseFontSize < 0x40) {
        fVar19 = fVar20;
    }

    local_49c = (float)(baseFontSize << 0x10); // logical size in fixed-point
    local_4b0 = (int)(local_49c * fVar19);
    local_4a4 = (int)(local_49c * fVar19);
    local_4ac = 0;
    local_4a8 = 0;
    FUN_006735d0(context[2], 0x48, &local_4b0); // set rendering color/alpha?

    // Initialize destination buffer header
    iVar9 = *context;
    *(undefined4 *)(iVar9 + 0x2c) = 0;
    *(undefined4 *)(iVar9 + 0x30) = 0;
    *(char *)(iVar9 + 0x1c) = (char)baseFontSize;

    iVar9 = context[2];
    local_4d0 = *(int *)(iVar9 + 0x6c) + 0x28000; // vertical offset base (line height)
    local_4cc = *outWidth;
    if (maxWidth < *outWidth) {
        local_4cc = maxWidth;
    }

    bVar5 = true;
    local_488 = (int)((float)((*(int *)(iVar9 + 0x7c) / 3 - *(int *)(iVar9 + 0x74)) + *(int *)(iVar9 + 0x6c)) * lineSpacing);

    context[0x68] = -1;
    context[0x69] = -1;
    bVar3 = false;

    do {
        do {
            uVar6 = *puVar17; // puVar17 starts at global text buffer (0x0119dac0)
            local_4dc = local_402;
            local_404 = 0;
            local_402[0] = 0;
            local_4e0 = 0;
            puVar15 = local_4dc;

            while (uVar6 != 0) {
                // Handle line breaks
                if (uVar6 == 0xd) { // CR
                    puVar17 = puVar17 + 1;
                    if (*puVar17 == 10) goto LAB_00670b59; // LF after CR
                    break;
                }
                if ((uVar6 == 0x5c) && (puVar17[1] == 0x6e)) { // "\n"
                    puVar17 = puVar17 + 2;
                    break;
                }
                if (uVar6 == 10) goto LAB_00670b59; // LF

                // Detect <font ...> tag
                if (((((uVar6 == 0x3c) && (puVar17[1] == 0x66)) && (puVar17[2] == 0x6f)) &&
                     (puVar17[3] == 0x6e) && (puVar17[4] == 0x74)) && (puVar17[5] == 0x20)) {
                    puVar15 = puVar15 + 1;
                    *puVar15 = 0;
                    puVar17 = puVar17 + 1;
                    bVar5 = false;
                    break;
                }

                // Detect "font " (without '<') or "size=" tag
                if (((uVar6 == 0x66) && (puVar17[1] == 0x6f)) &&
                    ((puVar17[2] == 0x6e) && (puVar17[3] == 0x74) && (puVar17[4] == 0x20))) {
                    puVar18 = puVar17 + 5;
                    puVar14 = puVar15;
                    do {
                        // Look for "name=" inside font tag
                        for (; (((*puVar18 == 0x6e && (puVar18[1] == 0x61)) &&
                                 (puVar18[2] == 0x6d) && (puVar18[3] == 0x65) && (puVar18[4] == 0x3d)));
                             puVar18 = puVar18 + 1) {
                            iVar9 = 0;
                            puVar18 = puVar18 + 5;
                            if (0 < context[5]) { // iterate through known fonts
                                do {
                                    FUN_00670490(local_484); // clear temp buffer
                                    iVar11 = 0;
                                    puVar17 = puVar18;
                                    do {
                                        uVar6 = *(ushort *)(((int)local_484 - (int)puVar18) + (int)puVar17);
                                        // Compare name with local_484 (built from font entry)
                                        if ((uVar6 == 0) && ((*puVar17 == 0x20 || (*puVar17 == 0x3e)))) {
                                            puVar18 = puVar18 + iVar11;
                                            // Font match: switch to that font
                                            if ((context[4] != iVar9) || (context[2] == 0)) {
                                                iVar11 = FUN_00671510(context[1], (short)context[iVar9 * 5 + 10], &local_4d4);
                                                context[2] = iVar11;
                                            }
                                            fVar19 = DAT_00e2cd54;
                                            fVar20 = DAT_00e2b1a4;
                                            context[4] = iVar9;
                                            if (baseFontSize < 0x40) {
                                                fVar19 = fVar20;
                                            }
                                            local_4b0 = (int)(local_49c * fVar19);
                                            local_4a4 = (int)(local_49c * fVar19);
                                            local_4ac = 0;
                                            local_4a8 = 0;
                                            FUN_006735d0(context[2], 0x48, &local_4b0);
                                            iVar11 = *context;
                                            *(undefined4 *)(iVar11 + 0x2c) = 0;
                                            *(undefined4 *)(iVar11 + 0x30) = 0;
                                            *(char *)(iVar11 + 0x1c) = (char)baseFontSize;
                                            fontIndex = iVar9;
                                            goto LAB_006708db;
                                        }
                                        if (*puVar17 != uVar6) break;
                                        iVar11 = iVar11 + 1;
                                        puVar17 = puVar17 + 1;
                                    } while (iVar11 < 0x40);
                                    iVar9 = iVar9 + 1;
                                } while (iVar9 < context[5]);
                            }
LAB_006708db:
                            // Skip rest of attribute value
                            uVar6 = *puVar18;
                            while (((uVar6 != 0 && (uVar6 != 0x20)) && (uVar6 != 0x3e))) {
                                puVar17 = puVar18 + 1;
                                puVar18 = puVar18 + 1;
                                uVar6 = *puVar17;
                            }
                            puVar14 = local_4dc;
                        }
                        // Look for "size=" attribute
                        if (((*puVar18 != 0x73) || (puVar18[1] != 0x69)) ||
                            ((puVar18[2] != 0x7a) || (puVar18[3] != 0x65) || (puVar18[4] != 0x3d)))
                            goto LAB_00670b42;
                        uVar6 = puVar18[5];
                        puVar18 = puVar18 + 5;
                        iVar9 = 0;
                        if (uVar6 != 0x20) {
                            do {
                                if (uVar6 == 0x3e) break;
                                if ((0x2f < uVar6) && (uVar6 < 0x3a)) {
                                    iVar9 = (uVar6 - 0x30) + iVar9 * 10;
                                }
                                uVar6 = puVar18[1];
                                puVar18 = puVar18 + 1;
                            } while (uVar6 != 0x20);
                            if (0x40 < iVar9) {
                                iVar9 = iVar9 * 2; // double size if large?
                            }
                        }
                        // Apply size change
                        baseFontSize = (int)((float)iVar9 / sizeScale);
                        puVar18 = puVar18 + 1;
                        fVar20 = DAT_00e2cd54;
                        if (baseFontSize < 0x40) {
                            fVar20 = DAT_00e2b1a4;
                        }
                        local_49c = (float)(baseFontSize << 0x10);
                        local_4b0 = (int)(local_49c * fVar20);
                        local_4a4 = (int)(local_49c * fVar20);
                        local_4ac = 0;
                        local_4a8 = 0;
                        FUN_006735d0(context[2], 0x48, &local_4b0);
                        iVar9 = *context;
                        *(char *)(iVar9 + 0x1c) = (char)baseFontSize;
                        *(undefined4 *)(iVar9 + 0x2c) = 0;
                        *(undefined4 *)(iVar9 + 0x30) = 0;
                        puVar14 = local_4dc;
                    } while( true );
                }

                // Handle word wrap: if wrapMode is set, treat spaces as break points
                if ((wrapMode == 0) || (uVar6 != 0x20)) {
                    // Handle non-space character
                    if (uVar6 == 0x1f) {
                        *puVar15 = 0x5c; // replace 0x1f with backslash?
                    } else {
                        *puVar15 = uVar6;
                    }
                    local_4e0 = local_4e0 + 1;
                    puVar14 = puVar15 + 1;
                    puVar18 = puVar17 + 1;
                    local_4dc = puVar14;
                    if (wrapMode != 0) {
                        *puVar14 = 0;
                        iVar9 = FUN_00670f30(context, local_402); // measure current word width
                        if (local_4cc + -4 <= iVar9) {
                            // Word too long: break line
                            *puVar15 = 0;
                            puVar15 = puVar14;
                            if (local_4e0 == 1) {
                                return local_4c4;
                            }
                            break;
                        }
                    }
                } else {
                    // Space with wrapMode: start new word
                    puVar17 = puVar17 + 1;
                    *puVar15 = 0x20;
                    uVar6 = *puVar17;
                    puVar18 = puVar17;
                    puVar14 = puVar15 + 1;
                    while (((local_4e0 = local_4e0 + 1, uVar6 != 0 && (uVar6 != 0xd)) && (uVar6 != 10))) {
                        if (uVar6 == 0x5c) {
                            if (puVar18[1] == 0x6e) break;
                        } else if (((uVar6 == 0x20) && (puVar18[1] != 0x21)) && (puVar18[1] != 0x3f)) break;
                        puVar18 = puVar18 + 1;
                        *puVar14 = uVar6;
                        puVar14 = puVar14 + 1;
                        uVar6 = *puVar18;
                    }
                    *puVar14 = 0;
                    iVar9 = FUN_00670f30(context, local_402); // measure word width
                    local_4dc = puVar14;
                    if (local_4cc + -4 <= iVar9 + 2) {
                        *puVar15 = 0;
                        puVar15 = puVar15 + 1;
                        break;
                    }
                }
LAB_00670b42:
                puVar15 = puVar14;
                puVar17 = puVar18;
                uVar6 = *puVar18;
            }
            local_4c4 = local_4c4 + 1; // line count
            *puVar15 = 0;
        } while (local_4c4 < maxLines);

        iVar9 = FUN_00670f30(context, local_402); // measure full line width
        if (local_498 < iVar9) {
            local_498 = iVar9; // track max width
        }

        iVar11 = 0;
        if (alignment == 1) {
            iVar11 = ((maxWidth - iVar9) + -4) * 0x10000; // center offset (fixed-point)
        } else if (alignment == 2) {
            iVar11 = ((maxWidth - iVar9) + -4) * 0x8000; // right offset
        }

        if (bVar3) {
            bVar3 = false;
        } else {
            local_4c8 = iVar11 + 0x20000; // set horizontal offset
        }

        local_4a0 = local_402;
        local_4b4 = 0;
        iVar9 = 0;
        if (local_402[0] != 0) {
            local_4c0 = (uint)local_402[0];
            local_494 = context + fontIndex * 5 + 10; // pointer to font data for this index
            local_48c = 1;
            do {
                uVar6 = local_402[local_4b4 & 0xffff];
                piVar1 = context + 2;
                sVar7 = FUN_00672900((short)*local_494, piVar1, uVar6); // get glyph width
                if (sVar7 == 0) {
                    // Glyph not found, render a placeholder
                    uVar8 = 0x42;
                    if (destPitch == 0) {
                        uVar8 = DAT_01127e58; // some default
                    }
                    FUN_00672750((short)*local_494, piVar1, uVar6, uVar8, &local_4d4); // render glyph
                }

                iVar9 = *piVar1; // current font context
                iVar16 = *(int *)(iVar9 + 0xe4) + (local_4c8 >> 10) >> 6; // x coordinate
                iVar11 = (local_4d0 >> 10) - *(int *)(iVar9 + 0xe0) >> 6; // y coordinate
                if (iVar11 < 0) {
                    iVar11 = 0;
                }

                iVar2 = *(int *)(iVar9 + 0x10c); // line width (destination row stride?)
                local_4dc = (ushort *)iVar2;
                if (local_4cc < iVar2 + iVar16) {
                    local_4dc = (ushort *)(local_4cc - iVar16); // clamp width
                }
                if (*outHeight < *(int *)(iVar9 + 0x110) + iVar11) {
                    iVar12 = *outHeight - iVar11; // clamp height
                } else {
                    iVar12 = *(int *)(iVar9 + 0x110);
                }

                if (local_4bc < (int)local_4dc + iVar16) {
                    local_4bc = (int)local_4dc + iVar16; // update max rendered width
                }
                if (local_4b8 < iVar12 + iVar11) {
                    local_4b8 = iVar12 + iVar11; // update max rendered height
                }

                // Determine if we should actually render the pixel data
                if (destPitch == 0) {
                    bVar4 = false;
                } else {
                    bVar4 = true;
                    if ((short)local_4c0 == 0x5f) goto LAB_00670d6e; // skip underscore? (effect marker?)
                }

                // Check substring effect range (context[0x66] and context[0x67])
                if (context[0x66] < 1) {
                    // No range: always render
                    goto LAB_00670da2;
                } else {
                    local_490 = local_490 + 1;
                    if ((local_490 <= context[0x66]) && (context[0x67] < local_490)) {
                        // Outside range: skip rendering
                        goto LAB_00670da2;
                    }
                }

                // Actually render glyph pixels into destination buffer
                if (bVar4) {
                    pbVar13 = *(byte **)(iVar9 + 0x118); // glyph bitmap data
                    iVar9 = *outWidth; // destination row width?
                    pbVar10 = (byte *)(iVar9 * iVar11 + iVar16 + destPitch);
                    while (iVar12 = iVar12 + -1, puVar15 = local_4dc, -1 < iVar12) {
                        while (-1 < (int)puVar15 + -1) {
                            *pbVar10 = *pbVar10 | (&DAT_01205178)[*pbVar13]; // alpha blend
                            pbVar13 = pbVar13 + 1;
                            pbVar10 = pbVar10 + 1;
                            puVar15 = (ushort *)((int)puVar15 + -1);
                        }
                        pbVar13 = pbVar13 + (iVar2 - (int)local_4dc); // advance to next row
                        pbVar10 = pbVar10 + (iVar9 - (int)local_4dc);
                    }
                }

                // Update vertical/horizontal offsets based on font metrics
                iVar9 = context[2];
                if (*(int *)(iVar9 + 100) != 0) {
                    local_4c8 = local_4c8 + *(int *)(iVar9 + 0xd0); // advance x
                }
                if (*(int *)(iVar9 + 0xa0) != 0) {
                    local_4d0 = local_4d0 + *(int *)(iVar9 + 0xd4); // advance y
                }

                local_4b4 = local_4b4 + 1;
                local_4a0 = local_4a0 + 1;
                uVar6 = *local_4a0;
                local_4c0 = (uint)uVar6;
                iVar9 = local_48c;
            } while (uVar6 != 0);
        }

        // After processing all characters in the line, adjust vertical offset
        if (bVar5) {
            if (iVar9 != 0) {
                local_4d0 = local_4d0 + local_488; // line spacing
            }
        } else {
            bVar3 = true;
            bVar5 = true;
        }

        // Update output dimensions
        if (*puVar17 == 0) {
            if (local_4bc < 1) {
                iVar9 = 0;
            } else {
                iVar11 = local_4bc;
                if ((local_4bc < local_4cc) && (iVar11 = local_4bc + 1, iVar11 < local_4cc)) {
                    iVar11 = local_4bc + 2;
                }
                iVar9 = local_4b8;
                local_4bc = iVar11;
                if ((local_4b8 < *outHeight) && (iVar9 = local_4b8 + 1, iVar9 < *outHeight)) {
                    iVar9 = local_4b8 + 2;
                }
            }
            *outWidth = local_4bc;
            *outHeight = iVar9;
            if ((destPitch != 0) && (-1 < context[0x66])) {
                context[0x67] = context[0x66]; // update effect end index
            }
            return local_4c4;
        }
    } while( true );
}
```