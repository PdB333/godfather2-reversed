// FUNC_NAME: CommandBuffer::addCommand
// Reconstructed from 0x005e7370 - EA EARS engine input/command buffer function.
// This function appends a command (byte 0x01) to a fixed-size buffer, generates a unique ID,
// and returns it. The buffer structure:
//   +0x18: char m_buffer[4]  (or larger, but only low 4 bytes checked)
//   +0x1c: uint8_t m_maxSize (max number of commands)
//   +0x1d: uint8_t m_currentSize (current number of commands)

uint __fastcall CommandBuffer::addCommand(CommandBuffer* thisPtr, uint* outResult)
{
    // outResult is passed in ESI register (non-standard calling convention)
    *outResult = 0;
    uint resultId = thisPtr->m_seed & 0xffffff00; // seed from caller's EAX? Actually in_EAX is from previous context

    if (thisPtr->m_currentSize < thisPtr->m_maxSize && thisPtr->m_maxSize != 0) {
        uint i = 0;
        // Find first null byte in the command buffer (starting at +0x18)
        while (thisPtr->m_buffer[i] != '\0') {
            i++;
            if ((int)(uint)thisPtr->m_maxSize <= (int)i) {
                return resultId;
            }
        }
        // Only allow commands in the first 4 slots? (i < 4)
        if ((byte)i < 4) {
            // Generate a unique ID by XOR with a magic constant
            resultId = (i & 0xff) ^ 0xAD103100;
            *outResult = resultId;
        }
        // Place command byte 0x01 into the found slot
        thisPtr->m_buffer[i] = 0x01;
        thisPtr->m_currentSize++;
        // Combine the low byte of resultId with 0x0100?? Unclear
        resultId = (resultId & 0xFFFFFF00) | 0x01; // CONCAT31(...,1)
    }
    return resultId;
}