// FUN_NAME: UIBookFinancial::updateNetTake
void UIBookFinancial::updateNetTake(void) {
    int iVar1;
    FormattedString *pszNetTake;
    FormattedString *pszNetHelp;
    FormattedString *pszTotalEarnings;
    // ... other local variables (for additional strings?) 
    // The decompiled shows many local variables: local_90, local_80, local_70, local_50, local_60, local_40, local_30, local_20, local_10
    // plus their associated destructors and extra fields.
    // We'll use a small struct to model the FormattedString objects.
    struct FormattedString {
        char *text;         // The formatted text pointer (might be internal buffer)
        int field_0x4;      // Unknown, possibly length
        int field_0x8;      // Unknown
        void (*destructor)(FormattedString *); // Destructor function pointer (stored separately in stack)
    };

    // Retrieve the financial UI manager singleton (offset 0x230 indicates visibility flag)
    iVar1 = getUIObject(0x637b907); // FUN_008c74d0 - get singleton by hash
    if (*(int *)(iVar1 + 0x230) != 0) {
        // Load localized strings for the net take labels
        localizeString("$dv_menu_books_financials_nettake");   // FUN_004d3bc0
        localizeString("$dv_menu_books_financials_net_helptext"); // FUN_004d3bc0

        // Get numeric values: net take, net help (maybe another value), and total earnings
        float fNetTake = getFloatValue();        // FUN_00892390
        float fNetHelp = getFloatValue();        // FUN_00892390
        getFloatValue();                         // Discarded?
        int iTotalEarnings = getTotalEarnings(); // FUN_00b9a1c0

        // Format numbers into string objects
        FormattedString *netTakeStr = nullptr;
        int netTakeStrField1 = 0;
        int netTakeStrField2 = 0;
        void (*netTakeStrDtor)(FormattedString *) = nullptr;
        // ... (similar pattern for other strings)
        FormattedString *netHelpStr = nullptr;
        int netHelpStrField1 = 0;
        int netHelpStrField2 = 0;
        void (*netHelpStrDtor)(FormattedString *) = nullptr;
        FormattedString *totalStr = nullptr;
        int totalStrField1 = 0;
        int totalStrField2 = 0;
        void (*totalStrDtor)(FormattedString *) = nullptr;

        // The decompiled also shows additional string variables: local_50, local_60, local_40, local_30, local_20, local_10
        // Probably for other parts of the display (e.g., negative signs, currency symbols, etc.)
        // Not fully used in the main call? They are included in the final message.
        // We'll skip them for brevity and assume they are similar format calls.

        // Format the numeric values into the string objects
        formatNumberToString((int)fNetTake, &netTakeStr, 1);        // FUN_00604000
        formatNumberToString((int)fNetHelp, &netHelpStr, 1);        // FUN_00604000
        formatNumberToString(iTotalEarnings, &totalStr, 1);         // FUN_00604000

        // Set the label text for "nettake"
        localizeString("nettake");
        localizeString(&DAT_00e36da0);   // Unknown constants (maybe empty strings or currency symbol)
        localizeString(&DAT_00e36da0);
        localizeString(&DAT_00e36da0);

        // Handle negative values by setting a negative indicator
        if ((int)fNetTake < 0) {
            setNegativeIndicator(&DAT_00e36d94); // FUN_004d3d90
        }
        if ((int)fNetHelp < 0) {
            setNegativeIndicator(&DAT_00e36d94);
        }
        if (iTotalEarnings < 0) {
            setNegativeIndicator(&DAT_00e36d94);
        }

        // Prepare all strings for the UI call, defaulting to empty string if null
        FormattedString *ptr1 = local_20 ? local_20 : &DAT_0120546e; // Some other string (maybe from earlier format)
        FormattedString *ptr2 = totalStr ? totalStr : &DAT_0120546e;
        FormattedString *ptr3 = netHelpStr ? netHelpStr : &DAT_0120546e;
        FormattedString *ptr4 = netTakeStr ? netTakeStr : &DAT_0120546e;
        // ... similar for other string variables (local_50, local_60, etc.)

        // Send a message to the UI system to update the financial total display
        sendMessageToUI("FinancesSetTotal", 0, &DAT_00d84448, 9,
                        ptr5, ptr6, ptr7, ptr8, ptr9, ptr4, ptr3, ptr2, ptr1);
        // The actual parameters include many strings (the decompiled shows 9 strings?).

        // Destroy all FormattedString objects using their destructor function pointers
        if (local_50 != nullptr) { // e.g., another string object
            local_44(local_50);    // destructor
        }
        // ... repeat for all string objects (local_60, local_40, local_30, local_70, local_80, local_90, local_20, local_10)
        // We only show a subset here; the original code cleans all.
        if (totalStr != nullptr) {
            totalStrDtor(totalStr);
        }
        if (netHelpStr != nullptr) {
            netHelpStrDtor(netHelpStr);
        }
        if (netTakeStr != nullptr) {
            netTakeStrDtor(netTakeStr);
        }
        // ... cleanup for other local strings
    }
}