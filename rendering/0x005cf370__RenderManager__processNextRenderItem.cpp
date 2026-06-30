// FUNC_NAME: RenderManager::processNextRenderItem
// Function at 0x005cf370: Processes the next item from a linked list, computes screen rectangle, and removes it.
// Global data: g_renderManager (0x01205668) - singleton manager instance
// The function allocates a node from a pool, registers it, computes screen coordinates, then removes it from the active list.
// The node structure (at iVar6) stores integer coordinates:
//   +0x08: left X
//   +0x0C: top Y
//   +0x10: right X (or width-related)
//   +0x14: bottom Y (or height-related)
// The linked list uses offset +0x94 as a `next` pointer.
// Manager offsets: head at +0x50, tail at +0x4C, something at +0x10 (passed to GetScreenRect).

// These globals are scaling factors and an offset constant.
extern float g_scaleX;          // DAT_01222214
extern float g_scaleY;          // DAT_01222218
extern float g_offsetConstant;  // DAT_00e2b1a4 (used for both axes)

extern RenderManager* g_renderManager;  // DAT_01205668

// Forward declarations of internal helpers.
static int AllocateNode(int param_a, int param_b, int param_c, int param_e, int param_b2, int param_f, int param_g);
static int RegisterNode(int handle);  // returns iVar6
static void GetScreenRect(int managerOffset, int handle, char outBuf1[16], char outBuf2[16], char outBuf3[76],
                           int zero1, int zero2, int zero3, int zero4, int someFlag);
static void ProcessRemovedNode();  // possibly updates state after removing node

int __fastcall RenderManager::processNextRenderItem(
    void* dummy_ecx,
    void* dummy_edx,
    float* outX,
    float* outY,
    float* outWidth,
    float* outHeight,
    int param7, int param8, int param9,
    int param10, int param11, int param12, int param13)
{
    RenderManager* mgr = g_renderManager;
    
    // Allocate a node? Call with many arguments.
    int* allocatedPtr = (int*)AllocateNode(param7, param8, param9, param11, param2, param12, param13);
    int handle = RegisterNode(*allocatedPtr);  // returns iVar6
    
    if (handle != 0)
    {
        char buf1[16];
        char buf2[16];
        char buf3[76];
        
        GetScreenRect((int)mgr + 0x10, handle, buf1, buf2, buf3, 0, 0, 0, 0, 1);
        
        // Compute screen rectangle from node's integer coordinates
        *outX = (float)(*(int*)(handle + 8)) * g_scaleX;
        *outY = (float)(*(int*)(handle + 0xC)) * g_scaleY;
        
        // Width = (right + left - g_offsetConstant) * g_scaleX
        *outWidth = ((float)(*(int*)(handle + 0x10) + *(int*)(handle + 8)) - g_offsetConstant) * g_scaleX;
        // Height = (bottom + top - g_offsetConstant) * g_scaleY
        *outHeight = ((float)(*(int*)(handle + 0x14) + *(int*)(handle + 0xC)) - g_offsetConstant) * g_scaleY;
        
        // Remove the node from the singly-linked list (head at mgr+0x50, tail at mgr+0x4C)
        int currentHead = *(int*)((char*)mgr + 0x50);
        if (currentHead != 0)
        {
            *(int*)((char*)mgr + 0x50) = *(int*)(currentHead + 0x94);  // head = head->next
            if (*(int*)((char*)mgr + 0x4C) == currentHead)
            {
                *(int*)((char*)mgr + 0x4C) = *(int*)(*(int*)((char*)mgr + 0x4C) + 0x94);  // tail = tail->next
            }
            ProcessRemovedNode();
        }
        
        // If list is now empty, set head to tail (makes list head = tail)
        if (*(int*)((char*)mgr + 0x50) == 0)
        {
            *(int*)((char*)mgr + 0x50) = *(int*)((char*)mgr + 0x4C);
        }
        
        return 1;
    }
    
    return 0;
}