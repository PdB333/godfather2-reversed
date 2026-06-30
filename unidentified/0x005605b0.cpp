// FUN_NAME: ProcessGlobalAnimationUpdate

void __fastcall FUN_005605b0(uint32_t inputData, uint32_t playerIndex, void* playerContext)
{
    // inputData: pointer to controller input (ECX)
    // playerIndex: player slot index (EDX)
    // playerContext: pointer to game object containing character at offset 0x18 (stack)
    // Global controller instance stored in ESI register (gs_animationController)
    // Offsets: this+0x8 = animation handle, this+0xC = some data

    uint8_t animOutput[28]; // local_20

    // Copy or process input with player index and context data
    FUN_009de610(playerIndex, inputData, *(gs_animationController + 0xC), *(int*)(playerContext + 0x18));

    // Update internal state of animation controller
    FUN_0053f390(gs_animationController);

    uint32_t animHandle = *(uint32_t*)(gs_animationController + 8);
    int* character = *(int**)(playerContext + 0x18); // character object pointer

    // Global update (e.g., frame start)
    FUN_009f2000();

    // Call virtual function on character at vtable offset 0x58 (e.g., ApplyAnimation)
    (*(void (**)(uint32_t, uint8_t*))(*(character + 0xD0) + 0x58))(animHandle, animOutput);
}