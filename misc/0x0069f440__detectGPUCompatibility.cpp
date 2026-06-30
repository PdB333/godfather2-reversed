// FUNC_NAME: detectGPUCompatibility
int detectGPUCompatibility(void)
{
    // Check if running under a debugger or some condition that forces software rendering
    if (FUN_0049bee0() != 0 &&
        FUN_0049bc90() != 0 &&
        FUN_0049c210() != '\0' &&
        local_1c0 == 0xf &&
        local_1c4 == 0)
    {
        return 2; // Return 2 for software? Or hardware?
    }

    DISPLAY_DEVICEA displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICEA); // 0x1a8
    DWORD deviceIndex = 0;

    // Enumerate all display devices
    while (EnumDisplayDevicesA(NULL, deviceIndex, &displayDevice, 0))
    {
        deviceIndex++;

        // Check if the device is active (StateFlags bit 2 - DISPLAY_DEVICE_MIRRORING_DRIVER? Or check for primary?)
        if (displayDevice.StateFlags & 4)
        {
            // Extract vendor ID from DeviceID string (format: "VEN_XXXX&DEV_XXXX&SUBSYS_...")
            char *vendorStart = strstr(displayDevice.DeviceID, "VEN_");
            // char *deviceStart = strstr(displayDevice.DeviceID, "DEV_"); // unused

            // Replace all '&' with null terminator to isolate vendor string
            for (char *ampPos = strchr(displayDevice.DeviceID, '&'); ampPos != NULL; ampPos = strchr(ampPos + 1, '&'))
            {
                *ampPos = '\0';
            }

            // Compute length of DeviceString
            int deviceStringLen = strlen(displayDevice.DeviceString);

            // Check for NVIDIA (vendor ID "10DE")
            if (vendorStart && strncmp(vendorStart + 4, "10DE", 4) == 0)
            {
                // Check if device name starts with "NVIDIA GeForce "
                const char nvidiaPrefix[] = "NVIDIA GeForce ";
                if (deviceStringLen > (int)sizeof(nvidiaPrefix) - 1 &&
                    strnicmp(displayDevice.DeviceString, nvidiaPrefix, sizeof(nvidiaPrefix) - 1) == 0)
                {
                    // Additional check for specific NVIDIA GPU model
                    if (FUN_0069f3b0() != 0)
                    {
                        return 2;
                    }
                }
            }
            else if (vendorStart && strncmp(vendorStart + 4, "1002", 4) == 0) // ATI/AMD vendor
            {
                // Check for "ATI Radeon X" series
                const char atiXPrefix[] = "ATI Radeon X";
                if (deviceStringLen > (int)sizeof(atiXPrefix) - 1 &&
                    strnicmp(displayDevice.DeviceString, atiXPrefix, sizeof(atiXPrefix) - 1) == 0)
                {
                    return 2; // Known good ATI X series
                }

                // Check for "ATI Radeon HD " series
                const char atiHDPrefix[] = "ATI Radeon HD ";
                if (deviceStringLen > (int)sizeof(atiHDPrefix) - 1 &&
                    strnicmp(displayDevice.DeviceString, atiHDPrefix, sizeof(atiHDPrefix) - 1) == 0)
                {
                    // Additional check for specific HD model
                    if (FUN_0069f3b0() != 0)
                    {
                        return 2;
                    }
                }
            }
        }

        // Continue enumeration, resetting struct size
        displayDevice.cb = sizeof(DISPLAY_DEVICEA);
    }

    // No GPU matched; fallback to other detection
    int status1 = FUN_0060f480();
    if (status1 == 0)
    {
        return 3; // Return 3 for fallback?
    }

    int status2 = FUN_0060f480();
    if (status2 == 1)
    {
        return 2; // Return 2 for hardware?
    }

    int status3 = FUN_0060f480();
    if (status3 == 3 && FUN_00608200() == 0)
    {
        return 2;
    }

    return 4; // Default fallback
}