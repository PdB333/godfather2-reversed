// FUN_004236f0: HUDManager::updateAndDisplay
void __thiscall HUDManager::updateAndDisplay(void) {
    int iVar1;
    int* piVar2;
    int fsOffset;
    float fVar3;
    float local_4;

    // Clear a low bit in global HUD state
    g_hudStateFlags = g_hudStateFlags & 0xfe;

    // Begin HUD rendering frame
    HUD::beginDraw();
    HUD::endDraw();

    // Check HUD mode and draw appropriate overlay
    if (this->hudMode == 1) {
        HUD::drawHealthBar(this->param1, this->param2, this->param3, this->param4);
    }
    else if (this->hudMode == 2) {
        HUD::drawMissionText(this->param2, this->param5, this->param6, this->param3);
    }

    // Access thread-local storage for current thread state
    __asm {
        mov eax, fs:[0x2c]  // TIB
        mov iVar1, [eax]
    }

    // Check global game state flag
    if (*(int*)(iVar1 + 0x34) == 0) {
        // Append this HUD object to a global list for rendering
        piVar2 = (int*)(g_hudObjectList + 0x14);
        **(int**)(g_hudObjectList + 0x14) = &g_hudVTable;
        *piVar2 = *piVar2 + 4;
        *(int*)*piVar2 = (int)this;
        *piVar2 = *piVar2 + 4;
    }
    else {
        if ((g_hudStateFlags & 1) == 0) {
            HUD::enableRendering();
        }
        g_hudStateFlags = g_hudStateFlags | 1;
    }

    // Determine screen position from position table or default
    iVar1 = (uint)(*(int*)(iVar1 + 0x34) != 0) * 4;
    if (g_screenPosIndex[iVar1 / 4] == -1) {
        local_4 = g_defaultPosX;
        fVar3 = g_defaultPosY;
    }
    else {
        local_4 = g_screenPositions[g_screenPosIndex[iVar1 / 4]].x;
        fVar3 = g_screenPositions[g_screenPosIndex[iVar1 / 4]].y;
        if (g_screenPositions[g_screenPosIndex[iVar1 / 4]].z == local_4) {
            fVar3 = g_fallbackPosY;
        }
    }

    // Render HUD element at computed position
    HUD::renderElement(local_4, fVar3);
}