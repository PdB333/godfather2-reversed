// Xbox PDB: EA::Jobs::JobThreadParameters::JobThreadParameters
// FUNC_NAME: JobThread::ctor
undefined4 * __fastcall JobThread::ctor(JobThread *this)
{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  // Call base initializer or system thread init function
  FUN_00ab5450(); // likely thread init / create system thread
  
  this->field_04 = local_14;  // +0x04: garbage, set from uninitialized local (maybe placeholder)
  this->field_08 = local_10;  // +0x08
  this->field_0C = local_c;   // +0x0C
  this->stackSize = 0x3f;     // +0x10: thread stack size (63?)
  this->threadName = "Job Manager - Job Thread"; // +0x14: pointer to string literal
  *(uint8 *)&this->field_18 = 0; // +0x18: byte flag (e.g., thread running flag)
  this->field_00 = 0;          // +0x00: first DWORD (flags or state)
  
  return this;
}