// FUNC_NAME: Object::Initialize
void __thiscall Object::Initialize(void) {
    uint32_t handle1 = GetUniqueHandle();
    *(uint32_t*)(this + 0x10) = handle1;
    uint32_t handle2 = GetObjectByName(&PTR_DAT_00f1100c);  // global string/resource
    *(uint32_t*)(this + 0x14) = handle2;
    PerformBaseInitialization();  // likely base class init
    *(uint32_t*)(this + 0xa4) = *(uint32_t*)(this + 0x10);  // copy handle to later field
    uint32_t handle3 = GetUniqueHandle();
    *(uint32_t*)(this + 0xa8) = handle3;
    return;
}