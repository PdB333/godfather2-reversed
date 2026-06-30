// FUNC_NAME: ResourceHandle::ResourceHandle
void __thiscall ResourceHandle::ResourceHandle(int this, uint handleValue, uint typeId) {
    // Base class constructor call: ResourceHandle(typeId, true)
    ResourceHandle::ResourceHandle(this, typeId, 1);

    // Store handle value at +0x2C: index from handleValue >> 2 with top bits set (magic handle flag)
    *(uint *)(this + 0x2C) = (handleValue >> 2) | 0xC0000000;

    // Global object creation notification
    GlobalInit::OnObjectCreated();

    // Log resource creation event (eventId = 0x2001)
    LogManager::LogEvent(0x2001, typeId, 0);
}