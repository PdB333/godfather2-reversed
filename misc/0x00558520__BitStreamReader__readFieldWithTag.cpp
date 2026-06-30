// FUNC_NAME: BitStreamReader::readFieldWithTag
// Address: 0x00558520
// Role: Reads a 32-bit field from a bitstream buffer using a two-bit tag (0x40000000, 0xc0000000) 
// to interpret the upper bits as an index type and the lower 5 bits as a size/count. 
// The actual data decoding is delegated to FUN_00557d80 (readTaggedValue).
// If the decoder state is uninitialized, calls FUN_00558430 (initStream) first.

#include <cstdint>

// Forward declarations for callees
void initStream(uint32_t* bufferPtr);          // FUN_00558430
void readTaggedValue(uint32_t context, int32_t param1, uint32_t thisPtr, uint32_t index); // FUN_00557d80

// Note: The exact class and method names are not known from the Xbox debug symbols,
// but the code structure corresponds to a typical EA EARS bitstream decoder.
// The object (in_EAX) contains at offset +0x1C a pointer to a decoder state struct,
// and at offset +0x10 in that state a context pointer used by the final decoding call.
// The buffer pointer (unaff_ESI) is stored in a member or register (not captured in param list).

void __thiscall BitStreamReader::readFieldWithTag(int32_t param1)
{
    // 'this' is in_EAX, treat as a pointer to the decoder object
    uint32_t* thisPtr = reinterpret_cast<uint32_t*>(this);
    
    // unaff_ESI: assumed to be a buffer pointer (m_bufferPtr) stored in a register
    uint32_t* bufferPtr = unaff_ESI; // from the context, ESI holds a uint* (likely current read position)

    // Lazy initialization: if the decoder state pointer (offset +0x1C) is null, init
    if (thisPtr[7] == 0)          // +0x1C: pointer to decoder state structure
    {
        initStream(bufferPtr);    // FUN_00558430 – sets up the state
    }

    // Get the context pointer from the decoder state (offset +0x10)
    uint32_t context = 0;
    if (thisPtr[7] != 0)
    {
        context = *(uint32_t*)(thisPtr[7] + 0x10); // +0x10 in state: context/aux data
    }

    // Read the next 32-bit word from the buffer
    uint32_t rawValue = *bufferPtr;

    // Extract the two highest bits as tag
    uint32_t tag = rawValue & 0xC0000000;

    if (tag != 0)
    {
        if (tag == 0x40000000)        // Bit30 set, Bit31 clear: direct index table
        {
            // Interpret rawValue as an index into a table at base 0 (rawValue*4)
            // The table base is not passed; likely an external global or register
            uint32_t index = *(uint32_t*)(rawValue * 4);
            readTaggedValue(context, param1, reinterpret_cast<uint32_t>(thisPtr), index & 0x1F);
            return;
        }
        else if (tag == 0xC0000000)   // Both bits set: offset table at +0x4C
        {
            // Interpret rawValue as an index into a table at offset 0x4C (76 bytes)
            uint32_t index = *(uint32_t*)(rawValue * 4 + 0x4C);
            readTaggedValue(context, param1, reinterpret_cast<uint32_t>(thisPtr), index & 0x1F);
            return;
        }
        else
        {
            // Tag = 0x80000000 (Bit31 only): fallback with index = 0
            // Unlikely tag, treat as error/legacy
            readTaggedValue(context, param1, reinterpret_cast<uint32_t>(thisPtr), 0);
            return;
        }
    }
    else
    {
        // tag == 0: use low 5 bits directly
        readTaggedValue(context, param1, reinterpret_cast<uint32_t>(thisPtr), rawValue & 0x1F);
        return;
    }
}