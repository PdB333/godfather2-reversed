// FUNC_NAME: LicenseValidator::validateKey
// Address: 0x00904b60
// This function checks if a given 128-bit license key (4 ints) matches any of three stored license strings.
// It uses a two-step resource lookup: openLicenseData (by name) then getLicenseData (returns pointer to 4 ints).
// Returns 1 if key matches any stored license, 0 otherwise.

// External library functions (part of EA EARS engine)
void openLicenseData(const char* name);    // FUN_004da550
int* getLicenseData(void* buffer);          // FUN_004da7e0 - fills buffer and returns pointer to data
void closeLicenseData();                    // FUN_004d8be0 - release global state
void deleteLicenseHandle(int handle);       // FUN_009c8eb0 - free handle

char validateKey(int* key)
{
    bool bMatchedAny = false;
    int handle1 = 0;
    int handle2 = 0;
    int handle3 = 0;
    int* dataPtr;
    char result = 0;

    // Check first license: "XENTKOWSKI_C9388CF_4754D41_v3"
    openLicenseData("XENTKOWSKI_C9388CF_4754D41_v3");
    dataPtr = getLicenseData(NULL); // Assuming buffer is not needed, or use stack buffer
    if ((key[0] == dataPtr[0]) && (key[1] == dataPtr[1]) &&
        (key[2] == dataPtr[2]) && (key[3] == dataPtr[3]))
    {
        bMatchedAny = true;
        result = 1;
        // If match, no need to check others; but cleanup for handle1 not needed here? Actually logic flows: if match, still sets handle1=0 but later cleanup only if matched and handle non-zero.
        // The original code sets local_4=0 before this first check, so handle1 is 0, so cleanup skipped.
        // It falls through to return 1 (uVar3=1).
        // But note: original code only sets uVar3=1 after successful match, and then does cleanup for any previous non-zero handles.
    }
    else
    {
        // Not first license, try second:
        bMatchedAny = true;
        handle2 = 0; // local_1c
        openLicenseData("XENTKOWSKI_C9406C2_15B317B_v3");
        dataPtr = getLicenseData(NULL);
        if ((key[0] == dataPtr[0]) && (key[1] == dataPtr[1]) &&
            (key[2] == dataPtr[2]) && (key[3] == dataPtr[3]))
        {
            bMatchedAny = true;
            handle2 = 0; // still 0, but original sets local_1c=0 before check, so it's 0 anyway
            result = 1;
        }
        else
        {
            // Not second, try third:
            bMatchedAny = true;
            handle3 = 0; // local_34
            openLicenseData("XENTKOWSKI_C9410DD_B49BA97_v3");
            dataPtr = getLicenseData(NULL);
            if ((key[0] == dataPtr[0]) && (key[1] == dataPtr[1]) &&
                (key[2] == dataPtr[2]) && (key[3] == dataPtr[3]))
            {
                result = 1;
            }
            else
            {
                result = 0;
                // No match; cleanup handles if any were set (but they are 0)
            }
        }
    }

    // Cleanup any non-zero handles (although in this code they are always 0)
    if (bMatchedAny && handle3 != 0) {
        closeLicenseData();
        deleteLicenseHandle(handle3);
    }
    if (bMatchedAny && handle2 != 0) {
        closeLicenseData();
        deleteLicenseHandle(handle2);
    }
    if (handle1 != 0) {
        closeLicenseData();
        deleteLicenseHandle(handle1);
    }

    return result;
}