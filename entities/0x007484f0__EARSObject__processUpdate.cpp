// FUNC_NAME: EARSObject::processUpdate
void __fastcall EARSObject::processUpdate(void* this_) {
    // +0x14: custom function pointer (nullable)
    void (*customUpdate)(void*) = *(void (**)(void*))((char*)this_ + 0x14);
    if (customUpdate != 0) {
        customUpdate(this_);
        return;
    }
    // +0x00: default function pointer
    void (*defaultUpdate)(void*) = *(void (**)(void*))((char*)this_ + 0x00);
    defaultUpdate(this_);
}