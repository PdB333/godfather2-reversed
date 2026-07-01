// FUNC_NAME: OnacMainRegisterScreenInit
// Function address: 0x00960390
// Role: Initializes the online account registration UI screen - sets up input fields (email, username, password, verify password) and binds hotspot images to each.

void __fastcall OnacMainRegisterScreenInit(void* screenContext) {
    // Handles for the four input fields in the registration UI
    void* emailInput;
    void* usernameInput;
    void* passwordInput;
    void* verifyPasswordInput;
    byte hotspotBindFlags[16] = {0}; // Flags/buffer for hotspot binding operation

    // Retrieve UI element objects by their string identifiers
    emailInput = GetUIElement("onac_main_register_email_input");
    SetupInputField(emailInput);

    usernameInput = GetUIElement("onac_main_register_username_input");
    SetupInputField(usernameInput);

    passwordInput = GetUIElement("onac_main_register_password_input");
    SetupInputField(passwordInput);

    verifyPasswordInput = GetUIElement("onac_main_register_vpassword_input");
    SetupInputField(verifyPasswordInput);

    // Bind hotspot images to each input field (likely for highlight/active states)
    BindHotspotToInputField("onac_main_register_email_input",
                            "onac_main_register_email_hotspot",
                            hotspotBindFlags, screenContext);
    BindHotspotToInputField("onac_main_register_username_input",
                            "onac_main_register_username_hotspot",
                            hotspotBindFlags, screenContext);
    BindHotspotToInputField("onac_main_register_password_input",
                            "onac_main_register_password_hotspot",
                            hotspotBindFlags, screenContext);
    BindHotspotToInputField("onac_main_register_vpassword_input",
                            "onac_main_register_vpassword_hotspot",
                            hotspotBindFlags, screenContext);
}