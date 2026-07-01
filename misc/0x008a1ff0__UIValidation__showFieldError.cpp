// FUNC_NAME: UIValidation::showFieldError
// Function address: 0x008a1ff0
// Role: Displays a localized error message in the frontend UI based on the field name
void __thiscall UIValidation::showFieldError(UIValidation *this, const char *fieldName)
{
    // Clear any previous error display (parameters unused)
    uiClearError(0, 0, 0);

    const char *errorKey = "$ui_fe_ukn_error"; // +0x0: default generic error key

    if (__stricmp(fieldName, "email") == 0)
    {
        uiShowError("$ui_fe_email_invalid");
        return;
    }
    if (__stricmp(fieldName, "password") == 0)
    {
        uiShowError("$ui_fe_pwd_invalid");
        return;
    }
    if (__stricmp(fieldName, "parentalEmail") == 0)
    {
        errorKey = "$ui_fe_parent_email_invalid";
    }
    uiShowError(errorKey);
}