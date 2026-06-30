// FUNC_NAME: SomeClass::update
void SomeClass::update() {
    // +0x00: flags (uint32), +0x02: timer (short)
    this->preUpdate(); // FUN_005a72f0

    if (*(short *)((int)this + 2) == 0) {
        // Check if bit 15 of flags is set
        if ((this->flags & 0x8000) != 0) {
            void* context = this->getContext();
            this->processContext(context);
        }

        void* obj = this->getContext(); // get another object (maybe same)
        if (obj != nullptr) {
            this->prepareAction();
            gEventDispatcher(obj, 0x70); // dispatch event 0x70
        }
    }
}