// FUN_00493070: EARSObject::shutdown
void EARSObject::shutdown() {
    // Perform base cleanup (e.g., release common resources)
    this->releaseBaseResources();

    // Release audio subsystem if active
    if (this->audioPtr != nullptr) {
        this->releaseAudio(this->contextHandle, this->audioPtr, &this->audioFinishFlag);
    }

    // Release input subsystem if active
    if (this->inputPtr != nullptr) {
        this->releaseInput(this->contextHandle, this->inputPtr, &this->inputFinishFlag);
    }

    // Release render subsystem if active
    if (this->renderPtr != nullptr) {
        this->releaseRender(this->contextHandle, this->renderPtr, &this->renderFinishFlag);
    }

    // Release UI subsystem if active
    if (this->uiPtr != nullptr) {
        this->releaseUI(this->contextHandle, this->uiPtr, &this->uiFinishFlag);
    }

    // Release another render instance if active
    if (this->renderPtr2 != nullptr) {
        this->releaseRender(this->contextHandle, this->renderPtr2, &this->renderFinishFlag2);
    }
}

// Members and offsets (for documentation):
// +0x14: contextHandle (e.g., module ID or handle)
// +0x1f0: audioPtr
// +0x1f8: inputPtr
// +0x200: audioFinishFlag
// +0x240: renderPtr
// +0x244: renderFinishFlag
// +0x24c: uiPtr
// +0x250: uiFinishFlag
// +0x260: renderPtr2
// +0x264: renderFinishFlag2