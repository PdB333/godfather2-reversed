//FUNC_NAME: UIElement::draw
// Function address: 0x0094ae10
// Role: Draws a UI element (text or image) with optional color, based on visibility flags and element ID.
// Offsets:
//   +0x11c: flags (uint) - bit 17 = visible, bit 16 = hidden, bit 19 = use custom color
//   +0x150: red byte (color)
//   +0x151: green byte
//   +0x152: blue byte
//   +0x1ac: source text buffer (if text mode)
//   +0x1bc: default text string pointer
//   +0x1cc: mode (0 = image, 1 = text)
//   +0x1d0: visibility bitmask (shifted by graphics quality)
//   +0x1d4: dirty flag (non-zero means needs redraw)
//   +0x194: pointer to array of element IDs (int)
//   +0x198: count of element IDs

void __thiscall UIElement::draw(int this, char visible, int elementId)
{
    int iVar1;
    char cVar2;
    uint uVar3;
    int *piVar4;
    undefined4 uVar5;
    undefined1 *puVar6;
    uint uVar7;
    undefined4 local_68;
    undefined1 local_64[4];
    float colorR;
    float colorG;
    float colorB;
    undefined4 colorA;
    undefined1 buffer[76];

    // Check visibility: if not visible, or if the element is hidden by flag, or forced hidden, skip
    if (((visible == '\0') || ((*(uint *)(this + 0x11c) >> 0x11 & 1) == 0)) ||
        ((*(uint *)(this + 0x11c) >> 0x10 & 1) != 0)) {
        goto defaultCase;
    }

    cVar2 = FUN_00948990(); // Check if UI is globally enabled
    if (cVar2 == '\0') {
        return;
    }

    uVar3 = *(uint *)(this + 0x1d0); // Visibility bitmask
    // Apply shift based on graphics quality setting (global at DAT_01130020 + 0x6c)
    switch (*(undefined4 *)(DAT_01130020 + 0x6c)) {
    case 0:
        break;
    case 1:
        uVar3 = uVar3 >> 3;
        break;
    case 2:
        if ((uVar3 & 4) == 0) {
            iVar1 = *(int *)(DAT_0112e2e8 + 0x58); // Another quality setting (0-2)
            if (iVar1 == 2) {
                uVar3 = uVar3 >> 8;
            }
            else if (iVar1 == 0) {
                uVar3 = uVar3 >> 7;
            }
            else {
                if (iVar1 != 1) goto defaultCase;
                uVar3 = uVar3 >> 9;
            }
            break;
        }
        goto LAB_0094aec2;
    case 3:
        uVar3 = uVar3 >> 5;
        break;
    case 4:
        uVar3 = uVar3 >> 1;
        break;
    case 5:
        uVar3 = uVar3 >> 6;
        break;
    default:
        goto defaultCase;
    }

    if ((uVar3 & 1) != 0) {
LAB_0094aec2:
        // Check if elementId is in the allowed list
        uVar3 = *(uint *)(this + 0x198); // Count of element IDs
        uVar7 = 0;
        if (uVar3 != 0) {
            piVar4 = (int *)(*(int *)(this + 0x194) + 4); // Skip first element? Actually array of ints, each pair? Wait: +4 suggests skipping first int? But loop uses *piVar4 and increments by 2 ints (8 bytes). So array is pairs of ints? Or maybe it's an array of structs with two ints? The code: piVar4 = piVar4 + 2; so each element is 8 bytes. The first int at offset 0 might be something else? Actually piVar4 starts at (*(int*)(this+0x194) + 4), so skipping 4 bytes. Then compares *piVar4 (first int of pair) with elementId. So each pair: first int is ID, second int is something else. We'll treat as ID array.
            do {
                if (*piVar4 == elementId) goto found;
                uVar7 = uVar7 + 1;
                piVar4 = piVar4 + 2;
            } while (uVar7 < uVar3);
        }
        // If count is zero, treat as always found
        if (uVar3 == 0) {
found:
            if (*(int *)(this + 0x1d4) != 0) {
                return; // Already dirty, skip
            }
            cVar2 = FUN_0094a7b0(buffer); // Fill buffer with text data (returns success)
            if (cVar2 == '\0') {
                return;
            }
            if (*(int *)(this + 0x1cc) == 1) {
                // Text mode: draw formatted text
                local_68 = 0;
                uVar5 = FUN_004df270(local_64, this + 0x1ac, buffer, 0x2ff, 4, &local_68);
            }
            else {
                // Image mode: draw using default string
                puVar6 = *(undefined1 **)(this + 0x1bc);
                if (puVar6 == (undefined1 *)0x0) {
                    puVar6 = &DAT_0120546e; // Default empty string
                }
                uVar5 = FUN_0045c740(local_64, puVar6, buffer, 0x2ff, 4, 0, 0xffffffff, 0);
            }
            FUN_00414db0(uVar5); // Begin draw
            FUN_00414df0();      // End draw (or commit)
            if (*(int *)(this + 0x1d4) == 0) {
                return;
            }
            // If custom color flag is set, apply color
            if ((*(uint *)(this + 0x11c) >> 0x13 & 1) == 0) {
                return;
            }
            colorR = (float)*(byte *)(this + 0x150);
            colorG = (float)*(byte *)(this + 0x151);
            colorB = (float)*(byte *)(this + 0x152);
            colorA = 0; // Alpha set to 0 (maybe full transparent? Or default?)
            FUN_004df760(&colorR); // Set draw color (takes pointer to float array of 4)
            return;
        }
    }

defaultCase:
    if (*(int *)(this + 0x1d4) != 0) {
        FUN_004df630(); // Reset color or cleanup
    }
    return;
}