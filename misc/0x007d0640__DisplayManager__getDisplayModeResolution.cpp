// FUNC_NAME: DisplayManager::getDisplayModeResolution
void DisplayManager::getDisplayModeResolution(int modeIndex, uint32_t* outWidth, uint32_t* outHeight)
{
    // Globals:
    // g_currentDisplayMode: 0x00d5780c  (maybe current resolution/display data)
    // g_pDisplayManager:    0x01223484  (pointer to display manager singleton)
    // g_resolutionTable:    0x00e52fac, 0x00e52fb0, 0x00e52fb4, 0x00e52fb8,
    //                       0x00e52fbc, 0x00e52fc0, 0x00e52fc4, 0x00e52fc8

    uint32_t uVar2 = *(uint32_t*)0x00d5780c;   // _DAT_00d5780c
    bool bFullscreenOrSomething;
    void* pDisplayMgr = *(void**)0x01223484;    // DAT_01223484

    if ((pDisplayMgr == NULL) || (*(uint32_t*)((char*)pDisplayMgr + 0xc) == 0)) {
        bFullscreenOrSomething = false;
    } else {
        bFullscreenOrSomething = true;
    }

    switch (modeIndex) {
        case 0:
            *outWidth  = *(uint32_t*)0x00d5780c;  // _DAT_00d5780c
            *outHeight = uVar2;
            return;
        case 1:
            break;
        case 2:
            *outWidth = *(uint32_t*)0x00d5780c;   // _DAT_00d5780c
            if (!bFullscreenOrSomething) {
                *outHeight = *(uint32_t*)0x00e52fbc;  // DAT_00e52fbc
                return;
            }
            *outHeight = *(uint32_t*)0x00e52fc0;  // DAT_00e52fc0
            return;
        case 3:
            *outWidth = *(uint32_t*)0x00d5780c;  // _DAT_00d5780c
            if (bFullscreenOrSomething) {
                *outHeight = *(uint32_t*)0x00e52fc8;  // DAT_00e52fc8
                return;
            }
            *outHeight = *(uint32_t*)0x00e52fc4;  // DAT_00e52fc4
            return;
        default:
            return;
    }

    // case 1 falls through here
    uVar2 = *(uint32_t*)0x00e52fac;  // DAT_00e52fac
    if (bFullscreenOrSomething) {
        uVar2 = *(uint32_t*)0x00e52fb4;  // DAT_00e52fb4
    }
    *outWidth = uVar2;

    if (!bFullscreenOrSomething) {
        *outHeight = *(uint32_t*)0x00e52fb0;  // DAT_00e52fb0
        return;
    }
    *outHeight = *(uint32_t*)0x00e52fb8;  // DAT_00e52fb8
    return;
}