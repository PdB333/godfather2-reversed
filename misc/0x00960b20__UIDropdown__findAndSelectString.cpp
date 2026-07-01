// FUNC_NAME: UIDropdown::findAndSelectString

bool __thiscall UIDropdown::findAndSelectString(void* thisPtr, const wchar_t* targetString)
{
    // Buffer for copying option strings (up to 512 wchar_t = 1024 bytes)
    wchar_t optionBuffer[256]; // local_200 is 512 bytes, so 256 wchar_t

    // Index used for iterating through dropdown options
    int currentIndex = 0;

    do {
        // Fetch the option string at index currentIndex from storage at +0x804
        getDropdownOptionString(optionBuffer, 256, (uint32_t*)((uint8_t*)thisPtr + 0x804), currentIndex);

        // Pointer to optionBuffer
        wchar_t* optionPtr = optionBuffer;
        // Pointer to target string
        const wchar_t* targetPtr = targetString;
        int cmpResult;

        // Wide-character comparison (comparing two bytes at a time)
        while (true) {
            wchar_t optChar = *optionPtr;
            wchar_t tgtChar = *targetPtr;
            if (optChar != tgtChar) {
                cmpResult = (optChar < tgtChar) ? -1 : 1;
                break;
            }
            if (optChar == L'\0') {
                // Both strings are equal up to null terminator
                cmpResult = 0;
                break;
            }
            ++optionPtr;
            ++targetPtr;
        }

        if (cmpResult == 0) {
            // Found a match: update dropdown selection
            int prevIndex = *(int*)((uint8_t*)thisPtr + 0xa04);
            if (prevIndex != currentIndex) {
                // Play "roll out" sound for the previous selection
                getDropdownOptionString(optionBuffer, 256, &DAT_00e3266c, prevIndex);
                playUISound(L"RollOutDropSelection", 0, DAT_00d8d668, 1, optionBuffer);

                // Update stored selection index
                *(int*)((uint8_t*)thisPtr + 0xa04) = currentIndex;

                // Play "roll over" sound for the new selection
                getDropdownOptionString(optionBuffer, 256, &DAT_00e3266c, currentIndex);
                playUISound(L"RollOverDropSelection", 0, DAT_00d8d668, 1, optionBuffer);

                // Reset local sound state (maybe stop any ongoing sound transition)
                uint32_t soundParams[3] = { DAT_011304d8, 0, 0 };
                resetSoundParams(soundParams, 0);
            }
            return true; // selection found and updated
        }

        currentIndex++;
        if (currentIndex > 19) { // 0x13 is 19, so at most 20 entries
            return false; // no match
        }
    } while (true);
}