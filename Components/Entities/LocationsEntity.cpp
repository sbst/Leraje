#include "pch.h"
#include "Components/Entities/LocationsEntity.h"

using namespace Leraje::Entities;
using namespace Leraje::Database::Tables;
using namespace std;

LocationsEntity::LocationsEntity(fastcgi::ComponentContext* context)
  : fastcgi::Component(context), Leraje::Entities::Entity(context)
{}

bool LocationsEntity::handleCustomRequest(fastcgi::Request& request)
{
  request.setStatus(404);
  return true;
}

void LocationsEntity::loadDatabase()
{
  db->LoadDatabase("locations", this);
  cout << "Database loaded for locations..." << endl;
}

void LocationsEntity::OutcomeData(TableRow* _data, JsonTree& tree)
{
  auto data = static_cast<LocationsTableRow*>(_data);
  tree.put("place", data->place);
  tree.put("country", data->country);
  tree.put("city", data->city);
  tree.put("distance", data->distance);
}

shared_ptr<ITableConnector::TableRow> LocationsEntity::IncomeData(JsonTree* tree)
{
  auto data = make_shared<LocationsTableRow>();
  data->place = tree->get<string>("place");
  data->country = tree->get<string>("country");
  data->city = tree->get<string>("city");
  data->distance = tree->get<int32_t>("distance");
  return data;
}

void LocationsEntity::UpdateData(TableRow* _data, JsonTree* tree)
{
  LocationsTableRow& data = *(static_cast<LocationsTableRow*>(_data));
  data.place = tree->get<string>("place");
  data.country = tree->get<string>("country");
  data.city = tree->get<string>("city");
  data.distance = tree->get<int32_t>("distance");
}
