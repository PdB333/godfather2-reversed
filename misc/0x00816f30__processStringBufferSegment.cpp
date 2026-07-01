// FUNC_NAME: processStringBufferSegment
void processStringBufferSegment(int param_1, int* param_2, int* param_3, int param_4)
{
    int length = param_2[3]; // +0x0C: length of data in buffer
    if (length != 0)
    {
        char* foundPos = (char*)FUN_00816c30(param_1, param_2 + 2); // searches for something in the buffer
        if (foundPos != nullptr && *foundPos != '\0')
        {
            char* bufferBase = (char*)param_2[2]; // +0x08: pointer to buffer data
            if (bufferBase == nullptr)
            {
                bufferBase = (char*)&DAT_0120546e; // fallback global
            }
            int newLength = length - (foundPos - bufferBase);
            // Copy the substring from foundPos (length newLength) to destination? parameter 0 might be offset or flag
            FUN_004d41f0(0, foundPos, 0, newLength);
            // Remove/shift data before foundPos? offset = foundPos - bufferBase, size = newLength
            FUN_004d45e0(foundPos - bufferBase, newLength);
            // Update size/count fields
            param_2[1] = param_2[3] * param_4; // +0x04: new width/stride?
            param_3[1] = param_3[3] * param_4; // +0x04 in output structure
            *param_3 = *param_2 + param_2[1]; // combine position + size
        }
    }
}