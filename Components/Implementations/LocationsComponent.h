#pragma once

#include "Components/Component.h"

namespace Leraje
{
  namespace Components
  {
    class LocationsComponent : public Component
    {
    public:
      LocationsComponent(fastcgi::ComponentContext *context);

      virtual bool handleCustomRequest(fastcgi::Request& request) override;

      virtual void loadDatabase() override;
    };
  }
}
