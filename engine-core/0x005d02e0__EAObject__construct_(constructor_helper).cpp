// FUNC_NAME: EAObject::construct (constructor helper)
int __thiscall EAObject::construct(EAObject *this) {
    // Adjust pointer to include allocation header at offset -4
    EAObject *obj = (EAObject *)((char *)this - 4);

    // Memory/object initialization: this pointer, size 0x90, class info from header, constructor callback
    MemoryManager::initObject(this, 0x90, *(int *)((char *)this - 4), reinterpret_cast<void (*)()>(0x005cffc0));

    // Post-construction validation check
    if (!ObjectDebugger::validate(obj)) {
        // If validation fails, call global manager (at DAT_012234ec + 4) error handler
        Manager *mgr = *(Manager **)((char *)DAT_012234ec + 4);
        mgr->vtable->errorHandler(obj, 0);
    }

    return (int)obj;
}