// FUNC_NAME: initializeAudioStream
void initializeAudioStream(void)
{
    int* objectPtr;
    float duration;
    float currentPos;

    // Check if audio manager pointer is valid and its type ID is not 0x1f30
    if ( ((*(int**)(*(int*)0x012233a0 + 4) != 0) && 
          (*(int**)(*(int*)0x012233a0 + 4) != 0x1f30)) )
    {
        // Get audio stream object from global handle
        objectPtr = (int*)FUN_0043b870((void*)0x01131018); // getAudioStream
        if ( (objectPtr != 0) && (g_audioStartTime < 0.0f) )
        {
            // Query stream duration and set start time
            duration = (*(float (*)())(*objectPtr + 0x28))(); // vtable+0x28: getDuration
            g_audioStartTime = duration;
            currentPos = (*(float (*)())(*objectPtr + 0x2c))(); // vtable+0x2c: getCurrentPosition
            (*(void (*)(float))(*objectPtr + 0x3c))(currentPos); // vtable+0x3c: setPosition / seek
        }
    }
    g_someFlag = 0;
    FUN_004464d0(&LAB_00842e60); // runScript
    return;
}