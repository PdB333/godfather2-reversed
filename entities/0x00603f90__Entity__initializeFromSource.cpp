// FUNC_NAME: Entity::initializeFromSource
void __thiscall Entity::initializeFromSource(void *this, undefined4 param_2, undefined4 param_3, undefined4 param_4) {
    // Copy data from source (param_2) using size/options (param_3, param_4)
    // Likely copies a block of memory or initializes multiple fields
    sub_603D30(param_2, param_3, param_4);
    
    // Initialize the sub‑object stored at offset +0x74 (e.g., a component, transform, or physics state)
    sub_4D4300((void *)((unsigned char *)this + 0x74));
}