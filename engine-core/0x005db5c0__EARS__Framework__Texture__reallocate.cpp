// FUNC_NAME: EARS::Framework::Texture::reallocate
// Address: 0x005db5c0
// Reallocates the texture buffer when dimensions change or first allocation.
// param_1 is bits per pixel (e.g., 32 for RGBA)
void __thiscall Texture::reallocate(int bpp) {
    // Globals from DAT_
    static int* g_width = (int*)0x012056b4;      // Current global width (e.g., screen width)
    static int* g_height = (int*)0x012056b8;     // Current global height
    static void* (*pAlloc)(uint, int) = (void* (*)(uint, int))0x0119caf0; // Allocation function
    static void (*pFree)(void*) = (void(*)(void*))0x0119caf4;              // Free function
    static int* g_counter = (int*)0x0103ae2c;    // Unique ID counter
    static int* g_cmdBufPtr = (int*)(*(int*)0x01206880 + 0x14); // Command buffer pointer

    int newWidth = *g_width;
    int newHeight = *g_height;

    // Only proceed if width/height are set and either this texture is new (m_id==0) or dimensions changed
    if (*g_width != 0 && *g_height != 0 &&
        (m_id == 0 || m_width != *g_width || m_height != *g_height)) {

        // Update dimensions
        m_width = *g_width;
        m_height = *g_height;

        // Free old buffer if exists
        if (m_buffer != nullptr) {
            pFree(m_buffer);
        }

        // Allocate new buffer size = (width * height * bpp) / 8
        uint size = (uint)(m_width * m_height * bpp) >> 3;
        m_bufferSize = size;
        m_buffer = pAlloc(size, 0);

        // Generate unique IDs if needed (seems to assign consecutive counters)
        if (m_texId1 == 0) {
            *g_counter = *g_counter + 1;
            m_texId1 = *g_counter;
        }
        // Some internal state reset
        m_state = 0;

        if (m_texId2 == 0) {
            *g_counter = *g_counter + 1;
            m_texId2 = *g_counter;
        }

        if (m_id == 0) {
            *g_counter = *g_counter + 1;
            m_id = *g_counter;
        }

        // Record a command to the global command buffer
        int res = FUN_00606c80(9, 0x200000, m_width, m_height, 1, 0xffffffff);
        int* ptr = g_cmdBufPtr;
        *(int**)ptr = &PTR_LAB_011273a4;  // Some vtable or resource type pointer
        ptr += 4;
        *ptr = m_texId2;
        ptr += 4;
        *ptr = m_id;
        ptr += 4;
        *ptr = res;
        ptr += 4;
        g_cmdBufPtr = ptr; // Update global pointer
    }
}