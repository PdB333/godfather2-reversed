// FUNC_NAME: InputDeviceManager::cleanupDeviceNotificationHandle
void __cdecl cleanupDeviceNotificationHandle(unsigned int* param_1) // param_1 is pointer to HDEVNOTIFY handle
{
    // If the handle is not null, unregister it and clear
    if ((HDEVNOTIFY)*param_1 != (HDEVNOTIFY)0x0) {
        UnregisterDeviceNotification((HDEVNOTIFY)*param_1);
        *param_1 = 0; // Set handle to null after cleanup
    }
}