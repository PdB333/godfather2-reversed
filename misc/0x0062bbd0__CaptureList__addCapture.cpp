// FUNC_NAME: CaptureList::addCapture
void __thiscall CaptureList::addCapture(void* callback, void* userData)
{
    int count = *(int *)(this + 0xc); // current number of captures
    if (count > 31) {
        // assert or log "too many captures"
        // param_1 is used as second argument? Not stored.
        errorFunction("too many captures", callback);
    }
    // Store entry at offset 0x10 + count*8
    *(void **)(this + 0x10 + count * 8) = callback;   // callback
    *(void **)(this + 0x14 + count * 8) = userData;   // user data
    // Increment count
    *(int *)(this + 0xc) = count + 1;
    // Validate the new entry (e.g., ensure callback is valid)
    if (!validateCaptures()) {
        // Revert count on failure
        *(int *)(this + 0xc) = count;
    }
}