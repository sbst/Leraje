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

      virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) override;

      virtual void loadDatabase() override;
    };
  }
}
