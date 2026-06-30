// FUNC_NAME: InputDeviceManager::registerDeviceNotification
void InputDeviceManager::registerDeviceNotification(HANDLE hwnd, unsigned __int64 deviceId, unsigned __int64 deviceData)
{
    // Build DEV_BROADCAST_DEVICEINTERFACE_A structure (size 0x20 = 32 bytes) inline
    // Constant 0x500000020 describes a device interface notification with dbcc_classguid
    // offset 0x00: dbcc_size = 0x20
    // offset 0x04: dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE (0x05)
    // offset 0x08: dbcc_reserved (0)
    // offset 0x0C: dbcc_classguid.Data1 (low 32 bits of deviceId)
    // offset 0x10: dbcc_classguid.Data2 (high 32 bits of deviceId)
    // offset 0x14: dbcc_classguid.Data3 (low 32 bits of deviceData)
    // offset 0x18: dbcc_classguid.Data4 (high 32 bits of deviceData)
    
    unsigned __int8 notificationBuffer[32]; // Actually uses stack locals
    
    // Build the DEV_BROADCAST_DEVICEINTERFACE_A structure
    notificationBuffer[0] = 0x20;    // dbcc_size
    notificationBuffer[1] = 0;       // zero padding
    notificationBuffer[2] = 0;       // 
    notificationBuffer[3] = 0;       // 
    *(unsigned int*)&notificationBuffer[4] = 0x05;   // DBT_DEVTYP_DEVICEINTERFACE
    *(unsigned int*)&notificationBuffer[8] = 0;       // dbcc_reserved
    *(unsigned int*)&notificationBuffer[12] = (unsigned int)(deviceId & 0xFFFFFFFF);       // GUID low
    *(unsigned int*)&notificationBuffer[16] = (unsigned int)(deviceId >> 32);               // GUID high
    *(unsigned int*)&notificationBuffer[20] = (unsigned int)(deviceData & 0xFFFFFFFF);     // 
    *(unsigned int*)&notificationBuffer[24] = (unsigned int)(deviceData >> 32);             //
    *(unsigned int*)&notificationBuffer[28] = 0;       // 
    
    // Register for device notifications (third param = 0 means no filter)
    RegisterDeviceNotificationA(hwnd, notificationBuffer, 0);
}