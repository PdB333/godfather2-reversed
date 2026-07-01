// FUNC_NAME: CommandBuffer::PushCommand
// Address: 0x00943ec0
// Role: Writes a command entry into the global command buffer. The entry consists of a function pointer (stub), an object pointer, and two unsigned 32-bit arguments.
// The command buffer is a linear buffer growing sequentially. The write pointer is stored at offset +0x14 of the global CommandBuffer singleton.

#include <cstdint>

// Global command buffer instance
extern CommandBuffer* g_commandBuffer;

// External function: writes data to the command buffer starting at the current write pointer,
// advances the internal pointer by size*count. (Function at 0x0049c430)
void BufferWrite(const void* data, uint32_t size, uint32_t count);

// Static constant: pointer to a thunk that dispatches a member function call from the stored object pointer
extern void* g_methodCallStub; // PTR_FUN_00e5699c

class CommandBuffer {
public:
    // Push a method call command: call a specific method on object pObject with arguments arg0 and arg1
    static void PushCommand(void* pObject, uint32_t arg0, uint32_t arg1) {
        // Retrieve the current write pointer from the global instance
        // g_commandBuffer + 0x14 points to a void* that is the current buffer write pointer
        void** writePtr = *reinterpret_cast<void***>(reinterpret_cast<uint8_t*>(g_commandBuffer) + 0x14);
        
        // Write the method call stub pointer
        *writePtr = &g_methodCallStub;
        writePtr++;
        
        // Write the object pointer
        *writePtr = pObject;
        writePtr++;
        
        // Write arg0 via the buffer write function (copies 4 bytes and advances the buffer internally)
        BufferWrite(&arg0, 4, 4);
        
        // Write arg1
        *reinterpret_cast<uint32_t*>(writePtr) = arg1;
        writePtr++;
        
        // Update the global write pointer
        *reinterpret_cast<void***>(reinterpret_cast<uint8_t*>(g_commandBuffer) + 0x14) = writePtr;
    }
};