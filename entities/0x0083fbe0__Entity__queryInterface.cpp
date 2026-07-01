// FUNC_NAME: Entity::queryInterface
// Function address: 0x0083fbe0
// Checks if this object supports the interface identified by the given ID (0xDA827575).
// If supported, returns the object's pointer via param_3 and returns 1; otherwise sets param_3 to NULL and returns 0.
int __thiscall Entity::queryInterface(uint32_t interfaceId, void** outInterface) {
    if (interfaceId == 0xDA827575) {
        *outInterface = this;   // This object IS the interface
        return 1;               // Success
    }
    *outInterface = NULL;
    return 0;                   // Interface not supported
}