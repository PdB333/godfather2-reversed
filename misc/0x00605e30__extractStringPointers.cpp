// FUNC_NAME: extractStringPointers
// Function at 0x00605e30: Iterates over a buffer of concatenated null-terminated strings (up to bufferSize bytes)
// and stores the address of each string's start into an output array pointed to by in_EAX.
// The caller is expected to have passed the buffer size in EDI (unaff_EDI) and the output pointer in EAX.
void extractStringPointers(char *buffer, char **outputArray)
{
    bool foundString = false;
    unsigned int offset = 0;
    unsigned int bufferSize = unaff_EDI; // uninitialized register; caller must set EDI

    if (bufferSize != 0) {
        do {
            if (buffer[offset] == '\0') {
                foundString = false;
            }
            else if (!foundString) {
                *outputArray = &buffer[offset]; // store pointer to start of string
                outputArray++;
                foundString = true;
            }
            offset++;
        } while (offset < bufferSize);
    }
    // After the loop, outputArray points past the last stored pointer; caller can compute count.
    return;
}