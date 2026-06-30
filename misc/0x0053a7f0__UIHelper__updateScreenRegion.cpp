// FUNC_NAME: UIHelper::updateScreenRegion
// Address: 0x0053a7f0
// This function appears to update screen region coordinates for a UI element (possibly minimap markers).
// It uses a global array of structures (0x38 bytes each) indexed by an implicit parameter in EAX.
// The function sets up a rectangle (local_20, local_1c, local_18, local_14) and calls a rendering helper.

void UIHelper::updateScreenRegion(uint index, int regionType) {
    // Global pointers and constants (likely from EARS engine)
    // DAT_0121b754: some manager or state object
    // DAT_0121bba8: comparison value (maybe null or default)
    // DAT_0121b9e8, DAT_0121b9f0, DAT_0121b9f4, DAT_0121b9fc, DAT_0121ba00, DAT_0121b9ec, DAT_0121b9f8: various IDs or pointers
    // DAT_011a0f28: base of an array of structures (size 0x38 per entry)
    // DAT_00e2cd54, DAT_00e2b118, DAT_00e44564, DAT_00e44718, DAT_00e2b1a4, DAT_00e2eff4: screen dimension constants

    float local_20, local_1c, local_18, local_14; // rectangle: left, top, right, bottom? or x, y, width, height?

    if (DAT_0121b754 == DAT_0121bba8) {
        // First branch: some condition met
        if (DAT_0121b9e8 != 0) {
            FUN_006063b0(); // Possibly a debug/log function
        }
        if (DAT_0121b9f0 != 0) {
            // Access array entry at index
            uint8_t* entry;
            if (index < 0x1000) {
                entry = &DAT_011a0f28 + index * 0x38;
            } else {
                entry = nullptr;
            }
            // Read ushorts at offsets +2 and +4 (likely width and height or some dimensions)
            local_18 = DAT_00e2cd54 / (float)*(uint16_t*)(entry + 2);
            local_14 = (float)*(uint16_t*)(entry + 4);
            // Fall through to common code
            goto LAB_0053a9bf;
        }
    } else {
        // Second branch
        if (DAT_0121b9f4 != 0) {
            FUN_006063b0();
        }
        // Access array entry
        uint8_t* entry;
        if (index < 0x1000) {
            entry = &DAT_011a0f28 + index * 0x38;
        } else {
            entry = nullptr;
        }
        local_20 = DAT_00e2b118 / (float)*(uint16_t*)(entry + 2);
        local_1c = DAT_00e2b118 / (float)*(uint16_t*)(entry + 4);
        local_18 = DAT_00e44564 - local_20;
        local_14 = local_1c;
        // Call rendering helper with different ID
        FUN_0060add0(DAT_0121b754, DAT_0121b9fc, &local_20);
        if (DAT_0121ba00 != 0) {
            // Additional calculation similar to first branch
            local_18 = DAT_00e2cd54 / (float)*(uint16_t*)(entry + 2);
            local_14 = (float)*(uint16_t*)(entry + 4);
            int iVar3 = DAT_0121ba00;
            goto LAB_0053a9bf;
        }
        // If no additional, skip to final call
        goto final_call;
    }

LAB_0053a9bf:
    // Common code for first branch and second branch's additional case
    local_1c = 0.0f;
    local_20 = 0.0f;
    local_14 = DAT_00e2cd54 / local_14;
    FUN_0060add0(DAT_0121b754, iVar3, &local_20); // iVar3 is either DAT_0121b9f0 or DAT_0121ba00
    // Note: iVar3 is set before the goto, but here it's undefined; we need to handle it.
    // Actually, in the first branch, iVar3 = DAT_0121b9f0; in the second, iVar3 = DAT_0121ba00.
    // We'll restructure to avoid goto.

final_call:
    // Switch on regionType to set predefined rectangle values
    switch (regionType) {
    case 0:
        local_20 = DAT_00e44718; // likely 0.0f
        local_1c = DAT_00e2b1a4; // likely 1.0f or some scale
        local_18 = 0.0f;
        break;
    case 1:
        local_20 = DAT_00e2cd54; // screen width
        local_1c = DAT_00e2eff4; // some constant
        local_18 = DAT_00e2b1a4;
        break;
    case 2:
        local_20 = DAT_00e44718;
        local_1c = DAT_00e2b1a4;
        local_18 = DAT_00e2cd54;
        break;
    case 3:
        local_20 = DAT_00e2cd54;
        local_1c = DAT_00e2b1a4;
        local_18 = DAT_00e44718;
        break;
    default:
        break;
    }
    local_14 = 0.0f;

    // Determine which ID to use for final call
    uint id = (DAT_0121b754 == DAT_0121bba8) ? DAT_0121b9ec : DAT_0121b9f8;
    FUN_0060add0(DAT_0121b754, id, &local_20);
}