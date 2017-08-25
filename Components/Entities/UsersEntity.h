#pragma once

#include "Components/Entity.h"

namespace Leraje
{
  namespace Entities
  {
    class UsersEntity : public Entity
    {
    public:
      UsersEntity(fastcgi::ComponentContext* context);

      virtual bool handleCustomRequest(fastcgi::Request& request) override;

      virtual void loadDatabase() override;

      virtual void OutcomeData(TableRow* data, Database::Tables::JsonTree& tree) override;

      virtual std::shared_ptr<TableRow> IncomeData(Database::Tables::JsonTree* tree) override;

      virtual void UpdateData(TableRow* _data, Database::Tables::JsonTree* tree) override;

      struct UsersTableRow : public TableRow
      {
        std::string email;
        std::string firstName;
        std::string lastName;
        char gender;
        int64_t birthDate;
      };
    };
  }
}
