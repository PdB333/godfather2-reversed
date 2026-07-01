// FUNC_NAME: UIScrollbarHandler::handleScrollbarEvent
bool __thiscall UIScrollbarHandler::handleScrollbarEvent(void *this, const wchar_t *targetPath)
{
    byte bVar1;
    int cmpResult;
    const wchar_t *comparedString;
    int iVar4;
    undefined4 uVar5;
    const wchar_t *currentPath;
    const wchar_t *otherPath;
    bool bVar8;
    undefined4 uVar9;

    // Global string pointers for scrollbar component paths (Scaleform/GFx movie clip names)
    comparedString = PTR_s__onli_mcMain_scrollbar_arr_up_hs_00e574ac; // "onli_mcMain_scrollbar_arr_up_hs"
    otherPath = PTR_s__onli_mcMain_scrollbar_slider_hs_00e574b4;   // "onli_mcMain_scrollbar_slider_hs"
    currentPath = targetPath;

    // Check if the scrollbar is currently being dragged (slider active)
    if (*(char *)((int)this + 0x180) == '\0') {
        // Not dragging – handle discrete arrow/track clicks
        // Validate that the combined current and target scroll positions are within bounds
        if (DAT_01205214 < *(float *)((int)this + 0x184) + *(float *)((int)this + 0x188)) {
            return false;
        }
        // Reset scroll values to defaults
        *(float *)((int)this + 0x188) = DAT_01205214;   // +0x188: scroll step/range?
        *(undefined4 *)((int)this + 0x184) = DAT_00d8dde0; // +0x184: current position?

        iVar2 = DAT_01129930; // Global context pointer (e.g., UI manager)
        otherPath = targetPath;
        // Compare target path to "arr_up_hs" (arrow up hit state)
        do {
            bVar1 = *comparedString;
            bVar8 = bVar1 < *otherPath;
            if (bVar1 != *otherPath) {
                cmpResult = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                goto LAB_009666b5;
            }
            if (bVar1 == 0) break;
            bVar1 = comparedString[1];
            bVar8 = bVar1 < otherPath[1];
            if (bVar1 != otherPath[1]) goto LAB_009666b0;
            comparedString = comparedString + 2;
            otherPath = otherPath + 2;
        } while (bVar1 != 0);
        cmpResult = 0;
LAB_009666b5:
        comparedString = PTR_s__onli_mcMain_scrollbar_arr_down__00e574b0; // "onli_mcMain_scrollbar_arr_down"
        otherPath = targetPath;
        if (cmpResult == 0) {
            // Arrow up pressed
            FUN_00966250(0xffffffff); // handleScrollUpButton(-1)
            return true;
        }
        // Compare to "arr_down" (arrow down)
        do {
            bVar1 = *comparedString;
            bVar8 = bVar1 < *otherPath;
            if (bVar1 != *otherPath) {
                cmpResult = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                goto LAB_009666f8;
            }
            if (bVar1 == 0) break;
            bVar1 = comparedString[1];
            bVar8 = bVar1 < otherPath[1];
            if (bVar1 != otherPath[1]) goto LAB_009666f3;
            comparedString = comparedString + 2;
            otherPath = otherPath + 2;
        } while (bVar1 != 0);
        cmpResult = 0;
LAB_009666f8:
        comparedString = PTR_s__onli_mcMain_scrollbar_track_hsp_00e574b8; // "onli_mcMain_scrollbar_track_hsp"
        if (cmpResult == 0) {
            // Arrow down pressed
            uVar9 = *(undefined4 *)(DAT_01129930 + 0xe0); // some UI resource?
            uVar5 = FUN_00962e40(uVar9);                  // get track size?
            FUN_009661c0(1, iVar2 + 0xd4, iVar2 + 0xc4, uVar5, uVar9); // update scrollbar track
            return true;
        }
        // Compare to "track_hsp" (track hit shape position)
        do {
            bVar1 = *comparedString;
            bVar8 = bVar1 < *targetPath;
            if (bVar1 != *targetPath) {
                cmpResult = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                goto LAB_00966765;
            }
            if (bVar1 == 0) break;
            bVar1 = comparedString[1];
            bVar8 = bVar1 < targetPath[1];
            if (bVar1 != targetPath[1]) goto LAB_00966760;
            targetPath = targetPath + 2;
            comparedString = comparedString + 2;
        } while (bVar1 != 0);
        cmpResult = 0;
LAB_00966765:
        if (cmpResult == 0) {
            // Track hit – scroll to position
            FUN_00966390(); // handleScrollTrackClick()
        }
        return cmpResult == 0;
    }
    else {
        // Currently dragging (slider active) – handle slider movement
        // Compare target path to "slider_hs" (slider hit state)
        do {
            bVar1 = *otherPath;
            bVar8 = bVar1 < *currentPath;
            if (bVar1 != *currentPath) {
                cmpResult = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                goto LAB_009665f5;
            }
            if (bVar1 == 0) break;
            bVar1 = otherPath[1];
            bVar8 = bVar1 < currentPath[1];
            if (bVar1 != currentPath[1]) goto LAB_009665f0;
            otherPath = otherPath + 2;
            currentPath = currentPath + 2;
        } while (bVar1 != 0);
        cmpResult = 0;
LAB_009665f5:
        bVar8 = cmpResult == 0;
        comparedString = PTR_s__onli_mcMain_scrollbar_track_hsp_00e574b8; // "onli_mcMain_scrollbar_track_hsp"
        if (!bVar8) {
            // Not a slider hit – check for track hit
            do {
                bVar1 = *comparedString;
                bVar8 = bVar1 < *targetPath;
                if (bVar1 != *targetPath) {
                    cmpResult = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
                    goto LAB_0096662a;
                }
                if (bVar1 == 0) break;
                bVar1 = comparedString[1];
                bVar8 = bVar1 < targetPath[1];
                if (bVar1 != targetPath[1]) goto LAB_00966625;
                targetPath = targetPath + 2;
                comparedString = comparedString + 2;
            } while (bVar1 != 0);
            cmpResult = 0;
LAB_0096662a:
            bVar8 = cmpResult == 0;
            if (!bVar8) {
                return bVar8; // neither slider nor track – ignore
            }
        }
        // If slider or track was hit while dragging, process slider release
        FUN_009662f0(); // handleSliderRelease()
        return bVar8;
    }
}