// FUNC_NAME: ComponentPair::initializeFromSource
void __thiscall ComponentPair::initializeFromSource(void* source) {
    // Copy/init first component at offset +0x8 from source
    initComponentA(source, reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 8));
    // Copy/init second component at offset +0x10 from source
    initComponentB(source, reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x10));
}