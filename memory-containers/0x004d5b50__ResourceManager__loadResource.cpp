// FUNC_NAME: ResourceManager::loadResource
// Address: 0x004d5b50
// Role: Loads a resource (e.g., texture/shader) from file, with optional extension-stripping fallback
// Struct: ResourceRequest
//   +0x00: const char* filename (input)
//   +0x04: int flags (non-zero = load, zero = clear output)
// Object (this in ESI):
//   +0x00: char workingBuffer[?] (3 pointers? but used as char*)
//   +0x10: int loadState?
//   +0x14: function pointer deallocator
//   +0x18: function pointer deallocator2
void ResourceManager::loadResource(ResourceRequest* request)
{
    if (request->flags != 0) {
        this->loadFile(request->filename);                     // FUN_004d3bc0
        this->setLoadState(1);                                // FUN_004d5900

        char* dotPos = strchr(this->workingBuffer, '.');      // local_20[0] is this->workingBuffer
        if (dotPos == nullptr) {
            this->loadFile(this->workingBuffer);               // FUN_004d3b50
        } else {
            char* baseName;                                    // local_10
            int hasExtension;                                  // local_c
            this->getBaseName(&baseName, &hasExtension);       // FUN_004d4ee0
            if (hasExtension == 0) {
                this->loadFile(this->workingBuffer);
            } else {
                this->loadFile(baseName);
            }
            if (baseName != nullptr) {
                this->m_deallocator(baseName);                 // local_4
            }
        }
        if (this->workingBuffer != nullptr) {
            this->m_deallocator2(this->workingBuffer);         // local_14
        }
        return;
    }
    // Clear output fields (4 dwords at this offsets)
    this->m_output[0] = 0;                                     // unaff_ESI[0]
    this->m_output[1] = 0;                                     // unaff_ESI[1]
    this->m_output[2] = 0;                                     // unaff_ESI[2]
    this->m_output[3] = 0;                                     // unaff_ESI[3]
}