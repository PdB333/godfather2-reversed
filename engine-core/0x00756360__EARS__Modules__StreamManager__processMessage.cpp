// FUNC_NAME: EARS::Modules::StreamManager::processMessage
void StreamManager::processMessage(void) {
    // Call virtual method at vtable+0x4c to fill local buffer (likely a small message header)
    // local_c is a 12-byte buffer for temporary data (e.g., message ID, flags)
    byte buffer[12];
    (this->vtable[0x4c])(buffer);

    // Get two object handles or pointers from the engine
    int* objA = Engine::getObjectHandle();
    int* objB = Engine::getObjectHandle();

    // Combine data from objects with the buffer and a constant key
    // objA+0x30 and objB+0x30 likely point to data segments (e.g., payloads)
    // &stack0xfffffff0 is actually the address of 'buffer' (decompiler artifact)
    // DAT_00d64e4c is a constant key/ID used for decryption or validation
    Engine::combineData(objB + 0x30, buffer, objA + 0x30, &KEY_CONSTANT);
}