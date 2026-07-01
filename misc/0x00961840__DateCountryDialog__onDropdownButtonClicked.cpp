// FUNC_NAME: DateCountryDialog::onDropdownButtonClicked
// Address: 0x00961840
// Role: Handles button clicks for date/country selection dialog. Switches on button mode (0=day,1=month,2=year,3=country,4=apply)
// Fields: m_mode (+0x60), m_selectedData (+0x5C), m_year (+0x64), m_month (+0x68), m_day (+0x6C), m_country (+0x70)
// Also accesses m_someDataPtr at +0x84 (offset 0x21 * 4) and reads field at +0xA04 from that pointer

void __thiscall DateCountryDialog::onDropdownButtonClicked(int *this)
{
    int *vtable = (int *)this[0];
    int mode = this[0x18]; // +0x60

    switch (mode) {
    case 0: // Day button
        dispatchUIEvent("onco_control_day");
        this[0x17] = *(int *)(this[0x21] + 0xa04); // +0x5C = copy value from external data
        showDropdown("OpenDateDropBox", 0, &DAT_00d8d668, 0);
        returnControl(&DAT_01130448, 0);
        break;

    case 1: // Month button
        dispatchUIEvent("onco_control_month");
        this[0x17] = *(int *)(this[0x21] + 0xa04);
        showDropdown("OpenMonthDropBox", 0, &DAT_00d8d668, 0);
        returnControl(&DAT_01130448, 0);
        break;

    case 2: // Year button
        dispatchUIEvent("onco_control_year");
        this[0x17] = *(int *)(this[0x21] + 0xa04);
        showDropdown("OpenYearDropBox", 0, &DAT_00d8d668, 0);
        returnControl(&DAT_01130448, 0);
        break;

    case 3: // Country button
        dispatchUIEvent("onco_control_country");
        this[0x17] = *(int *)(this[0x21] + 0xa04);
        showDropdown("OpenCountryDropBox", 0, &DAT_00d8d668, 0);
        returnControl(&DAT_01130448, 0);
        break;

    case 4: // Apply/OK button
        if (this[0x1c] >= 0) // +0x70 = country is valid (not -1)
        {
            applyDateSelection((char)this[0x19], this[0x1a], (short)this[0x1b], this[0x1c]); // year, month, day, country
            // Call virtual function at offset 0x2C (likely close/submit)
            ((void (__thiscall *)(int *))vtable[0xB])(); // offset 0x2C = 11th vtable entry (0x2C/4=11)
            returnControl(&DAT_01130448, 0);
        }
        else
        {
            // Show error dialog for missing country
            int *dialog = (int *)allocDialog(0xf0);
            if (dialog != (int *)0)
            {
                dialog = (int *)createErrorDialog(0);
            }
            // else dialog remains null; likely error case
            dialog[3] = 3; // +0xC = set type to error
            setErrorMessage("$ui_plasma_country_error");
            setDialogButton(1); // enable OK button?
            dialog[5] = (int)errorDialogOkCallback; // +0x14 = set callback to FUN_00982b30
            showDialog();
            returnControl(&DAT_01130448, 0);
        }
        break;

    default:
        break;
    }
}