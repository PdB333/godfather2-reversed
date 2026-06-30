// FUNC_NAME: AsyncResource::getData
__thiscall uint AsyncResource::getData(AsyncResource* this) {
    if (this->isLoaded) { // +0x28
        uint flags = 0;
        if (this->someFlag) { // +0x8
            flags = 0x3000;
        }
        // Virtual function at vtable+0x2c (likely "beginLoad")
        (this->vtable->beginLoad)(this, 0, 0, &this->data, flags); // +0x14
        return this->data;
    }
    this->loadRequested = 1; // +0x29
    return this->defaultValue; // +0x1c
}