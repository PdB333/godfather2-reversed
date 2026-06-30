// FUNC_NAME: EARS::Framework::updateFrame
void EARS::Framework::updateFrame(void)
{
    int iHead;
    int iTail;
    LARGE_INTEGER perfCounter;

    // g_pTaskList points to a structure with head and tail pointers for a linked list of updateable objects
    // +0x04: head, +0x0C: tail, nodes have next pointer at +0x2C
    int* pTaskList = DAT_012234d0;

    // Clear a global flag (possibly "needs special update")
    DAT_01163cf6 = false;

    // Capture high-resolution timestamp for frame timing
    QueryPerformanceCounter(&perfCounter);
    DAT_01194b78 = perfCounter.s.LowPart;   // global QPC low part
    DAT_01194b7c = perfCounter.s.HighPart;  // global QPC high part

    iHead = *(int*)(pTaskList + 4);
    iTail = *(int*)(pTaskList + 0xc);

    // First pass: iterate over all nodes and call a "pre-frame" processing function
    // Note: The function is called with constant 0, suggesting it may use the global list or have side effects on each node.
    if (iHead != iTail)
    {
        do {
            FUN_0051fc90(0);
            iHead = *(int*)(iHead + 0x2c);   // advance via next pointer
        } while (iHead != iTail);
    }

    // If flag was set during first pass, perform a "special" update (e.g., deferred actions)
    if (DAT_01163cf6 != false)
    {
        FUN_0051ead0();
    }

    // Second pass (post-frame), only if not disabled by global flag
    if ((DAT_012054eb == 0) && (iHead = *(int*)(pTaskList + 4), iHead != *(int*)(pTaskList + 0xc)))
    {
        do {
            FUN_0051fc40();
            iHead = *(int*)(iHead + 0x2c);
        } while (iHead != *(int*)(pTaskList + 0xc));
    }
}