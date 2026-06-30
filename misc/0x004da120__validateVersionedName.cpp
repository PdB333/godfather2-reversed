// FUNC_NAME: validateVersionedName
// Function at 0x004da120 validates a string matching pattern: <name>_<8hex>_<8hex>_v3
// Returns non-zero (success) or failure code (low 24 bits of address of failure point).
uint __fastcall validateVersionedName(char *name)
{
    char *pCurrent;       // pcVar3 - tracking current position for failure return
    char *pScan;          // pcVar1 - scanning pointer
    char *pSecondSeg;     // pcVar2 - pointer to second hex segment
    char c;               // cVar4
    int iVar5, iVar6;     // temporary chars/indices

    pCurrent = name;
    if (name == nullptr) {
        return 0; // actually returns (uint)pCurrent & 0xffffff00, but pCurrent is nullptr -> 0
    }

    // Validate the main name part: must start with alphanumeric and consist of alphanumeric or underscore
    while (true) {
        c = *name;
        iVar6 = (int)(unsigned char)c;
        // Check if first character is alphanumeric (a-z, A-Z, 0-9). If not, break out early.
        if ((0x19 < iVar6 - 0x61U) && (0x19 < iVar6 - 0x41U)) { // not lowercase and not uppercase
            pCurrent = name;
            if (9 < iVar6 - 0x30U)  // not a digit
                break;
        }
        // At this point, the first char is alphanumeric or we have a digit; continue scanning.
        if (c != '\0') {
            iVar6 = 0;
            do {
                if (c == '_') break; // underscore terminates the name part
                pCurrent = name;
                // Check for max length 10 and alphanumeric only
                if ((10 < iVar6) ||
                    (((iVar5 = (int)(unsigned char)c, 0x19 < iVar5 - 0x61U && (0x19 < iVar5 - 0x41U)) &&
                      (9 < iVar5 - 0x30U)))) {
                    goto LAB_004da25e; // failure: non-alphanumeric or too long
                }
                c = name[1];
                name++;
                iVar6++;
            } while (c != '\0');
        }
        // Now we've hit an underscore or end of string
        pScan = name + 1;
        pCurrent = pScan;
        if (*name != '_') break; // must be followed by underscore

        // First hex segment: expect 8 hex digits
        for (; pScan != name + 8; pScan++) {
            c = *pScan;
            if ((c < '0') || ('9' < c)) { // not a digit
                iVar5 = (int)(unsigned char)c;
                iVar6 = iVar5 + 0x20; // convert to lowercase if uppercase
                if (0x19 < iVar5 - 0x41U) { // not uppercase letter
                    iVar6 = iVar5; // keep as is
                }
                pCurrent = pScan;
                if (iVar6 < 0x61) goto LAB_004da25e; // not a-f (after lowercasing)
                // Must be a-f (so original letter A-F or a-f)
                if (iVar5 - 0x41U < 0x1a) { // if uppercase
                    iVar5 = iVar5 + 0x20; // convert to lowercase
                }
                if (0x66 < iVar5) goto LAB_004da25e; // > 'f'
            }
        }
        // After 8 hex digits, expect an underscore
        pSecondSeg = pScan + 1;
        pCurrent = pSecondSeg;
        if (*pScan != '_') break;

        // Second hex segment: expect 8 hex digits (same logic)
        for (; pSecondSeg != pScan + 8; pSecondSeg++) {
            c = *pSecondSeg;
            if ((c < '0') || ('9' < c)) {
                iVar5 = (int)(unsigned char)c;
                iVar6 = iVar5 + 0x20;
                if (0x19 < iVar5 - 0x41U) {
                    iVar6 = iVar5;
                }
                pCurrent = pSecondSeg;
                if (iVar6 < 0x61) goto LAB_004da25e;
                if (iVar5 - 0x41U < 0x1a) {
                    iVar5 = iVar5 + 0x20;
                }
                if (0x66 < iVar5) goto LAB_004da25e;
            }
        }
        // After second segment, expect underscore followed by "v3"
        pCurrent = pSecondSeg + 1;
        if ((*pSecondSeg != '_') || (c = *pCurrent, pCurrent = pSecondSeg + 2, c != 'v') ||
            (c = *pCurrent, pCurrent = pSecondSeg + 3, c != '3')) break;

        // Finally, must be null-terminated
        if (*pCurrent == '\0') {
            // Success: return non-zero (1)
            return (uint)((int3)((uint)pCurrent >> 8), 1);
            // The CONCAT31 trick: effectively returns 1 (since pCurrent >> 8 is 0 for small pointer)
        }
        // If not null, continue scanning? Actually the code does name = pSecondSeg + 4 and loops back.
        name = pSecondSeg + 4;
    }

LAB_004da25e:
    // Failure: return low 24 bits of pCurrent (address of failure point)
    return (uint)pCurrent & 0xffffff00;
}