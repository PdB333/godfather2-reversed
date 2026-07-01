// FUNC_NAME: BooksFinancialsScreen::addFinancialRow
// Address: 0x00913240
// This function adds a financial row to the books UI, handling income, expense, and summary categories.
// It retrieves localized strings, computes financial values, formats them, and calls the UI to add the item.

void BooksFinancialsScreen::addFinancialRow(int category, int subCategoryIndex)
{
    float *pPlayerMoney;
    int value1, value2, value3, value4;
    float10 moneyLaundering;
    char *localizedString, *helpText;
    char *strValue1, *strValue2, *strValue3;
    char *strEmpty; // always empty string (DAT_0120546e)
    char *strCategory;

    // Get the game manager singleton (hash 0x637b907)
    GameManager *gameMgr = GameManager::getInstance(0x637b907);
    pPlayerMoney = *(float **)(gameMgr + 0x230); // +0x230: player current funds
    if (pPlayerMoney == nullptr) {
        return;
    }

    // Initialize formatted strings to null
    strValue1 = nullptr;
    strValue2 = nullptr;
    strValue3 = nullptr;
    strEmpty = nullptr; // will be set to empty string later

    // Handle summary category (category == 2)
    if (category == 2) {
        if (subCategoryIndex == 0) {
            // Venue income
            localizedString = Localization::getString("$dv_menu_books_financials_summary_venue_income");
            helpText = Localization::getString("$dv_menu_books_financials_summary_venue_income_helptext");
            getSummaryIncome(); // likely sets up some internal state
            value4 = getFinancialValue(); // returns total venue income
            strValue1 = formatNumber(value4, &strValue1, 1); // format as money
        }
        else if (subCategoryIndex == 1) {
            // Guard expense
            localizedString = Localization::getString("$dv_menu_books_financials_summary_guard_expense");
            helpText = Localization::getString("$dv_menu_books_financials_summary_guard_expense_helptext");
            getSummaryExpense();
            value4 = getFinancialValue();
            value4 = -value4; // expense is negative
            strValue1 = formatNumber(value4, &strValue1, 1);
        }
        else if (subCategoryIndex == 3) {
            // Money laundering
            moneyLaundering = getMoneyLaunderingValue();
            // Compare with some global thresholds (DAT_00d5780c, DAT_00d5e288)
            if ((moneyLaundering - (float10)_DAT_00d5780c) * (float10)DAT_00d5e288 <= (float10)0) {
                getMoneyLaunderingValue(); // discard result
            }
            else {
                getMoneyLaunderingValue(); // discard result
            }
            value4 = getFinancialValue();
            localizedString = Localization::getString("$dv_menu_books_financials_summary_money_laundering");
            helpText = Localization::getString("$dv_menu_books_financials_summary_money_laundering_helptext");
            strValue1 = formatFloat((float)value4, 0, &strValue1, 1);
        }
        else if (subCategoryIndex == 2) {
            // Current funds
            localizedString = Localization::getString("$dv_menu_books_financials_summary_current_funds");
            helpText = Localization::getString("$dv_menu_books_financials_summary_current_funds_helptext");
            value4 = (int)*pPlayerMoney;
            strValue1 = formatNumber(value4, &strValue1, 1);
        }
    }
    else {
        // Income (category == 0) or Expense (category == 1)
        if (category == 0) {
            switch (subCategoryIndex) {
            case 0:
                localizedString = Localization::getString("$dv_menu_books_financials_income_rackets");
                helpText = "$dv_menu_books_financials_income_rackets_helptext";
                break;
            case 1:
                localizedString = Localization::getString("$dv_menu_books_financials_income_extortion");
                helpText = "$dv_menu_books_financials_income_extortion_helptext";
                break;
            case 2:
                localizedString = Localization::getString("$dv_menu_books_financials_income_mlaunder");
                helpText = "$dv_menu_books_financials_income_mlaunder_helptext";
                break;
            case 4:
                localizedString = Localization::getString("$dv_menu_books_financials_income_otherfelonies");
                helpText = "$dv_menu_books_financials_income_otherfelonies_helptext";
                break;
            default:
                // case 3? fall through
                break;
            }
            Localization::getString(helpText); // discard? Actually it's called but result not used? Might be for side effects.
            // Get financial data for this subcategory (multiple calls to get different values)
            getFinancialData(subCategoryIndex);
            value1 = getFinancialValue();
            getFinancialData(subCategoryIndex);
            value2 = getFinancialValue();
            value1 = value1 + value2;
            getFinancialData(subCategoryIndex);
            value3 = getFinancialValue();
            getFinancialData(subCategoryIndex);
            value4 = getFinancialValue();
        }
        else if (category == 1) {
            switch (subCategoryIndex) {
            case 5:
                localizedString = Localization::getString("$dv_menu_books_financials_expense_bribes");
                helpText = "$dv_menu_books_financials_expense_bribes_helptext";
                break;
            case 6:
                localizedString = Localization::getString("$dv_menu_books_financials_expense_guards");
                helpText = "$dv_menu_books_financials_expense_guards_helptext";
                break;
            case 9:
                localizedString = Localization::getString("$dv_menu_books_financials_expense_familydev");
                helpText = "$dv_menu_books_financials_expense_familydev_helptext";
                break;
            case 10:
                localizedString = Localization::getString("$dv_menu_books_financials_expense_other");
                helpText = "$dv_menu_books_financials_expense_other_helptext";
                break;
            default:
                // case 7,8? fall through
                break;
            }
            Localization::getString(helpText);
            getFinancialData(subCategoryIndex);
            value1 = getFinancialValue();
            getFinancialData(subCategoryIndex);
            value2 = getFinancialValue();
            value1 = -value2 - value1; // expenses are negative
            getFinancialData(subCategoryIndex);
            value3 = getFinancialValue();
            value3 = -value3;
            getFinancialData(subCategoryIndex);
            value4 = getFinancialValue();
            value4 = -value4;
        }

        // Format the three values into strings
        strValue1 = formatNumber(value1, &strValue1, 1);
        strValue2 = formatNumber(value3, &strValue2, 1);
        strValue3 = formatNumber(value4, &strValue3, 1);
    }

    // Determine category string
    if (category == 0) {
        strCategory = "income";
    }
    else if (category == 1) {
        strCategory = "expense";
    }
    else if (category == 2) {
        strCategory = "sum";
    }
    else {
        strCategory = nullptr;
    }
    Localization::getString(strCategory); // discard? Might be for side effects.

    // Use empty string if any formatted string is null
    char *emptyStr = &DAT_0120546e; // global empty string
    char *catStr = strCategory ? strCategory : emptyStr;
    char *val1 = strValue1 ? strValue1 : emptyStr;
    char *val2 = strValue2 ? strValue2 : emptyStr;
    char *val3 = strValue3 ? strValue3 : emptyStr;

    // Add the financial item to the UI list
    // Parameters: "FinancesAddItem", 0, some UI handle (DAT_00d84448), 6 fields, then strings: category, empty, value1, value2, value3, empty
    UIList::addItem("FinancesAddItem", 0, &DAT_00d84448, 6, catStr, emptyStr, val1, val2, val3, emptyStr);

    // Free the formatted strings if they were allocated
    if (strValue3) {
        freeString(strValue3);
    }
    if (strValue2) {
        freeString(strValue2);
    }
    if (strValue1) {
        freeString(strValue1);
    }
    // Note: strEmpty is not allocated, it's a global constant.
}