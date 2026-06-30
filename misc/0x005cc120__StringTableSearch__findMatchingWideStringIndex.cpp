// FUNC_NAME: StringTableSearch::findMatchingWideStringIndex
int StringTableSearch::findMatchingWideStringIndex() {
    // Compares a wide character string (pointed to by ESI / unaff_ESI) against a static table of wide strings.
    // The table starts at PTR_s_Magnesium_MVB_Std_00f17638 and continues until a NULL pointer sentinel.
    // Returns the zero‑based index of the first match, or -1 if not found.
    
    int index = 0;
    do {
        wchar_t* tableEntry = (&PTR_s_Magnesium_MVB_Std_00f17638)[index];
        wchar_t* target = reinterpret_cast<wchar_t*>(unaff_ESI);  // unaff_ESI is the wide string to search
        wchar_t* targetStart = target;
        
        do {
            wchar_t cTarget = *target;
            bool lessThan = cTarget < *tableEntry;
            if (cTarget != *tableEntry) {
                // Compute comparison result: -1, 0, or 1
                int cmpResult = (1 - static_cast<int>(lessThan)) - static_cast<int>(lessThan != false);
                goto checkMatch;
            }
            if (cTarget == 0) break;
            cTarget = *(target + 1);
            lessThan = cTarget < *(tableEntry + 1);
            if (cTarget != *(tableEntry + 1)) {
                int cmpResult = (1 - static_cast<int>(lessThan)) - static_cast<int>(lessThan != false);
                goto checkMatch;
            }
            target += 2;  // Advance past the two bytes (wide character)
            tableEntry += 2;
        } while (cTarget != 0);
        
        // Full match
        if (false) {
checkMatch:
            if (cmpResult == 0) {
                return index;
            }
        } else {
            // After the inner loop, if a match was found (target reached null after matching all chars)
            // the flag iVar4 was set to 0; we mimic that here.
            int cmpResult = 0;
            if (cmpResult == 0) {
                return index;
            }
        }
        
        index++;
        if (index > 0) {  // Ghidra shows this condition; effectively limits to the first entry only.
            return -1;
        }
    } while (true);
}