#pragma once

#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>
#include <fastcgi2/stream.h>

#include <iostream>
#include <sstream>

#include <memory>

namespace Leraje
{
  namespace Components
  {
    class IComponent : virtual public fastcgi::Component, virtual public fastcgi::Handler
    {
    protected:
      IComponent(fastcgi::ComponentContext *context) : fastcgi::Component(context) {};

      virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) = 0;

      virtual void loadDatabase() = 0;

      virtual void onLoad() = 0;

      virtual void onUnload() = 0;

      virtual ~IComponent() {};

    };
  }
}
