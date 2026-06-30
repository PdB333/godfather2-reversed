// FUNC_NAME: EARS::ContainerIterator::nextElement
void __fastcall ContainerIterator::nextElement(uint32_t* outBuffer) {
    void* currentPtr = *(void**)(this + 8); // +0x8: current element pointer

    switch (eax) { // eax = function code (from register)
        case 1:
        case 3: {
            // Retrieve key/value from current node
            int32_t* node = (int32_t*)currentPtr;
            outBuffer[0] = *(node - 2); // key or first value
            outBuffer[1] = *(node - 1); // value or second element
            break;
        }
        case 4: {
            // Allocate new node / generate fresh output
            outBuffer[0] = 4; // size? type?
            outBuffer[1] = allocateNodeId(); // FUN_00638920
            break;
        }
        case 5: {
            // Similar to case 4
            outBuffer[0] = 4;
            outBuffer[1] = allocateNodeId();
            break;
        }
        // default: does nothing (no write to outBuffer)
    }

    // Advance internal pointer past the output
    *(void**)(this + 8) = outBuffer + 2;
}