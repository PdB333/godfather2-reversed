// FUNC_NAME: InputDeviceManager::unregisterDeviceNotificationHandle
// Address: 0x0069d6e0
// Role: Unregisters and clears a device notification handle (HDEVNOTIFY) stored at offset 0 of the object.

void InputDeviceManager::unregisterDeviceNotificationHandle()
{
    // The HDEVNOTIFY handle is stored at offset 0 of this object
    // +0x00: HDEVNOTIFY m_hDeviceNotify
    if (m_hDeviceNotify != NULL)
    {
        UnregisterDeviceNotification(m_hDeviceNotify);
        m_hDeviceNotify = NULL;
    }
}