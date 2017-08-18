#pragma once

#include "Database/Database.h"

#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include <iostream>
#include <sstream>

#include <memory>

namespace Leraje
{
  namespace Components
  {
    class Component : virtual public fastcgi::Component, virtual public fastcgi::Handler
    {
    protected:
      Component(fastcgi::ComponentContext *context);

      virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) = 0;

      virtual void loadDatabase() = 0;

      virtual ~Component();

      std::shared_ptr<Database::Database> db;

    private:
      virtual void onLoad();

      virtual void onUnload();
    };
  }
}
