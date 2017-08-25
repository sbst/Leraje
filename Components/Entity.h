#pragma once

#include "Database/ITableConnector.h"
#include "Components/IComponent.h"
#include "Database/Database.h"

namespace Leraje
{
  namespace Entities
  {
    class Entity : public Components::IComponent, public Database::Tables::ITableConnector
    {
    protected:
      Entity(fastcgi::ComponentContext *context);

      virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) override;

      virtual bool handleCustomRequest(fastcgi::Request& request) = 0;

      virtual void loadDatabase() = 0;

      virtual void OutcomeData(TableRow* data, Database::Tables::JsonTree& tree) = 0;

      virtual std::shared_ptr<TableRow> IncomeData(Database::Tables::JsonTree* tree) = 0;

      virtual void UpdateData(TableRow* _data, Database::Tables::JsonTree* tree) = 0;

      virtual ~Entity();

      std::shared_ptr<Database::Database> db;

    private:
      virtual void onLoad() override;

      virtual void onUnload() override;

      void getDataFromTable(fastcgi::Request& request);

      void setDataToTable(fastcgi::Request& request);
    };
  }
}
