// FUNC_NAME: ScrollBar::scrollBy
void __thiscall ScrollBar::scrollBy(uint delta, uint *scrollOffset, uint *currentIndex, uint maxIndex)
{
    uint uVar1 = *scrollOffset;
    if (uVar1 != 0) {
        if (uVar1 < delta) {
            *scrollOffset = 0;
        } else {
            *scrollOffset = uVar1 - delta;
        }
        *currentIndex = *currentIndex + delta;
        if (maxIndex <= *currentIndex) {
            *currentIndex = maxIndex - 1;
        }
        // vtable[0x70] - likely getScrollPosition() or getScrollbarValue()
        uint scrollPos = (*(code **)(*(int *)this + 0x70))(0);
        // vtable[0x74] - likely updateScrollbar() or refresh()
        uint result = (*(code **)(*(int *)this + 0x74))(0, scrollPos);
        debugPrint(result); // FUN_005a04a0
        // vtable[0x6c] - likely setScrollPosition()
        (*(code **)(*(int *)this + 0x6c))(*scrollOffset);
        // vtable[0x70] again
        uint newScrollPos = (*(code **)(*(int *)this + 0x70))(0);
        debugPrint("UpdateCurrentScroll", 0, newScrollPos);
    }
}