

#ifndef __NDP_APPLICATIONBASE_H
#define __NDP_APPLICATIONBASE_H

#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/lifecycle/ModuleOperations.h" //Maybe change?!
//#include "inet/common/lifecycle/NodeOperations.h"

namespace inet {

class INET_API ApplicationBaseNdp : public OperationalBase
{
  public:
    ApplicationBaseNdp();

  protected:
    virtual bool isInitializeStage(int stage) override { return stage == INITSTAGE_APPLICATION_LAYER; }
    virtual bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_APPLICATION_LAYER; }
    virtual bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_APPLICATION_LAYER; }
};

} // namespace inet

#endif // ifndef __INET_APPLICATIONBASE_H

