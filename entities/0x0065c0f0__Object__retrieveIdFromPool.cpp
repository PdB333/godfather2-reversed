// FUNC_NAME: Object::retrieveIdFromPool

void Object::retrieveIdFromPool() {
    uint32_t idParts[2]; // local_8 and local_4
    getObjectIdPair(0x40, idParts); // FUN_0064b9e0: generates or retrieves a 64-bit ID pair
    this->field_0x00 = idParts[0]; // +0x00: low part of ID
    this->field_0x04 = idParts[1]; // +0x04: high part of ID
}