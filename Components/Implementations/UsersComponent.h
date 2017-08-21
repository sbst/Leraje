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

      virtual bool handleCustomRequest(fastcgi::Request& request) override;

      virtual void loadDatabase() override;
    };
  }
}
