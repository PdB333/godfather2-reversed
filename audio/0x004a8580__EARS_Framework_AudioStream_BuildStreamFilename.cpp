// Xbox PDB: EARS::Framework::AudioStream::BuildStreamFilename
// FUNC_NAME: AudioStreamManager::initializeStreams
// Function at 0x004a8580: Initializes audio streams, loading required soundbanks/resources. Handles global init, string management, resource cleanup.
bool AudioStreamManager::initializeStreams(const char* streamName, bool needLoadResource, bool needExtraString)
{
    // Global one-time initialization
    if ((g_initialized & 1) == 0) {
        g_initialized |= 1;
        engineInit(); // FUN_0040ce40
    }

    // Resolve stream name: use default if null/empty
    bool hasCustomName = (streamName != nullptr) && (streamName[0] != '\0');
    if (!hasCustomName) {
        streamName = g_defaultStreamName; // DAT_01223b10
    }

    // Reference the strings used internally
    stringReference(streamName);         // FUN_004d3bc0
    stringReference(g_someString1);      // DAT_00e2f048
    stringReference(streamName);         // param_1? Actually streamName is param_1? The decompiler shows param_1 used, we treat it as streamName

    // Decide path: load from scratch or reuse cached strings
    if (hasCustomName || g_flagAudioStreams == '\0') { // DAT_012051f8
        allocateStreamList(&local_streamList); // FUN_004d3e20
        loadString("audiostreams");            // FUN_004d4300
    } else {
        unloadString("audiostreams");          // FUN_004d3d90
        unloadString(g_someString1);           // DAT_00e2f048
    }

    // Release resource if previously allocated (local variables may be reused)
    releaseResource(&local_resource48, 0, 0); // FUN_004d43f0

    // If flag1 set and resource exists, process extra resource
    if (needLoadResource && g_resourceSize1 != 0) {
        releaseResource(g_resourcePtr1, 0, g_resourceSize1);
        releaseResource(&local_resource48, 0, 0);
    }

    // If flag2 set, load an additional string
    if (needExtraString) {
        loadString(g_someString2); // DAT_00e355ac
    }

    // Check length of local_string (local_28) – if string too long, perform error handling
    const char* strPtr = local_string;
    if (strPtr == nullptr) {
        strPtr = g_defaultFallbackString; // DAT_0120546e
    }
    size_t len = 0;
    const char* p = strPtr;
    while (*p++) len++;
    if (len > 16) {
        // Too long: release old, process, set flags, cleanup
        stringReference(local_string + 4);   // FUN_004d3bc0 (skip first 4 bytes?)
        processStream();                     // FUN_004d57e0
        setStreamFlag(8, 0);                 // FUN_004d4060
        releaseResource(&local_resource38, 0, 0); // FUN_004d43f0
        releaseResource(&local_resource48, 0, 0); // FUN_004d43f0
        if (local_resource38 != 0) {
            (*(void(*)(int))local_vtable38)(local_resource38); // call destructor via vtable
        }
    }

    // Release the local_string resource
    releaseResource(local_string, 0, 0);
    if (local_string != nullptr) {
        (*(void(*)(int))local_vtableString)(local_string); // destructor via vtable
    }

    // Release the main resource container
    if (local_resource48 != 0) {
        (*(void(*)(int))local_vtable48)(local_resource48);
    }

    // Release the stream list
    if (local_streamList[0] != 0) {
        (*(void(*)(int))local_vtableList)(local_streamList[0]);
    }

    return true; // always returns 1
}