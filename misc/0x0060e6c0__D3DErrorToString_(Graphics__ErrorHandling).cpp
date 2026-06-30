// FUNC_NAME: D3DErrorToString (Graphics::ErrorHandling)
// Function address: 0x0060e6c0
// Role: Translates Direct3D error codes (0-8) to human-readable strings.
// Used in rendering pipeline to report D3D initialization failures.
const char* D3DErrorToString(int errorCode)
{
    if (errorCode == 0)
    {
        return "An error has occured."; // Generic error
    }
    if (errorCode == 1)
    {
        return "Unable to create D3D Device."; // D3D device creation failed
    }
    if (errorCode == 2)
    {
        return "Out of video memory."; // Insufficient video memory
    }
    if (errorCode == 3)
    {
        return "An error has occured getting device caps."; // Failed to get device capabilities
    }
    if (errorCode == 4)
    {
        return "Required format not supported."; // Required pixel format not available
    }
    if (errorCode == 5)
    {
        return "No supported resolutions available."; // No valid display modes found
    }
    if (errorCode == 6)
    {
        return "A required D3D device cap is not available."; // Missing required device capability
    }
    if (errorCode == 7)
    {
        return "The minimum pixel shader version is not meet."; // Pixel shader version too low
    }
    if (errorCode == 8)
    {
        return "No D3D adapters found."; // No Direct3D adapters detected
    }
    return "<Error>"; // Unknown error code
}