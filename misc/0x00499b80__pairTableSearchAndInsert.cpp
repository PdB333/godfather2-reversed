// FUNC_NAME: pairTableSearchAndInsert
int pairTableSearchAndInsert(int secondKey)
{
    int* pairArray;
    int currentIndex;
    int foundIndex = -1;
    int count = DAT_01217d80;

    if (unaff_EDI == 0) {
        return 0;
    }

    // Search for existing pair (unaff_EDI, secondKey)
    if (count > 0) {
        pairArray = &DAT_01217d84;
        currentIndex = 0;
        do {
            if (pairArray[0] == unaff_EDI && pairArray[1] == secondKey) {
                foundIndex = currentIndex;
                if (foundIndex != -1) {
                    goto return_with_increment;
                }
                break;
            }
            currentIndex++;
            pairArray += 2;
        } while (currentIndex < count);
    }

    // Not found, insert if space available
    if (count < 64) { // max 0x40 entries
        if (&DAT_01217d84 + count * 2 != nullptr) { // safety check, always true
            // Store the pair
            *(int*)(&DAT_01217d84 + count * 2) = unaff_EDI; // first element
            *(int*)(&DAT_01217d84 + count * 2 + 4) = secondKey; // second element
            DAT_01217d80 = count + 1;
        }
        foundIndex = count; // new index
    }

return_with_increment:
    return foundIndex + 1;
}