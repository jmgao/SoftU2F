//
//  SoftU2FDriver.cpp
//  SoftU2F
//
//  Created by Benjamin P Toews on 1/12/17.
//

#include <IOKit/IOLib.h>
#include "SoftU2FDriver.hpp"

#define super IOService
OSDefineMetaClassAndStructors(SoftU2FDriver, IOService);

bool SoftU2FDriver::start(IOService *provider) {
  IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);

  if (!super::start(provider))
    return false;

  _workLoop = IOWorkLoop::workLoop();
  if (!_workLoop)
    return false;

  registerService();

  return true;
}

void SoftU2FDriver::free() {
  IOLog("%s[%p]::%s()\n", getName(), this, __FUNCTION__);
  OSSafeReleaseNULL(_workLoop);
  super::free();
}

IOWorkLoop* SoftU2FDriver::getWorkLoop() const {
  return _workLoop;
}
