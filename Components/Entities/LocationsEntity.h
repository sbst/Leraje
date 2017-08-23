#pragma once

#include "Components/Entity.h"

namespace Leraje
{
  namespace Entities
  {
    class LocationsEntity : public Entity
    {
    public:
      LocationsEntity(fastcgi::ComponentContext* context);

      virtual bool handleCustomRequest(fastcgi::Request& request) override;

      virtual void loadDatabase() override;

      virtual void OutcomeData(uint32_t id, TableRow* data, Database::Tables::JsonTree& tree) override;

      virtual std::shared_ptr<TableRow> IncomeData(Database::Tables::JsonTree* tree) override;

      struct LocationsTableRow : public TableRow
      {
        std::string place;
        std::string country;
        std::string city;
        int32_t distance;
      };
    };
  }
}
