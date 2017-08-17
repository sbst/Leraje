#pragma once

#include "Components/Component.h"

namespace Leraje
{
  namespace Components
  {
    class UsersComponent : public Component
    {
    public:
      UsersComponent(fastcgi::ComponentContext* context);

      virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) override;

      virtual void loadDatabase() override;
    };
  }
}
