// FUNC_NAME: AudioStreamManager::releaseAllStreams
void AudioStreamManager::releaseAllStreams()
{
    uint count;

    // If there are streams allocated (array pointer and count non-zero)
    if ((this->streamCount != 0) && (this->streamArray != nullptr)) {
        count = 0;
        if (this->streamCount != 0) {
            do {
                // Release each stream object twice (e.g., two references)
                releaseSubObject();
                releaseSubObject();
                count++;
            } while (count < this->streamCount);
        }
        // Free the array of streams
        freeMemory(this->streamArray);
        this->streamArray = nullptr;
        this->streamCount = 0;
    }

    // If a single master stream exists, free it
    if (this->masterStream != nullptr) {
        freeMemory(this->masterStream);
        this->masterStream = nullptr;
        this->masterStreamSize = 0;  // +0xA0
    }

    // Reset other member variables
    this->field_04 = 0;  // +0x04
    this->field_08 = 0;  // +0x08
    this->unknown1 = 0;  // +0x90
    this->unknown2 = 0;  // +0x94
    this->basePointer = nullptr;  // +0x00
    this->field_A8 = 0;  // +0xA8
}