// FUNC_NAME: ScrollableList::updateScrollRows
// Function address: 0x009662f0
// Role: Retrieves the number of rows to scroll from script system, parses it, updates scrolling state, and performs scroll.

#include <cstdio>
#include <cstring>

void ScrollableList::updateScrollRows()
{
    char buffer[256];          // local_100 + local_ff combined
    int scrollRows;            // local_104

    buffer[0] = '\0';
    memset(buffer, 0, sizeof(buffer) - 1); // clear rest

    // Send command to get rows to scroll, with a script context (gScriptContext)
    sendScriptCommand("GetRowsToScroll", buffer, &gScriptContext, 0);

    scrollRows = 0;
    sscanf(buffer, "%d", &scrollRows);

    // Update scroll row count stored in another global (gScrollData)
    setScrollRowCount(buffer, &gScrollData, scrollRows);

    // Notify that scrolling has been updated, passing the original command result
    sendScriptCommand("UpdateScrolling", nullptr, &gScriptContext, 1, buffer);

    // Perform the actual scroll action
    scrollToRow(scrollRows);
}