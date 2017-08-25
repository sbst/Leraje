#include "pch.h"
#include "Components/Entities/VisitsEntity.h"

using namespace Leraje::Entities;
using namespace Leraje::Database::Tables;
using namespace std;

VisitsEntity::VisitsEntity(fastcgi::ComponentContext* context)
  : fastcgi::Component(context), Leraje::Entities::Entity(context)
{}

bool VisitsEntity::handleCustomRequest(fastcgi::Request& request)
{
  request.setStatus(404);
  return true;
}

void VisitsEntity::loadDatabase()
{
  db->LoadDatabase("visits", this);
  cout << "Database loaded for visits..." << endl;
}

void VisitsEntity::OutcomeData(TableRow* _data, Database::Tables::JsonTree& tree)
{
  auto data = static_cast<VisitsTableRow*>(_data);
  tree.put("location", data->location);
  tree.put("user", data->user);
  tree.put("visited_at", data->visitedAt);
  tree.put("mark", data->mark);
}

shared_ptr<ITableConnector::TableRow> VisitsEntity::IncomeData(Database::Tables::JsonTree* tree)
{
  auto data = make_shared<VisitsTableRow>();
  data->location = tree->get<int32_t>("location");
  data->user = tree->get<int32_t>("user");
  data->visitedAt = tree->get<int64_t>("visited_at");
  data->mark = tree->get<int8_t>("mark");
  return data;
}

void VisitsEntity::UpdateData(TableRow* _data, JsonTree* tree)
{
  VisitsTableRow& data = *(static_cast<VisitsTableRow*>(_data));
  data.location = tree->get<int32_t>("location");
  data.user = tree->get<int32_t>("user");
  data.visitedAt = tree->get<int64_t>("visited_at");
  data.mark = tree->get<int8_t>("mark");
}
