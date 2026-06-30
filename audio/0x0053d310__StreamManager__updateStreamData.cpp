// FUNC_NAME: StreamManager::updateStreamData
void __fastcall StreamManager::updateStreamData(int this)
{
    int iVar1;
    int localBuffer[4];  // 16 bytes on stack

    // Call base class or system update
    FUN_00612a60();

    // Check if a specific stream source matches a global identifier
    if (*(int*)(this + 0x10) == DAT_01219908 && DAT_01219928 != 0) {
        localBuffer[0] = 0;
        localBuffer[1] = 0;
        localBuffer[2] = 0;
        localBuffer[3] = 0;
        // Copy data from global into local buffer
        FUN_0060add0(*(int*)(this + 0x10), DAT_01219928, localBuffer);
    }

    // Call another update routine
    FUN_0053d200();

    // Get current index into stream source array (array at +0xf0, element size 0x20)
    int currentIndex = *(int*)(this + 0x2a8);   // +0x2a8: current stream index

    // Check first field of the selected stream source element
    int* streamElementBase = (int*)(this + 0xf0 + currentIndex * 0x20);
    if (streamElementBase[0] != 0) {
        FUN_006063b0(); // Unknown function, maybe flush or prepare
    }

    // Check four 4-byte fields in the stream element, copy to corresponding output buffers
    if (streamElementBase[1] != 0) { // field at +0x04
        FUN_0060add0(*(int*)(this + 0x14), streamElementBase[1], this + 0xb0); // buffer at +0xb0
    }
    if (streamElementBase[2] != 0) { // field at +0x08
        FUN_0060add0(*(int*)(this + 0x14), streamElementBase[2], this + 0xc0); // buffer at +0xc0
    }
    if (streamElementBase[3] != 0) { // field at +0x0c
        FUN_0060add0(*(int*)(this + 0x14), streamElementBase[3], this + 0xd0); // buffer at +0xd0
    }

    // Final update call
    FUN_0053d590();
}