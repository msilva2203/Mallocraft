/**
 * @file SandboxInstance.h
 * @author Marco Silva (msilva2203)
 */

#include "Utility.h"
#include "Framework/Instance.h"

class SandboxInstance : public Instance
{
    using Super = Instance;
public:

    virtual void Setup() override;

private:


};