// FUNC_NAME: LayoutContainer::layoutItems
// Address: 0x00897370
// This function computes the layout rectangle of a container based on its child items.
// It processes an array of item descriptors (each 16 bytes) stored at +0x4, with count at +0xC.
// Item structure: [0x00] int type, [0x04] float value, [0x08] byte flags (bit0 = visible).
// If any visible child exists, the container becomes visible and its bounding rectangle is computed.
// Globals: g_screenWidth (DAT_00e44564) and g_statusBarHeight (DAT_00d77a94).

void LayoutContainer::layoutItems() {
    uint itemIndex = 0;
    float maxValue = 0.0f;           // fVar5: tracks maximum value among visible items
    float specialValue = 0.0f;       // fVar7: value of the item with type 0x100 (e.g., "fill" item)

    if (this->itemCount != 0) {
        Item* items = this->items;   // +0x4
        do {
            if ((items->flags & 1) != 0) {   // Check if item is visible (bit 0)
                this->flags |= 1;             // Set container visibility flag (+0x58)
                float itemValue = items->value; // +0x04
                if (maxValue < itemValue) {
                    maxValue = itemValue;
                }
                if (items->type == 0x100) {    // Special "stretch" or "width" item
                    specialValue = itemValue;
                }
            }
            itemIndex++;
            items++;
        } while (itemIndex < this->itemCount);
    }

    float screenWidth = g_screenWidth;      // DAT_00e44564
    float statusBarHeight = g_statusBarHeight; // DAT_00d77a94

    if ((this->flags & 1) != 0) {           // Container has visible children
        float totalWidth = maxValue + statusBarHeight;   // fVar5
        this->field_0x3c = 0;                            // Left margin? Set to 0
        this->rectLeft = screenWidth - totalWidth;       // +0x30
        this->rectRight = screenWidth - totalWidth;      // +0x38 (same as left – likely a square/centered)
        this->rectTop = screenWidth - (specialValue + statusBarHeight); // +0x34
        this->rectWidth = totalWidth;                    // +0x40
        this->rectHeight = statusBarHeight;              // +0x44
        this->anotherWidth = totalWidth;                 // +0x48 (maybe duplicate)
        this->field_0x4c = 0;                            // Right margin? Set to 0
        FUN_008971c0();      // Likely triggers a redraw or layout update
    }
}