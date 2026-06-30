// FUNC_NAME: ComponentDispatcher::callMethod
void ComponentDispatcher::callMethod(void* object, uint32_t param, uint32_t componentOffset) {
    // (*(code **)(uint32_t**)(gGlobal + 0x2D4))(object + componentOffset, param);
    void (*method)(void*, uint32_t) = **(void (***)(void*, uint32_t))(gGlobal + 0x2D4);
    method((char*)object + componentOffset, param);
}