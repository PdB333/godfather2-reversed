// FUNC_NAME: ObjectBase::release
void ObjectBase::release(void)
{
  int refCountBeforeRelease;
  
  refCountBeforeRelease = this->releaseRef();
  if (refCountBeforeRelease != 0) {
    FUN_009c8eb0(refCountBeforeRelease); // likely deleteObject(refCountBeforeRelease)
  }
  return;
}