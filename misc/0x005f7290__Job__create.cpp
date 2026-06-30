// FUNC_NAME: Job::create
// Constructor/factory for a Job object (size 0x38 = 56 bytes)
// Allocates memory via operator new (FUN_009c8e50) and initializes fields.
// param_1: likely some identifier or owner pointer stored at +0x08
// Returns a pointer to the new Job object, or null on allocation failure.

Job* Job::create(int param_1) {
    Job* job = (Job*)operator new(0x38); // custom allocator at 0x009c8e50
    if (job != nullptr) {
        // offset +0x00: vtable pointer (set to class-specific vtable)
        job->vtable = &Job_vtable; // PTR_FUN_00e407e4
        // offset +0x04: next pointer (possibly linked list of jobs) - initialized to 0
        job->next = nullptr;
        // offset +0x08: stored parameter (e.g., a reference count or ID)
        job->someId = param_1;
        // offsets +0x0C, +0x10, +0x14, +0x18, +0x1C, +0x20, +0x24, +0x28, +0x2C, +0x30, +0x34: all zeros
        job->field_0x0c = 0;
        job->field_0x10 = 0;
        job->field_0x14 = 0;
        job->field_0x18 = 0;
        job->field_0x1c = 0;
        job->field_0x20 = 0;
        job->field_0x24 = 0;
        job->field_0x28 = 0;
        job->field_0x2c = 0;
        job->field_0x30 = 0;
        job->field_0x34 = 0;
    }
    return job;
}