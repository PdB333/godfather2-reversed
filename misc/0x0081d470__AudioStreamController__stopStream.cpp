// FUNC_NAME: AudioStreamController::stopStream
void __fastcall AudioStreamController::stopStream(AudioStreamController *this)
{
    // Call pre-stop cleanup (likely flushes or queues)
    FUN_0081c980();

    // Call virtual function at vtable offset 4 (0x04) on the held stream object
    // with a fade duration of 0x2c (44 ms or frames)
    // This is likely IStream::stop(uint32_t fadeDuration)
    (this->vtable->stop)(this->stream + 0x18, 0x2c);

    // Clear the stream pointer to avoid double-release
    this->stream = nullptr;

    // Call post-stop cleanup (likely unregisters callbacks, frees resources)
    FUN_0081d230();
}