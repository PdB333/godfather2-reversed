// FUNC_NAME: InputDevice::waitForReady
bool InputDevice::waitForReady(void* device) {
    // Retry up to 4 times to check if the device is ready (likely hardware status polling)
    for (int attempt = 0; attempt < 4; ++attempt) {
        if (isDeviceReady(device)) {
            return true;
        }
    }
    return false;
}