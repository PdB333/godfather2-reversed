// FUNC_NAME: ItemPool::addItem
// Address: 0x0063ebc0
// Role: Adds an item to the pool, incrementing item count and total added, with a capacity limit check.

void ItemPool::addItem() {
    // Pre-add initialization (e.g., linking to internal structures)
    preAdd(); // FUN_0063fad0

    int currentCount = m_itemCount; // +0x1c: current number of items in pool
    if (currentCount > 0x3ffff) { // pool capacity limit (262143 items)
        // Assert failure: "too many items in a constructor"
        char* msg = debugPrintf("too many %s (limit=%d)", "items in a constructor", 0x3ffff);
        handleAssertion(msg); // FUN_00638b80 likely aborts
    }

    m_totalAdded++;  // +0x20: cumulative count of additions (even across clears?)
    m_itemCount = currentCount + 1; // +0x1c: increment pool item count
}