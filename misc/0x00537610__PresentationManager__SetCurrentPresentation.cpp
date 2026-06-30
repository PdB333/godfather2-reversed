// FUNC_NAME: PresentationManager::SetCurrentPresentation
// Function address: 0x00537610
// Sets the global active presentation pointer and releases two internal resources
// Offsets: +0x10 and +0x14 are sub-object pointers (likely streams or assets)

void PresentationManager::SetCurrentPresentation(Presentation* pPresentation)
{
    g_pCurrentPresentation = pPresentation;                     // DAT_012058e8 = param_1
    ReleaseResource(*(void**)((char*)pPresentation + 0x10));    // FUN_0060a460(*(param_1+0x10))
    ReleaseResource(*(void**)((char*)pPresentation + 0x14));    // FUN_0060a460(*(param_1+0x14))
}