#pragma once

#include "Components/Component.h"

namespace Leraje
{
  namespace Components
  {
    class VisitsComponent : public Component
    {
    public:
      VisitsComponent(fastcgi::ComponentContext *context);

      virtual bool handleCustomRequest(fastcgi::Request& request) override;

      virtual void loadDatabase() override;
    };
  }
}
