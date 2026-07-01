// FUNC_NAME: NetConnection::processObjectUpdate
// Address: 0x00810960
// Role: Copies object data and checks interface, then dispatches to handler if cast succeeds.

void __thiscall NetConnection::processObjectUpdate(void *sourceObj, void *destObj) {
    // Copy 4 dwords (16 bytes) from source to destination.
    *(uint32_t *)destObj = *(uint32_t *)sourceObj;
    ((uint32_t *)destObj)[1] = ((uint32_t *)sourceObj)[1];
    ((uint32_t *)destObj)[2] = ((uint32_t *)sourceObj)[2];
    ((uint32_t *)destObj)[3] = ((uint32_t *)sourceObj)[3];

    // Get the class descriptor (RTTI) of the source object.
    ClassDescriptor *classDesc = getClassDescriptor(sourceObj, 0);
    if (classDesc != nullptr) {
        // Attempt to query for an interface with GUID 0x420f378a.
        // This may be the interface for network replication (e.g., INetObject).
        void *interfacePtr = nullptr;
        bool success = (classDesc->vtable->queryInterface)(0x420f378a, &interfacePtr);
        if (success && (this != nullptr)) {
            // Call the handler for the received object (vtable offset 0x158).
            (this->vtable->onObjectReceived)(destObj);
        }
    }
}