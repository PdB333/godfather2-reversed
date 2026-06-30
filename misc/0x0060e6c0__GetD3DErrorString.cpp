// FUNC_NAME: GetD3DErrorString
// Address: 0x0060e6c0
// Role: Maps Direct3D error codes to human-readable error messages.
const char* GetD3DErrorString(int errorCode)
{
    if (errorCode == 0)
    {
        return "An error has occured.";
    }
    if (errorCode == 1)
    {
        return "Unable to create D3D Device.";
    }
    if (errorCode == 2)
    {
        return "Out of video memory.";
    }
    if (errorCode == 3)
    {
        return "An error has occured getting device caps.";
    }
    if (errorCode == 4)
    {
        return "Required format not supported.";
    }
    if (errorCode == 5)
    {
        return "No supported resolutions available.";
    }
    if (errorCode == 6)
    {
        return "A required D3D device cap is not available.";
    }
    if (errorCode == 7)
    {
        return "The minimum pixel shader version is not meet.";
    }
    // errorCode == 8: No adapters found; default returns "<Error>"
    if (errorCode == 8)
    {
        return "No D3D adapters found.";
    }
    return "<Error>";
}