// Xbox PDB: EARS_Apt_UIHud_ShowIncomeMessage
// FUNC_NAME: IncomeMessageHandler::showIncomeMessage
// Address: 0x00939a30
// This function triggers an income message display and sets a pending flag.

void IncomeMessageHandler::showIncomeMessage(int incomeValue) {
    // EARS debug/log call: logs "ShowIncomeMessage" with some global data and the income value
    // Parameters: name string, zero, pointer to global DAT_00d8a64c, 1, incomeValue
    FUN_005a04a0("ShowIncomeMessage", 0, &DAT_00d8a64c, 1, incomeValue);

    // Set bit 23 (0x800000) at offset 0x5C in this object
    // This flag marks that an income message has been shown and might need processing.
    *(uint32_t*)(this + 0x5C) |= 0x800000;

    // Prepare a structure/stack variable for a conversion/formatting call
    // local_c holds a value from global DAT_011304a0 (likely the income amount or a currency constant)
    uint32_t value = DAT_011304a0;   // offset 0x0 in local struct
    uint32_t zero = 0;               // offset 0x4
    uint8_t extra = 0;               // offset 0x8 (unused fill?)

    // Call formatting/conversion function with pointer to 'value' and a zero flag
    // This probably converts the raw value into a displayable string or number
    FUN_00408a00(&value, 0);
}