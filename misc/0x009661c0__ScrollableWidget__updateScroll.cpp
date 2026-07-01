// FUNC_NAME: ScrollableWidget::updateScroll
void __thiscall ScrollableWidget::updateScroll(int *this, int deltaScroll, int *pScrollPos, uint *pRemaining, uint pageSize, uint maxScroll)
{
    // Check if we can scroll: currentPos + pageSize < maxScroll
    if (*pScrollPos + pageSize < maxScroll)
    {
        int newPos = *pScrollPos + deltaScroll;
        *pScrollPos = newPos;

        // Clamp so that the scroll doesn't go beyond the max minus page size
        if (maxScroll < newPos + pageSize)
        {
            *pScrollPos = maxScroll - pageSize;
        }

        // Update remaining scroll distance
        *pRemaining = *pRemaining - deltaScroll;
        if (pageSize <= *pRemaining)
        {
            *pRemaining = 0;
        }

        // Vtable call at +0x70: likely GetClientArea() or similar
        int v0 = (**(code **)(*this + 0x70))(0);
        // Vtable call at +0x74: some method taking two args (0 and the result above)
        int v1 = (**(code **)(*this + 0x74))(0, v0);
        DebugLog(v1);

        // Vtable call at +0x6c: SetScrollPosition(*pScrollPos)
        (**(code **)(*this + 0x6c))(*pScrollPos);

        v0 = (**(code **)(*this + 0x70))(0);
        DebugLog("UpdateCurrentScroll", 0, v0);
    }
}