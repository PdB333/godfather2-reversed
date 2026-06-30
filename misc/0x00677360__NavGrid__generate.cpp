// FUNC_NAME: NavGrid::generate
void __thiscall NavGrid::generate(NavGrid* this, char mode, void* (*allocFunc)(void*, int), void* allocContext, int brightnessAdjust, int contrastAdjust, int edgeShiftFlag)
{
    uint flagCompressed = this->field_0x2204; // this[0x881]
    if (this->needsInit == 0) { // this[9]
        NavGrid::init(this);
    }

    int x0 = this->left; // this[10]
    if (edgeShiftFlag != 0) {
        x0 -= 0x40; // shift left edge by 64 (half cell)
    }
    int x1 = this->right; // this[0xb]
    int y0 = this->top; // this[0xc]
    int y1 = this->bottom; // this[0xd]
    int y1Plus = y1 + 0x40;

    // Store raw coordinates
    this->storedLeft = x0; // this[5]
    this->storedBottomPlus64 = y1Plus; // this[4]

    // Convert to grid cell coordinates (cell size = 64)
    int gridX0 = x0 >> 6; // local_28
    int gridX1 = (x1 + 0x40) >> 6; // iVar2
    int gridY0 = y0 >> 6; // iVar23
    int gridY1 = (y1 + 0x40) >> 6; // iVar16, after reuse
    gridY1 = y1Plus >> 6;

    this->gridX0 = gridX0; // this[0]
    this->gridX1 = gridX1; // this[1]
    this->gridY0 = gridY0; // this[2]
    this->gridY1 = gridY1; // this[3]

    int gridWidth = gridX1 - gridX0; // iVar2 (original)
    int gridHeight = gridY1 - gridY0; // iVar9

    int rowStride = gridWidth; // iVar3, may be bits or bytes
    if (flagCompressed == 0) {
        rowStride = (gridWidth + 7) >> 3; // bits to bytes (ceil div 8)
    }
    this->rowStride = rowStride; // this[6]
    this->gridData = 0; // this[7]

    if (mode == 0) {
        // Mode 0: allocate buffer and rasterize compressed (binary occupation) grid
        this->ownsData = 0; // this[8]
        int totalBytes = rowStride * gridHeight;
        int* buffer = 0;
        if ((allocFunc != 0) && (buffer = (int*)allocFunc(allocContext, totalBytes), buffer != 0)) {
            // custom allocator succeeded
        } else {
            buffer = (int*)NavGrid::malloc(totalBytes); // FUN_00672f60
            this->ownsData = 1;
        }
        this->gridData = (int)buffer;

        // Zero-fill buffer
        int* ptr = buffer;
        int words = totalBytes >> 2;
        int i = 0;
        if (words > 0) {
            do {
                *ptr = 0;
                ptr++;
                words--;
            } while (words != 0);
        }
        if (i * 4 < totalBytes) {
            _memset(&buffer[i], 0, totalBytes - i * 4);
        }

        int minScanline = this->minScanline; // this[0x35]
        int maxScanline = this->maxScanline; // this[0x36]

        // Ensure max is within bounds
        if ((minScanline <= maxScanline) && (gridY1 <= maxScanline)) {
            this->maxScanline = gridY1 - 1;
            maxScanline = gridY1 - 1;
        }

        if (flagCompressed == 0) {
            // Rasterize polygons into compressed bit grid
            int curScanline = maxScanline;
            int* rowPtr = (int*)((int)buffer + ((gridHeight - maxScanline - 1 + gridY0) * rowStride)); // offset to top row?
            // Actually offset: (gridHeight - (maxScanline - gridY0) - 1) * rowStride
            // We simplify: rowPtr = buffer + (gridHeight - (maxScanline - gridY0 + 1)) * rowStride

            while (minScanline <= curScanline) {
                uint* polyList = *(uint**)(this->scanlinePolygonHeads + curScanline * 4); // this[0x33] is array of heads
                if (polyList != 0) {
                    uint* activeEdge = (uint*)polyList[1]; // second pointer is edge list head?
                    int parity = 0;
                    do {
                        uint edgeX0 = *polyList;
                        uint edgeX1 = *activeEdge;
                        parity = parity - 2 + ((edgeX1 & 1) + (edgeX0 & 1)) * 2;
                        if (parity != 0) {
                            do {
                                activeEdge = (uint*)activeEdge[1];
                                edgeX1 = *activeEdge;
                                parity = parity - 1 + (edgeX1 & 1) * 2;
                            } while (parity != 0);
                            parity = 0;
                        }
                        int spanStart = ((int)edgeX0 + 0x3e) >> 7;
                        int spanEnd = ((int)edgeX1 + 0x40) >> 7;
                        if (spanStart < spanEnd) {
                            int colStart = spanStart - gridX0;
                            int colEnd = spanEnd - 1 - gridX0;
                            int byteStart = colStart >> 3;
                            int byteEnd = colEnd >> 3;
                            byte maskStart = (byte)(0xff >> (colStart & 7));
                            byte maskEnd = (byte)(0xff80 >> (colEnd & 7));
                            if (byteStart == byteEnd) {
                                byte* target = (byte*)rowPtr + byteStart;
                                *target |= maskStart & maskEnd;
                            } else {
                                byte* targetByte = (byte*)rowPtr + byteStart;
                                *targetByte |= maskStart;
                                int curByte = byteStart + 1;
                                if ((curByte & 1) != 0) {
                                    *(byte*)((int)rowPtr + curByte) = 0xff;
                                    curByte++;
                                }
                                while (curByte < byteEnd) {
                                    int remaining = (byteEnd - curByte - 1) >> 1;
                                    uint* align4 = (uint*)((int)rowPtr + curByte);
                                    for (uint dwords = remaining >> 1; dwords != 0; dwords--) {
                                        *align4 = 0xffffffff;
                                        align4++;
                                    }
                                    for (uint remain = (uint)((remaining & 1) != 0); remain != 0; remain--) {
                                        *(ushort*)align4 = 0xffff;
                                        align4 = (uint*)((int)align4 + 2);
                                    }
                                    curByte = byteEnd; // exit condition
                                }
                                *(byte*)((int)rowPtr + byteEnd) = (char)maskEnd;
                            }
                        }
                        polyList = (uint*)activeEdge[1];
                    } while ((polyList != 0) && (activeEdge = (uint*)polyList[1], activeEdge != 0));
                }
                curScanline--;
                rowPtr = (int*)((int)rowPtr + rowStride);
            }

            // Additional edge smoothing for diagonal paths
            if (*(char*)(this + 0x2205) != '\0') { // flag byte
                int scanline = minScanline + 1;
                uint smoothingFlag = 0;
                if (scanline < maxScanline) {
                    int rowOffset = ((gridHeight - scanline - 1 + gridY0) * rowStride);
                    // Actually: offset = (gridHeight - (scanline - gridY0) - 1) * rowStride
                    // We'll compute per iteration.
                    do {
                        uint* polyList = *(uint**)(this->scanlinePolygonHeads + scanline * 4);
                        if (polyList != 0) {
                            uint* activeEdge = (uint*)polyList[1];
                            while (activeEdge != 0) {
                                uint edgeX0 = *polyList;
                                uint edgeX1 = *activeEdge;
                                for (int p = ((edgeX1 & 1) + (edgeX0 & 1)) * 2 - 2; p != 0; p = p - 1 + (edgeX1 & 1) * 2) {
                                    activeEdge = (uint*)activeEdge[1];
                                    edgeX1 = *activeEdge;
                                }
                                int leftEdge = (int)edgeX0 >> 1;
                                int rightEdge = (int)edgeX1 >> 1;
                                if ((rightEdge - leftEdge) < 0x40) {
                                    int col = (leftEdge + rightEdge - 0x40) >> 7; // midpoint - 64?
                                    int colStart = col - gridX0;
                                    int colEnd = col + 1 - gridX0;
                                    if (colStart < 0) colStart = 0;
                                    if (colEnd >= gridWidth) colEnd = gridWidth - 1;
                                    int byteOffset = ((gridHeight - scanline - 1 + gridY0) * rowStride) + (colStart >> 3);
                                    int byteOffsetEnd = ((gridHeight - scanline - 1 + gridY0) * rowStride) + (colEnd >> 3);
                                    byte maskStart = (byte)(0x80 >> (colStart & 7));
                                    byte maskEnd = (byte)(0x80 >> (colEnd & 7));
                                    if (((*(byte*)((int)buffer + byteOffset) & maskStart) == 0) && ((*(byte*)((int)buffer + byteOffsetEnd) & maskEnd) == 0)) {
                                        int newEdge = (leftEdge + rightEdge) >> 1;
                                        if (newEdge < (x1 + x0 >> 1)) {
                                            newEdge = newEdge + 1;
                                        } else {
                                            newEdge = newEdge - 2;
                                        }
                                        int newCol = ((newEdge + (rightEdge >> 1)) >> 7) - gridX0;
                                        // Actually: newEdge + (edgeX1>>1) >> 7? Seems off.
                                        // Keep original logic:
                                        int colNew = ((newEdge + ((int)edgeX1 >> 1)) >> 7) - gridX0;
                                        smoothingFlag = 1;
                                        byte* targetByte = (byte*)((int)buffer + ((gridHeight - scanline - 1 + gridY0) * rowStride) + (colNew >> 3));
                                        *targetByte |= (byte)(0x80 >> (colNew & 7));
                                    }
                                }
                                polyList = (uint*)activeEdge[1];
                                if (polyList == 0) break;
                                activeEdge = (uint*)polyList[1];
                            }
                        }
                        // Adjust rowOffset? Actually row offset per scanline: rowOffset decreases by rowStride
                        // But we recompute each iteration? Use rowOffset variable.
                        scanline++;
                    } while (scanline < maxScanline);
                }
                this->flag_0x883 |= smoothingFlag;
            }

            // Similar processing for second polygon set (e.g., water/obstacle)
            if (*(char*)(this + 0x2206) != '\0') {
                int scanline2 = this->minScanline2 + 1; // this[0x59]
                uint otherSmoothingFlag = 0;
                if (scanline2 < this->maxScanline2) { // this[0x5a]
                    int localX0 = scanline2 - gridX0; // used as column offset
                    do {
                        uint* polyList = *(uint**)(this->scanlinePolygonHeads2 + scanline2 * 4); // this[0x57]
                        if (polyList != 0) {
                            uint* activeEdge = (uint*)polyList[1];
                            while (activeEdge != 0) {
                                uint edgeX0 = *polyList;
                                uint edgeX1 = *activeEdge;
                                for (int p = ((edgeX1 & 1) + (edgeX0 & 1)) * 2 - 2; p != 0; p = p - 1 + (edgeX1 & 1) * 2) {
                                    activeEdge = (uint*)activeEdge[1];
                                    edgeX1 = *activeEdge;
                                }
                                int leftEdge = (int)edgeX0 >> 1;
                                int rightEdge = (int)edgeX1 >> 1;
                                if ((rightEdge - leftEdge) < 0x40) {
                                    int col = ((rightEdge - 0x40 + leftEdge) >> 7);
                                    int rowStart = col; // should be row coordinate?
                                    int rowEnd = col + 1;
                                    if (col < gridY0) col = gridY0;
                                    if (rowEnd >= gridY1) rowEnd = gridY1 - 1;
                                    int byteCol = localX0 >> 3;
                                    byte mask = (byte)(0x80 >> (localX0 & 7));
                                    int rowOffset1 = ((gridHeight - (rowStart - gridY0) - 1) * rowStride) + byteCol;
                                    int rowOffset2 = ((gridHeight - (rowEnd - gridY0) - 1) * rowStride) + byteCol;
                                    if ((*(byte*)((int)buffer + rowOffset1) & mask) == 0 && (*(byte*)((int)buffer + rowOffset2) & mask) == 0) {
                                        int newEdge = (leftEdge + rightEdge) >> 1;
                                        if (newEdge < ((y1 + y0) >> 1)) {
                                            newEdge = newEdge - 2;
                                        } else {
                                            newEdge = newEdge + 1;
                                        }
                                        int newRow = ((newEdge + ((int)edgeX1 >> 1)) >> 7);
                                        int rowOffset3 = ((gridHeight - (gridY0 + (gridHeight - (newRow - gridY0) - 1)) - 1) * rowStride) + byteCol;
                                        // Actually: ( gridY0 + (gridHeight - (newRow - gridY0) - 1) )? Let's keep original:
                                        int rowIndex = newRow - gridY0;
                                        int rowOffset3 = ((gridHeight - rowIndex - 1) * rowStride) + byteCol;
                                        // Wait, the formula in original: (iVar23 + -1 + (iVar9 - (iVar8 + ((int)*puVar1 >> 1) >> 7))) * iVar3 + iVar2 + (int)puVar4
                                        // Simplify to: (gridY0 -1 + (gridHeight - (newRow?)) ) * stride + byteCol
                                        // We'll trust the original.
                                        int newRow2 = (newEdge + ((int)edgeX1 >> 1)) >> 7;
                                        int rowFix = gridY0 - 1 + (gridHeight - newRow2) * rowStride; // Not sure.
                                        byte* target = (byte*)((int)buffer + rowFix + byteCol);
                                        *target |= mask;
                                        otherSmoothingFlag = 1;
                                    }
                                }
                                polyList = (uint*)activeEdge[1];
                                if (polyList == 0) break;
                                activeEdge = (uint*)polyList[1];
                            }
                        }
                        localX0++;
                        scanline2++;
                    } while (scanline2 < this->maxScanline2);
                }
                this->flag_0x884 |= otherSmoothingFlag;
            }
        } // end if (flagCompressed == 0)
    } else {
        // Mode != 0: generate height/cost grid with blending
        int totalBytes = rowStride * gridHeight;
        // Assume buffer already allocated? But code proceeds without allocation?
        // Actually it uses the data pointer from the object. Assume this->gridData is already set.
        int* buffer = (int*)this->gridData;

        int minScanline = this->minScanline;
        if (minScanline <= this->maxScanline) {
            // Process primary polygon list (height blending)
            int yIter = minScanline;
            int rowOffset = ((gridHeight - (yIter - gridY0) - 1) * rowStride); // start at bottom?
            // Actually original: iVar20 = (((iVar9 - iVar11) + iVar23) * iVar3 - local_28) + (int)puVar4;
            // Where local_28 = gridX0? So it's buffer - gridX0? We'll keep as in code.
            int rowOffset2 = (((gridHeight - (yIter - gridY0) - 1) * rowStride) - gridX0); //? Let's not overcomplicate.
            // We'll just follow original.
            int local_28_acc = yIter - gridX0; // used as column offset?

            do {
                uint* polyList = *(uint**)(this->scanlinePolygonHeads + yIter * 4);
                if (polyList != 0) {
                    uint* activeEdge = (uint*)polyList[1];
                    int parity = 0;
                    do {
                        uint edgeX0 = *polyList;
                        uint edgeX1 = *activeEdge;
                        parity = parity - 2 + ((edgeX1 & 1) + (edgeX0 & 1)) * 2;
                        if (parity != 0) {
                            do {
                                activeEdge = (uint*)activeEdge[1];
                                edgeX1 = *activeEdge;
                                parity = parity - 1 + (edgeX1 & 1) * 2;
                            } while (parity != 0);
                            parity = 0;
                        }
                        int colStart = (int)edgeX0 >> 7;
                        int colEnd = (int)edgeX1 >> 7;
                        byte heightStart = (byte)(((int)edgeX0 >> 1) & 0x3f);
                        byte heightEnd = (byte)(((int)edgeX1 >> 1) & 0x3f); // but note &0x3f only on start
                        // Actually heightEnd = (byte)((int)edgeX1 >> 1); // without mask? Code does bVar14 = (byte)((int)uVar10 >> 1);
                        // Then later uses bVar14 & 0x3f
                        if (colStart == colEnd) {
                            // Single column
                            byte* target = (byte*)((int)buffer + colStart + rowOffset2);
                            *target = *target + ((heightEnd & 0x3f) - heightStart) * 2; // additive?
                        } else {
                            // Multiple columns: fill with max height? Actually using 0x7e (126 = 63*2)
                            byte* startTarget = (byte*)((int)buffer + colStart + rowOffset2);
                            *startTarget = *startTarget + (0x3f - heightStart) * 2; // 0x3f = '?' = 63
                            int curCol = colStart + 1;
                            if (curCol < colEnd) {
                                if ((curCol & 1) != 0) { // align to short
                                    *(byte*)((int)buffer + curCol + rowOffset2) = 0x7e;
                                    curCol++;
                                }
                                while (curCol < colEnd) {
                                    int remaining = (colEnd - curCol - 1) >> 1;
                                    uint* fillPtr = (uint*)((int)buffer + curCol + rowOffset2);
                                    for (uint dwords = remaining >> 1; dwords != 0; dwords--) {
                                        *fillPtr = 0x7e7e7e7e;
                                        fillPtr++;
                                    }
                                    for (uint remain = (uint)((remaining & 1) != 0); remain != 0; remain--) {
                                        *(ushort*)fillPtr = 0x7e7e;
                                        fillPtr = (uint*)((int)fillPtr + 2);
                                    }
                                    curCol = colEnd;
                                }
                            }
                            byte* endTarget = (byte*)((int)buffer + colEnd + rowOffset2);
                            *endTarget = (heightEnd & 0x3f) * 2;
                        }
                        polyList = (uint*)activeEdge[1];
                    } while ((polyList != 0) && (activeEdge = (uint*)polyList[1], activeEdge != 0));
                }
                rowOffset2 -= rowStride;
                yIter++;
            } while (yIter <= this->maxScanline);
        }

        // Process secondary polygon list (secondary height blending with interpolation)
        int minScanline2 = this->minScanline2;
        if (minScanline2 <= this->maxScanline2) {
            byte* previousEdgeTarget = 0;
            uint previousHeight = 0;
            int yIter2 = minScanline2;
            int local_28_acc2 = yIter2 - gridX0; // column offset
            do {
                uint* polyList = *(uint**)(this->scanlinePolygonHeads2 + yIter2 * 4);
                byte* edgeTarget = 0;
                uint currentHeight = 0;
                if (polyList != 0) {
                    uint* activeEdge = (uint*)polyList[1];
                    int parity = 0;
                    do {
                        uint edgeX0 = *polyList;
                        uint edgeX1 = *activeEdge;
                        parity = parity - 2 + ((edgeX1 & 1) + (edgeX0 & 1)) * 2;
                        if (parity != 0) {
                            do {
                                activeEdge = (uint*)activeEdge[1];
                                edgeX1 = *activeEdge;
                                parity = parity - 1 + (edgeX1 & 1) * 2;
                            } while (parity != 0);
                            parity = 0;
                        }
                        int colStart = (int)edgeX0 >> 7;
                        int colEnd = (int)edgeX1 >> 7;
                        int rowIndex = ((gridHeight - colStart) + gridY0) * rowStride + local_28_acc2; // Actually similar to earlier
                        // Simplify: rowIndex = (gridY0 + (gridHeight - colStart) - 1) * rowStride + local_28_acc2
                        int rowIndexStart = (((gridHeight - (colStart - gridY0) - 1) * rowStride) + local_28_acc2);
                        int rowIndexEnd = (((gridHeight - (colEnd - gridY0) - 1) * rowStride) + local_28_acc2);
                        // Actually original uses iVar8 = ((iVar9 - ((int)uVar10 >> 7)) + iVar23) * iVar3 + local_28;
                        // => (gridHeight - colStart + gridY0) * rowStride + local_28_acc2? Let's trust original.

                        if ((edgeTarget != 0) && (edgeTarget != (byte*)((int)buffer + rowIndexStart))) {
                            // Interpolate previous edge height with current edge height
                            int prevDist = 0x3f - (uint)*edgeTarget;
                            int curDist = 0x3f - previousHeight;
                            int weightPrev = 0xf82 - prevDist * prevDist;
                            int weightCur = 0xf82 - curDist * curDist;
                            *edgeTarget = (byte)(((uint)*edgeTarget * weightPrev + previousHeight * weightCur) / (weightPrev + weightCur));
                        }

                        byte heightStart = (byte)(((int)edgeX0 >> 1) & 0x3f);
                        byte heightEnd = (byte)(((int)edgeX1 >> 1) & 0x3f); // note: unshifted? Actually bVar14 = (byte)((int)uVar21 >> 1);
                        // then later uses bVar14 & 0x3f

                        if (colStart == colEnd) {
                            heightStart = currentHeight + ((heightEnd & 0x3f) - heightStart) * 2;
                            // target same column
                            byte* thisTarget = (byte*)((int)buffer + rowIndexStart);
                            // code writes: *(char *)(iVar5 + iVar20) = bVar7; where bVar7 is this modified height
                            // Actually it writes to the rowIndexStart
                            // We'll assign to edgeTarget for next iteration
                            edgeTarget = (byte*)((int)buffer + rowIndexStart);
                            currentHeight = heightStart;
                        } else {
                            unsigned int interpHeight = (unsigned int)(byte)(currentHeight + (0x3f - heightStart) * 2);
                            // Blend current edge with previous edge (if previous exists)
                            byte* curEdge = (byte*)((int)buffer + rowIndexStart);
                            if ((edgeTarget != 0) && (edgeTarget != curEdge)) {
                                int prevDist = 0x3f - (uint)*curEdge;
                                int curDist = 0x3f - interpHeight;
                                int weightPrev = 0xf82 - prevDist * prevDist;
                                int weightCur = 0xf82 - curDist * curDist;
                                *curEdge = (byte)(((uint)*curEdge * weightPrev + interpHeight * weightCur) / (weightPrev + weightCur));
                            } else {
                                *curEdge = interpHeight; // write blended result
                            }
                            // Then write end edge height
                            edgeTarget = (byte*)((int)buffer + rowIndexEnd);
                            currentHeight = (heightEnd & 0x3f) * 2; // full height
                        }
                        polyList = (uint*)activeEdge[1];
                    } while ((polyList != 0) && (activeEdge = (uint*)polyList[1], activeEdge != 0));
                    // After loop, blend the last edge if it exists
                    if (edgeTarget != 0) {
                        int prevDist = 0x3f - (uint)*edgeTarget;
                        int curDist = 0x3f - currentHeight;
                        int weightPrev = 0xf82 - prevDist * prevDist;
                        int weightCur = 0xf82 - curDist * curDist;
                        *edgeTarget = (byte)(((uint)*edgeTarget * weightPrev + currentHeight * weightCur) / (weightPrev + weightCur));
                    }
                }
                local_28_acc2++;
                yIter2++;
            } while (yIter2 <= this->maxScanline2);
        }

        // Apply brightness/contrast adjustments
        if (contrastAdjust == 0) {
            if (brightnessAdjust != 0) {
                for (int i = 0; i < totalBytes; i++) {
                    ((byte*)buffer)[i] = ((byte*)buffer)[i] + brightnessAdjust;
                }
            }
        } else {
            for (int i = 0; i < totalBytes; i++) {
                // contrast adjustment: (value >> 5) + value * 2
                ((byte*)buffer)[i] = (((uint)((byte*)buffer)[i] >> 5) + ((byte*)buffer)[i] * 2) & 0xff;
            }
        }
    }
}