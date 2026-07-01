// FUNC_NAME: displayMessageById
void displayMessageById(int messageId)
{
    // Stack-allocated resource structure (likely a string holder with destructor)
    struct {
        char* text;          // +0x00
        int32_t unknownLen;  // +0x04
        int32_t unknownFlag; // +0x08
        void (*destroy)(char*); // +0x0C
    } resource = {0, 0, 0, 0};

    // Compute a hash based on messageId (0x8336B71B if id==1, else 0xCF59C5D4)
    uint32_t hash = ((messageId != 1) ? 0xFFFFFFFF : 0) & 0x4C230EB9;
    hash += 0x8336B71B;

    // Fetch the localized string resource (FUN_00603330)
    getStringResource(hash, &resource);

    // Use default string if fetch failed
    char* text = resource.text;
    if (text == nullptr) {
        text = (char*)0x0120546e; // DAT_0120546e – assumed default/error string
    }

    // Display the message (FUN_008fce70)
    showMessage(messageId, text);

    // Free resource if it was dynamically allocated
    if (resource.text != nullptr) {
        resource.destroy(resource.text);
    }
}