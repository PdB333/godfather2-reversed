// FUNC_NAME: Engine::UpdateFrame
void __thiscall Engine::UpdateFrame(Engine* this, uint param_2) {
    // Reset or clear some state with two zero arguments
    ResetState(0, 0);
    // Perform actual frame update logic
    ProcessFrame(this, param_2);
}