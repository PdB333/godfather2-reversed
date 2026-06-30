// FUNC_NAME: EARSObject::cleanupEmbeddedContainers
void __fastcall EARSObject::cleanupEmbeddedContainers(void* this) {
    // Clean up sub-object at offset +0x84
    cleanupSubObject((void*)((char*)this + 0x84));
    // Clean up sub-object at offset +0x9c
    cleanupSubObject((void*)((char*)this + 0x9c));
    // Clean up sub-object at offset +0xa8
    cleanupSubObject((void*)((char*)this + 0xa8));
    // Clean up sub-object at offset +0xb4
    cleanupSubObject((void*)((char*)this + 0xb4));
}