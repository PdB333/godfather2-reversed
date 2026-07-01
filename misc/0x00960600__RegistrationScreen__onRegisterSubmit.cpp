// FUNC_NAME: RegistrationScreen::onRegisterSubmit
void RegistrationScreen::onRegisterSubmit(void)
{
    // String objects for UI widget text (each 16 bytes: data ptr, size, capacity, vtable)
    EARS::String emailStr;
    EARS::String usernameStr;
    EARS::String passwordStr;
    EARS::String verifyPasswordStr;

    // Retrieve email input text
    uint emailWidget = getWidgetByName("onac_main_register_email_input");
    getWidgetText(emailWidget, &emailStr);

    // Retrieve username input text
    uint usernameWidget = getWidgetByName("onac_main_register_username_input");
    getWidgetText(usernameWidget, &usernameStr);

    // Retrieve password input text
    uint passwordWidget = getWidgetByName("onac_main_register_password_input");
    getWidgetText(passwordWidget, &passwordStr);

    // Retrieve verify password input text
    uint verifyPasswordWidget = getWidgetByName("onac_main_register_vpassword_input");
    getWidgetText(verifyPasswordWidget, &verifyPasswordStr);

    // Validate email
    const char* emailCStr = (emailStr.data != nullptr) ? emailStr.data : "";
    if (!isEmailValid(emailCStr))
    {
        showRegistrationError("Invalid email address (LOC)");
    }
    else
    {
        // Validate username length (max 63 characters, null excluded)
        const char* usernameCStr = (usernameStr.data != nullptr) ? usernameStr.data : "";
        size_t usernameLen = 0;
        while (usernameCStr[usernameLen] != '\0')
            usernameLen++;
        // Original check: (usernameLen - 1) < 63 allows length up to 63
        if (usernameLen > 63)
        {
            showRegistrationError("Invalid username (LOC)");
        }
        else
        {
            // Compare password and verify password
            const char* pwdCStr = (passwordStr.data != nullptr) ? passwordStr.data : "";
            const char* vpwdCStr = (verifyPasswordStr.data != nullptr) ? verifyPasswordStr.data : "";
            int cmpResult = 0;
            {
                const char* p = pwdCStr;
                const char* vp = vpwdCStr;
                int diff;
                do {
                    diff = (unsigned char)*p - (unsigned char)*vp;
                    if (diff != 0)
                        break;
                    if (*p == 0)
                        break;
                    p++;
                    vp++;
                } while (true);
                cmpResult = diff;
            }
            if (cmpResult != 0)
            {
                showRegistrationError("Password mismatch (LOC)");
            }
            else
            {
                // Validate password length (max 32 characters)
                size_t pwdLen = 0;
                while (pwdCStr[pwdLen] != '\0')
                    pwdLen++;
                // Original check: (pwdLen - 6) < 27 allows length up to 32
                if (pwdLen > 32)
                {
                    showRegistrationError("Invalid password (LOC)");
                }
                else
                {
                    // All valid, attempt registration
                    attemptRegistration(emailCStr, usernameCStr, pwdCStr);
                }
            }
        }
    }

    // Release string objects (call destructor via vtable)
    emailStr.release();
    usernameStr.release();
    passwordStr.release();
    verifyPasswordStr.release();
}