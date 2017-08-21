#pragma once

#include "Components/IComponent.h"
#include "Database/Database.h"

namespace Leraje
{
  namespace Components
  {
    class Component : public IComponent
    {
    protected:
      Component(fastcgi::ComponentContext *context);

      virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) override;

      virtual bool handleCustomRequest(fastcgi::Request& request) = 0;

      virtual void loadDatabase() = 0;

      virtual ~Component();

      std::shared_ptr<Database::Database> db;

    private:
      virtual void onLoad() override;

      virtual void onUnload() override;

      void getDataFromTable(fastcgi::Request& request);
    };
  }
}
