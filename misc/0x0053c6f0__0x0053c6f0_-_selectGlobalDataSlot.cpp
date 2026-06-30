// FUNC_NAME: 0x0053c6f0 - selectGlobalDataSlot
void selectGlobalDataSlot(int slotIndex)
{
    void* selectedDataA = nullptr;
    void* selectedDataB = nullptr;

    switch (slotIndex)
    {
    case 0:
        selectedDataA = DAT_01198e54;
        goto LAB_0053c705;
    case 1:
        selectedDataA = DAT_0121990c;
        goto LAB_0053c720;
    case 2:
        selectedDataA = DAT_01198e4c;
        goto LAB_0053c705;
    case 3:
        selectedDataA = DAT_01198e70;
        goto LAB_0053c742;
    case 4:
        selectedDataA = DAT_01198e64;
        selectedDataB = DAT_01198e74;
        break;
    case 5:
        selectedDataA = DAT_01198e68;
        goto LAB_0053c742;
    case 6:
        selectedDataA = DAT_01198e50;
        selectedDataB = DAT_01198e48;
        break;
    case 7:
        selectedDataA = DAT_01198e58;
        goto LAB_0053c742;
    case 8:
        selectedDataA = DAT_01198e78;
        selectedDataB = DAT_01198e74;
        break;
    case 9:
        selectedDataA = DAT_01198e6c;
        // fall through to LAB_0053c742
        goto LAB_0053c742;
    case 10:
        selectedDataA = DAT_01198e60;
        selectedDataB = DAT_01198e48;
        break;
    case 0xB: // 11
        selectedDataA = DAT_01194d04;
        goto LAB_0053c720;
    case 0xC: // 12
        selectedDataA = DAT_01198e5c;
        goto LAB_0053c705;
    }

    // Common path for goto targets
    // LAB_0053c720: sets selectedDataB = DAT_01219900
    // LAB_0053c742: sets selectedDataB = DAT_01198e48
    // LAB_0053c705: sets selectedDataB = DAT_01219900

    // Note: These labels are handled by the goto statements in the switch.
    // Since goto is messy, we'll restructure with fallthrough comments.

    // However, to preserve logic, we'll use a separate block after switch
    // that applies the default assignments for the cases that jumped.

    // Actually, better to integrate the goto targets into case bodies.
    // Let's rewrite properly:

    // We'll use a helper variable to indicate which label was targeted.
    // But for clarity, I'll keep the original goto structure in comments and rewrite.

    // Since the decompiled code uses goto, we'll simulate with a switch that
    // has case blocks that set both variables and break appropriately.

    // Let's redo the switch with proper fallthrough:

    // I'll rewrite the entire switch to be cleaner:

    /*
    switch (slotIndex) {
    case 0:
        selectedDataA = DAT_01198e54;
        selectedDataB = DAT_01219900;
        break;
    case 1:
        selectedDataA = DAT_0121990c;
        selectedDataB = DAT_01219900;
        break;
    case 2:
        selectedDataA = DAT_01198e4c;
        selectedDataB = DAT_01219900;
        break;
    case 3:
        selectedDataA = DAT_01198e70;
        selectedDataB = DAT_01198e48;
        break;
    case 4:
        selectedDataA = DAT_01198e64;
        selectedDataB = DAT_01198e74;
        break;
    case 5:
        selectedDataA = DAT_01198e68;
        selectedDataB = DAT_01198e48;
        break;
    case 6:
        selectedDataA = DAT_01198e50;
        selectedDataB = DAT_01198e48;
        break;
    case 7:
        selectedDataA = DAT_01198e58;
        selectedDataB = DAT_01198e48;
        break;
    case 8:
        selectedDataA = DAT_01198e78;
        selectedDataB = DAT_01198e74;
        break;
    case 9:
        selectedDataA = DAT_01198e6c;
        selectedDataB = DAT_01198e48;
        break;
    case 10:
        selectedDataA = DAT_01198e60;
        selectedDataB = DAT_01198e48;
        break;
    case 0xB:
        selectedDataA = DAT_01194d04;
        selectedDataB = DAT_01219900;
        break;
    case 0xC:
        selectedDataA = DAT_01198e5c;
        selectedDataB = DAT_01219900;
        break;
    }
    */

    // But the decompiled code has goto and then after the switch, there is
    // a conditional release. So we need to follow the actual flow.

    // I'll implement exactly as the decompiled code, using goto in C++.
    // It's acceptable for reverse engineering reconstruction.

    // However, we need to handle the fact that some cases set both variables
    // and some set only selectedDataA and then goto a common label that sets B.

    // Let's replicate the original structure:

    void* selectedDataA = nullptr;
    void* selectedDataB = nullptr;

    switch (slotIndex) {
    case 0:
        selectedDataA = DAT_01198e54;
        goto LAB_0053c705;
    case 1:
        selectedDataA = DAT_0121990c;
        goto LAB_0053c720;
    case 2:
        selectedDataA = DAT_01198e4c;
        goto LAB_0053c705;
    case 3:
        selectedDataA = DAT_01198e70;
        goto LAB_0053c742;
    case 4:
        selectedDataA = DAT_01198e64;
        selectedDataB = DAT_01198e74;
        break;
    case 5:
        selectedDataA = DAT_01198e68;
        goto LAB_0053c742;
    case 6:
        selectedDataA = DAT_01198e50;
        selectedDataB = DAT_01198e48;
        break;
    case 7:
        selectedDataA = DAT_01198e58;
        goto LAB_0053c742;
    case 8:
        selectedDataA = DAT_01198e78;
        selectedDataB = DAT_01198e74;
        break;
    case 9:
        selectedDataA = DAT_01198e6c;
        goto LAB_0053c742;
    case 10:
        selectedDataA = DAT_01198e60;
        selectedDataB = DAT_01198e48;
        break;
    case 0xB:
        selectedDataA = DAT_01194d04;
        goto LAB_0053c720;
    case 0xC:
        selectedDataA = DAT_01198e5c;
        goto LAB_0053c705;
    }

    // Labels for goto targets
    // These are after the switch, but since we use goto, we need to place them
    // before the final if block.

    // In the original code, the labels are inside the switch? No, they are outside.
    // Let's check: The decompiled code shows:
    //   switch(in_EAX) {
    //   case 0: ... goto LAB_0053c705;
    //   case 1: ... goto LAB_0053c720;
    //   ... }
    //   if (DAT_012058e8 == &DAT_0121bc10) { ... }
    // But then after the switch, there are labels: LAB_0053c705, LAB_0053c720, LAB_0053c742.
    // Actually, in the decompiled code, the labels appear within the switch bodies,
    // but they are also used as jump targets from multiple cases.
    // The decompiled code structure is:

    // switch(in_EAX) {
    // case 0: DAT_... = ...; goto LAB_0053c705;
    // case 1: DAT_... = ...; goto LAB_0053c720;
    // ...
    // case 9: DAT_... = ...; LAB_0053c742: DAT_... = ...; break;  (??? confusion)
    // Actually look at original decompiled:
    // case 9: ... DAT_0121bc24 = ...; LAB_0053c742: DAT_0121bc20 = ...; break;
    // That means for case 9, it sets DAT_0121bc24 and then falls into LAB_0053c742 which sets DAT_0121bc20 and then break.
    // So LAB_0053c742 is a label inside the switch block for case 9, but other cases also goto it.
    // Similarly for LAB_0053c705 and LAB_0053c720.

    // So the labels are inside the switch, but they appear after the switch in the control flow because of gotos.
    // The actual assembly probably has the labels within the jump table.

    // To keep it simple, I'll restructure using explicit assignments per case without goto, as I noted above.
    // The logic is the same: each case sets both selectedDataA and selectedDataB.
    // The decompiled code's goto is just a way to avoid duplicate B assignments.

    // I'll produce a clean version without goto:

    void* selectedDataA = nullptr;
    void* selectedDataB = nullptr;

    switch (slotIndex) {
    case 0:
        selectedDataA = DAT_01198e54;
        selectedDataB = DAT_01219900;
        break;
    case 1:
        selectedDataA = DAT_0121990c;
        selectedDataB = DAT_01219900;
        break;
    case 2:
        selectedDataA = DAT_01198e4c;
        selectedDataB = DAT_01219900;
        break;
    case 3:
        selectedDataA = DAT_01198e70;
        selectedDataB = DAT_01198e48;
        break;
    case 4:
        selectedDataA = DAT_01198e64;
        selectedDataB = DAT_01198e74;
        break;
    case 5:
        selectedDataA = DAT_01198e68;
        selectedDataB = DAT_01198e48;
        break;
    case 6:
        selectedDataA = DAT_01198e50;
        selectedDataB = DAT_01198e48;
        break;
    case 7:
        selectedDataA = DAT_01198e58;
        selectedDataB = DAT_01198e48;
        break;
    case 8:
        selectedDataA = DAT_01198e78;
        selectedDataB = DAT_01198e74;
        break;
    case 9:
        selectedDataA = DAT_01198e6c;
        selectedDataB = DAT_01198e48;
        break;
    case 10:
        selectedDataA = DAT_01198e60;
        selectedDataB = DAT_01198e48;
        break;
    case 0xB:
        selectedDataA = DAT_01194d04;
        selectedDataB = DAT_01219900;
        break;
    case 0xC:
        selectedDataA = DAT_01198e5c;
        selectedDataB = DAT_01219900;
        break;
    default:
        return; // no matching slot
    }

    // Store the selected data into global variables (likely members of a manager)
    DAT_0121bc24 = selectedDataA;
    DAT_0121bc20 = selectedDataB;

    // If a specific global points to a structure, release old resources
    if (DAT_012058e8 == &DAT_0121bc10) {
        releaseResource(selectedDataA);
        releaseResource(selectedDataB);
    }

    // Search for the selected data A in the 13-element table
    uint32_t indexA = 0;
    do {
        if (PTR_DAT_010beba0[indexA] == selectedDataA) {
            // Set a pointer to a slot in an array of 0x20-byte structures
            DAT_0121be7c = (uint8_t*)&DAT_0121bcdc + indexA * 0x20;
            break;
        }
        indexA++;
    } while (indexA < 13);

    // Search for the selected data B in the 3-element table
    uint32_t indexB = 0;
    do {
        if (PTR_DAT_010bebd4[indexB] == selectedDataB) {
            // Set a pointer to a slot in an array of 0xC-byte structures
            DAT_0121bcd8 = (uint8_t*)0x121bcb4 + indexB * 0xC;
            return;
        }
        indexB++;
    } while (indexB < 3);
}

// Note: Actual global variable names and types are unknown.
// These would need to be defined elsewhere based on original symbols.
// The function uses __fastcall or custom calling convention (parameter in EAX).
// We've added 'int slotIndex' parameter for clarity.
// The decompiled code uses in_EAX, so it's likely a hidden parameter.
// For reconstruction, we treat it as a normal int parameter.