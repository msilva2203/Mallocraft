/**
 * @file World.h
 * @author Marco Silva (msilva2203)
 */

#include "Utility.h"
#include "Framework/Entity.h"

class World : public Entity
{
    using Super = Entity;
public:

    World();
    virtual ~World();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

private:

};