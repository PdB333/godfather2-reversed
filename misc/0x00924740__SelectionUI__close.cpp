// FUNC_NAME: SelectionUI::close
void __thiscall SelectionUI::close(int thisPtr, bool forceClose)
{
    if (forceClose) {
        // Immediate close: reset all selection state and dispatch close event
        resetSelectionData();                                      // FUN_004c3950
        *(int32_t*)(thisPtr + 0x70) = 0;                          // m_closeTimer
        *(int32_t*)(thisPtr + 0x78) = 0;                          // m_animationState (0 = not animating)
        *(int32_t*)(thisPtr + 0x74) = 3;                          // m_selectionType = 3 (e.g., type 3 = forced)
        setSelectionActive(false);                                 // FUN_0090c960(0)
        updateSelectionVisibility(*(int32_t*)(thisPtr + 0x78) == 1); // FUN_0090ce50 (check if animation state == 1)
        setSelectionType(*(int32_t*)(thisPtr + 0x74));             // FUN_0090d0c0
        executeScriptEvent("CloseSelection", 0, &DAT_00d87288, 0); // FUN_005a04a0 (dispatch script event)
        onCloseComplete();                                         // FUN_00924360
        hideSelectionUI();                                         // FUN_00923500
        clearSelection();                                          // FUN_00923590
        *(uint8_t*)(thisPtr + 0x7c) = 1;                          // m_closingFlag = 1
    }
    *(int32_t*)(thisPtr + 0x50) = 0;                              // m_isOpen = 0 (mark as closed)
}