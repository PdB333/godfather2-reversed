// Xbox PDB: EARS_Apt_UIFrontend_ConnectingToPlasma
// FUNC_NAME: OnlineServices::submitAccountCreation
void OnlineServices::submitAccountCreation(int *thisPtr) {
    char isValid;
    int someIndex;
    const char *accountName;
    const char *password1;
    const char *password2;
    int (*destructor1)(void *);
    int (*destructor2)(void *);
    int (*destructor3)(void *);
    int tempArray[3];
    const char **outputStrings;

    // Check if a global flag (likely error state) is set
    if (*(int *)(DAT_012234b8 + 8) == 0) {
        // Call a virtual method (likely showError or abort)
        (*(void (**)(void))(*(int *)thisPtr + 0x2c))();
        FUN_00934ec0(); // Some error handling function
        return;
    }

    // Free/reset some buffers in the object at offset 0x1c (likely a sub-struct)
    // Offsets +0x10, +0x5c, +0xa8 probably represent password, confirm password, account name
    FUN_004d3b50(thisPtr[0x1c] + 0x10);
    FUN_004d3b50(thisPtr[0x1c] + 0x5c);
    FUN_004d3b50(thisPtr[0x1c] + 0xa8);

    // Parse the form data: likely extracts account name, password1, password2
    isValid = FUN_00401e20(&password1, &someIndex); // Returns 0 if invalid

    if (isValid == 0) {
        int accountResult = FUN_009c8e50(0xf0); // Check account existence
        if (accountResult == 0) {
            accountResult = 0;
            outputStrings = "$mp_online_invalid_password_match";
        } else {
            accountResult = FUN_00982280(0); // Another validation
            outputStrings = "$mp_online_invalid_password_match";
        }
        // Fall through to error
    } else {
        // Check if some index value is within range (likely form field count)
        if (someIndex - 4U < 0xd) {
            // Use password2 if not null, else default
            const char *pw2 = password2 ? password2 : &DAT_0120546e; // Some default string
            FUN_00b0fc90(pw2); // Probably copy or validate
            const char *pw1 = password1 ? password1 : &DAT_0120546e;
            FUN_00b0fcb0(pw1);
            FUN_005669d0(); // Additional processing
            FUN_00983120("$fe_plasma_acount_creation_pending", 0, 0); // Show pending message
            goto cleanup;
        }

        // If password fields don't match the expected count, treat as invalid password
        int accountResult = FUN_009c8e50(0xf0);
        if (accountResult == 0) {
            accountResult = 0;
        } else {
            accountResult = FUN_00982280(0);
        }
        outputStrings = "$mp_online_invalid_password";
    }

    // Set error: display the relevant error string
    FUN_00981eb0(outputStrings);
    // Set state to 3 (likely error state) at offset +0x0c
    *(int *)(accountResult + 0xc) = 3;
    // Set a callback function at offset +0x14
    *(void (**)(void))(accountResult + 0x14) = FUN_00982b30;
    FUN_00982e10(); // Show UI

cleanup:
    // Clean up dynamically allocated strings from parsing
    if (tempArray[0] != 0) {
        destructor1(tempArray[0]);
    }
    if (password1 != 0) {
        destructor2(password1);
    }
    if (password2 != 0) {
        destructor3(password2);
    }
    return;
}