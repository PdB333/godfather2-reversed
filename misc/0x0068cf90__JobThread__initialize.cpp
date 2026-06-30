// FUNC_NAME: JobThread::initialize
void* __fastcall JobThread::initialize(JobThread* this)
{
    // Call to base class or sub-initializer
    FUN_00ab5450();

    // Copy garbage from stack into fields; likely not intended, may be a decompiler artifact
    this->field_4 = local_14;  // stack garbage
    this->field_8 = local_10;  // stack garbage
    this->field_C = local_c;   // stack garbage

    // Set maximum job count (0x3f = 63)
    this->maxJobs = 63;

    // Thread name string pointer
    this->threadName = "Job Manager - Job Thread";

    // Byte flag at offset 6 (24 bytes into structure)
    *reinterpret_cast<uint8_t*>(&this->field_18) = 0;   // offset 0x18

    // Initialize first field to null
    this->field_0 = 0;

    return this;
}