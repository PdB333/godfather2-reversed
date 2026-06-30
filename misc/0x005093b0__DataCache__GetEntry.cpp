// FUNC_NAME: DataCache::GetEntry
void DataCache::GetEntry(int index, DataEntry* outEntry) {
    // Compute the base of the global data cache table using thread-local storage.
    // FS:[0x2C] points to the TLS array; we access the first TLS slot,
    // then follow a pointer chain to get the global cache pointer.
    // The cache table starts at offset 0x80 from that pointer.
    // The specific entry is at offset 'index' (from param_1+8).
    DataEntry* source = (DataEntry*)(*(int*)(*(int*)(*(int**)__readfsdword(0x2C) + 8) + 0x80) + index);
    // Copy the 16-byte entry to the output.
    *outEntry = *source;
}