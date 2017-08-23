#pragma once

#include "Components/Entity.h"

namespace Leraje
{
  namespace Entities
  {
    class VisitsEntity : public Entity
    {
    public:
      VisitsEntity(fastcgi::ComponentContext* context);

      virtual bool handleCustomRequest(fastcgi::Request& request) override;

      virtual void loadDatabase() override;

      virtual void OutcomeData(uint32_t id, TableRow* data, Database::Tables::JsonTree& tree) override;

      virtual std::shared_ptr<TableRow> IncomeData(Database::Tables::JsonTree* tree) override;

      struct VisitsTableRow : public TableRow
      {
        int32_t location;
        int32_t user;
        int64_t visitedAt;
        int8_t mark;
      };
    };
  }
}
