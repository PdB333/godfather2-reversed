// FUNC_NAME: FinancialsScreen::populateFinancials
// Address: 0x00913a10
// This function populates the financial summary screen in the Books menu.
// It iterates over several financial categories (guard expenses, current funds,
// income from money laundering/other felonies, expenses for guards/family/other)
// and adds items to the UI via FinancesAddItem.

void FinancialsScreen::populateFinancials(void)
{
    // Local string objects (EA::Text::String or similar)
    // Each is a 16-byte structure: pointer, length, capacity, destructor function pointer
    String strLabel;      // local_60
    String strHelpText;   // local_50
    String strValue1;     // local_40
    String strValue2;     // local_30
    String strValue3;     // local_20
    String strValue4;     // local_10

    // Initialize all strings to empty
    strLabel.init();
    strHelpText.init();
    strValue1.init();
    strValue2.init();
    strValue3.init();
    strValue4.init();

    // --- Section 1: Guard Expense (summary) ---
    UI::callUIFunction("ShowScreen", 0, &DAT_00d84448, 1, "Finances");
    setFinancialTab(2, 0); // Set tab to "Expenses" or similar

    GameManager* pGameMgr = GameManager::getInstance(0x637b907); // Singleton hash
    if (pGameMgr->m_pFinancialData != nullptr) // +0x230
    {
        // Get localized strings
        Localization::getString("$dv_menu_books_financials_summary_guard_expense");
        Localization::getString("$dv_menu_books_financials_summary_guard_expense_helptext");

        accumulateFinancialCategory(2); // Accumulate category 2 (guard expenses)
        int totalGuardExpense = getFinancialValue(); // Get total
        formatNumberToString(-totalGuardExpense, &strValue1, 1); // Negative for expense

        // Label string
        Localization::getString(&DAT_00d84620); // Probably "expense" or empty

        // Add item to UI: FinancesAddItem(label, helpText, value1, value2, value3, value4)
        UI::callUIFunction("FinancesAddItem", 0, &DAT_00d84448, 6,
                           strLabel.isEmpty() ? &DAT_0120546e : strLabel.c_str(),
                           strHelpText.isEmpty() ? &DAT_0120546e : strHelpText.c_str(),
                           strValue1.isEmpty() ? &DAT_0120546e : strValue1.c_str(),
                           strValue2.isEmpty() ? &DAT_0120546e : strValue2.c_str(),
                           strValue3.isEmpty() ? &DAT_0120546e : strValue3.c_str(),
                           strValue4.isEmpty() ? &DAT_0120546e : strValue4.c_str());

        // Destruct strings
        strLabel.destroy();
        strValue4.destroy();
        strValue3.destroy();
        strValue1.destroy();
        strHelpText.destroy();
        strValue2.destroy();
    }

    // --- Section 2: Current Funds ---
    setFinancialTab(2, 3); // Switch to "Income" or similar
    pGameMgr = GameManager::getInstance(0x637b907);
    if (pGameMgr->m_pFinancialData != nullptr)
    {
        strLabel.init();
        strHelpText.init();
        strValue1.init();
        strValue2.init();
        strValue3.init();
        strValue4.init();

        Localization::getString("$dv_menu_books_financials_summary_current_funds");
        Localization::getString("$dv_menu_books_financials_summary_current_funds_helptext");

        formatNumberToString((int)*pGameMgr->m_pFinancialData, &strValue1, 1); // Current funds (positive)

        // Label
        Localization::getString(&DAT_00d84620);

        UI::callUIFunction("FinancesAddItem", 0, &DAT_00d84448, 6,
                           strValue2.isEmpty() ? &DAT_0120546e : strValue2.c_str(),
                           strLabel.isEmpty() ? &DAT_0120546e : strLabel.c_str(),
                           strValue1.isEmpty() ? &DAT_0120546e : strValue1.c_str(),
                           strValue3.isEmpty() ? &DAT_0120546e : strValue3.c_str(),
                           strValue4.isEmpty() ? &DAT_0120546e : strValue4.c_str(),
                           strHelpText.isEmpty() ? &DAT_0120546e : strHelpText.c_str());

        strValue2.destroy();
        strValue4.destroy();
        strValue3.destroy();
        strValue1.destroy();
        strHelpText.destroy();
        strLabel.destroy();
    }

    // --- Section 3: Income from Money Laundering ---
    setFinancialTab(0, 0);
    setFinancialTab(0, 1);
    pGameMgr = GameManager::getInstance(0x637b907);
    if (pGameMgr->m_pFinancialData != nullptr)
    {
        strValue4.init();
        strValue3.init();
        strLabel.init();
        strHelpText.init();
        strValue1.init();
        strValue2.init();

        Localization::getString("$dv_menu_books_financials_income_mlaunder");
        Localization::getString("$dv_menu_books_financials_income_mlaunder_helptext");

        accumulateFinancialCategory(2); // Category 2 for money laundering
        int val1 = getFinancialValue();
        accumulateFinancialCategory(2);
        int val2 = getFinancialValue();
        accumulateFinancialCategory(2);
        int val3 = getFinancialValue();
        accumulateFinancialCategory(2);
        int val4 = getFinancialValue();

        formatNumberToString(val1 + val2, &strLabel, 1); // Total income
        formatNumberToString(val3, &strHelpText, 1);     // Some sub-value
        formatNumberToString(val4, &strValue1, 1);       // Another sub-value

        // Label
        Localization::getString("income");

        UI::callUIFunction("FinancesAddItem", 0, &DAT_00d84448, 6,
                           strValue2.isEmpty() ? &DAT_0120546e : strValue2.c_str(),
                           strValue4.isEmpty() ? &DAT_0120546e : strValue4.c_str(),
                           strLabel.isEmpty() ? &DAT_0120546e : strLabel.c_str(),
                           strHelpText.isEmpty() ? &DAT_0120546e : strHelpText.c_str(),
                           strValue1.isEmpty() ? &DAT_0120546e : strValue1.c_str(),
                           strValue3.isEmpty() ? &DAT_0120546e : strValue3.c_str());

        strValue2.destroy();
        strValue1.destroy();
        strHelpText.destroy();
        strLabel.destroy();
        strValue4.destroy();
        strValue3.destroy();
    }

    // --- Section 4: Income from Other Felonies ---
    pGameMgr = GameManager::getInstance(0x637b907);
    if (pGameMgr->m_pFinancialData != nullptr)
    {
        strLabel.init();
        strHelpText.init();
        strValue1.init();
        strValue2.init();
        strValue3.init();
        strValue4.init();

        Localization::getString("$dv_menu_books_financials_income_otherfelonies");
        Localization::getString("$dv_menu_books_financials_income_otherfelonies_helptext");

        accumulateFinancialCategory(4); // Category 4 for other felonies
        int val1 = getFinancialValue();
        accumulateFinancialCategory(4);
        int val2 = getFinancialValue();
        accumulateFinancialCategory(4);
        int val3 = getFinancialValue();
        accumulateFinancialCategory(4);
        int val4 = getFinancialValue();

        formatNumberToString(val1 + val2, &strValue1, 1); // Total income
        formatNumberToString(val3, &strValue2, 1);        // Sub-value
        formatNumberToString(val4, &strValue3, 1);        // Sub-value

        // Label
        Localization::getString("income");

        UI::callUIFunction("FinancesAddItem", 0, &DAT_00d84448, 6,
                           strValue4.isEmpty() ? &DAT_0120546e : strValue4.c_str(),
                           strLabel.isEmpty() ? &DAT_0120546e : strLabel.c_str(),
                           strValue1.isEmpty() ? &DAT_0120546e : strValue1.c_str(),
                           strValue2.isEmpty() ? &DAT_0120546e : strValue2.c_str(),
                           strValue3.isEmpty() ? &DAT_0120546e : strValue3.c_str(),
                           strHelpText.isEmpty() ? &DAT_0120546e : strHelpText.c_str());

        strValue4.destroy();
        strValue3.destroy();
        strValue2.destroy();
        strValue1.destroy();
        strHelpText.destroy();
        strLabel.destroy();
    }

    // --- Section 5: Expense - Guards ---
    setFinancialTab(1, 5); // Switch to "Expenses" tab
    pGameMgr = GameManager::getInstance(0x637b907);
    if (pGameMgr->m_pFinancialData != nullptr)
    {
        strLabel.init();
        strHelpText.init();
        strValue1.init();
        strValue2.init();
        strValue3.init();
        strValue4.init();

        Localization::getString("$dv_menu_books_financials_expense_guards");
        Localization::getString("$dv_menu_books_financials_expense_guards_helptext");

        accumulateFinancialCategory(6); // Category 6 for guard expenses
        int val1 = getFinancialValue();
        accumulateFinancialCategory(6);
        int val2 = getFinancialValue();
        accumulateFinancialCategory(6);
        int val3 = getFinancialValue();
        accumulateFinancialCategory(6);
        int val4 = getFinancialValue();

        formatNumberToString(-val1 - val2, &strValue1, 1); // Total expense (negative)
        formatNumberToString(-val3, &strValue2, 1);        // Sub-expense
        formatNumberToString(-val4, &strValue3, 1);        // Sub-expense

        // Label
        Localization::getString("expense");

        UI::callUIFunction("FinancesAddItem", 0, &DAT_00d84448, 6,
                           strValue4.isEmpty() ? &DAT_0120546e : strValue4.c_str(),
                           strLabel.isEmpty() ? &DAT_0120546e : strLabel.c_str(),
                           strValue1.isEmpty() ? &DAT_0120546e : strValue1.c_str(),
                           strValue2.isEmpty() ? &DAT_0120546e : strValue2.c_str(),
                           strValue3.isEmpty() ? &DAT_0120546e : strValue3.c_str(),
                           strHelpText.isEmpty() ? &DAT_0120546e : strHelpText.c_str());

        strValue4.destroy();
        strValue3.destroy();
        strValue2.destroy();
        strValue1.destroy();
        strHelpText.destroy();
        strLabel.destroy();
    }

    // --- Section 6: Expense - Family Development ---
    pGameMgr = GameManager::getInstance(0x637b907);
    if (pGameMgr->m_pFinancialData != nullptr)
    {
        strLabel.init();
        strHelpText.init();
        strValue1.init();
        strValue2.init();
        strValue3.init();
        strValue4.init();

        Localization::getString("$dv_menu_books_financials_expense_familydev");
        Localization::getString("$dv_menu_books_financials_expense_familydev_helptext");

        accumulateFinancialCategory(9); // Category 9 for family development
        int val1 = getFinancialValue();
        accumulateFinancialCategory(9);
        int val2 = getFinancialValue();
        accumulateFinancialCategory(9);
        int val3 = getFinancialValue();
        accumulateFinancialCategory(9);
        int val4 = getFinancialValue();

        formatNumberToString(-val1 - val2, &strValue1, 1);
        formatNumberToString(-val3, &strValue2, 1);
        formatNumberToString(-val4, &strValue3, 1);

        Localization::getString("expense");

        UI::callUIFunction("FinancesAddItem", 0, &DAT_00d84448, 6,
                           strValue4.isEmpty() ? &DAT_0120546e : strValue4.c_str(),
                           strLabel.isEmpty() ? &DAT_0120546e : strLabel.c_str(),
                           strValue1.isEmpty() ? &DAT_0120546e : strValue1.c_str(),
                           strValue2.isEmpty() ? &DAT_0120546e : strValue2.c_str(),
                           strValue3.isEmpty() ? &DAT_0120546e : strValue3.c_str(),
                           strHelpText.isEmpty() ? &DAT_0120546e : strHelpText.c_str());

        strValue4.destroy();
        strValue3.destroy();
        strValue2.destroy();
        strValue1.destroy();
        strHelpText.destroy();
        strLabel.destroy();
    }

    // --- Section 7: Expense - Other ---
    pGameMgr = GameManager::getInstance(0x637b907);
    if (pGameMgr->m_pFinancialData != nullptr)
    {
        strLabel.init();
        strHelpText.init();
        strValue1.init();
        strValue2.init();
        strValue3.init();
        strValue4.init();

        Localization::getString("$dv_menu_books_financials_expense_other");
        Localization::getString("$dv_menu_books_financials_expense_other_helptext");

        accumulateFinancialCategory(10); // Category 10 for other expenses
        int val1 = getFinancialValue();
        accumulateFinancialCategory(10);
        int val2 = getFinancialValue();
        accumulateFinancialCategory(10);
        int val3 = getFinancialValue();
        accumulateFinancialCategory(10);
        int val4 = getFinancialValue();

        formatNumberToString(-val1 - val2, &strValue1, 1);
        formatNumberToString(-val3, &strValue2, 1);
        formatNumberToString(-val4, &strValue3, 1);

        Localization::getString("expense");

        UI::callUIFunction("FinancesAddItem", 0, &DAT_00d84448, 6,
                           strValue4.isEmpty() ? &DAT_0120546e : strValue4.c_str(),
                           strLabel.isEmpty() ? &DAT_0120546e : strLabel.c_str(),
                           strValue1.isEmpty() ? &DAT_0120546e : strValue1.c_str(),
                           strValue2.isEmpty() ? &DAT_0120546e : strValue2.c_str(),
                           strValue3.isEmpty() ? &DAT_0120546e : strValue3.c_str(),
                           strHelpText.isEmpty() ? &DAT_0120546e : strHelpText.c_str());

        strValue4.destroy();
        strValue3.destroy();
        strValue2.destroy();
        strValue1.destroy();
        strHelpText.destroy();
        strLabel.destroy();
    }

    // Finalize display
    updateFinancialsDisplay(); // FUN_00913750
    UI::callUIFunction("FinancesSetTitle", 0, &DAT_00d84448, 1, "$dv_menu_books_financials_income");
    UI::callUIFunction("FinancesSetTitle", 0, &DAT_00d84448, 1, "$dv_menu_books_financials_expense");
    UI::callUIFunction("FinancesShowScreen", 0, &DAT_00d84448, 0);
}