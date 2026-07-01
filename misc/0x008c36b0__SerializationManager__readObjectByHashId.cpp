// FUNC_NAME: SerializationManager::readObjectByHashId

void SerializationManager::readObjectByHashId(uint32_t hashId, Stream* stream, void* param3) {
    String hashIdString; // local_10, size 3 ints (12 bytes) - stack-based string object
    // Format the hash ID into a string like "{#12345}"
    String::format(&hashIdString, 1, "{#%u}", hashId); // FUN_004d4a60
    // Read object from stream using the hash string and additional params
    Serializable::readFromStream(&hashIdString, stream, param3); // FUN_008c0fd0
    if (hashIdString.data != 0) {
        // NOTE: local_4 is uninitialized - likely a function pointer callback or virtual call
        // This may be a bug in decompilation or a missing parameter.
        // Possibly intended: call some post-processing callback with the object pointer.
        ((void (*)(char*))0x0)(hashIdString.data); // undefined behavior in original
    }
}