#include "pch.h"
#include "Components/Entities/UsersEntity.h"

using namespace Leraje::Entities;
using namespace Leraje::Database::Tables;
using namespace std;

UsersEntity::UsersEntity(fastcgi::ComponentContext* context)
  : fastcgi::Component(context), Leraje::Entities::Entity(context)
{}

bool UsersEntity::handleCustomRequest(fastcgi::Request& request)
{
  request.setStatus(404);
  return true;
}

void UsersEntity::loadDatabase()
{
  db->LoadDatabase("users", this);
  cout << "Database loaded for users..." << endl;
}

void UsersEntity::OutcomeData(uint32_t id, TableRow* _data, boost::property_tree::ptree& tree)
{
  auto data = static_cast<UsersTableRow*>(_data);
  tree.put("email", data->email);
  tree.put("first_name", data->firstName);
  tree.put("last_name", data->lastName);
  tree.put("gender", data->gender);
  tree.put("birth_date", data->birthDate);
}

shared_ptr<ITableConnector::TableRow> UsersEntity::IncomeData(boost::property_tree::ptree* tree)
{
  auto data = make_shared<UsersTableRow>();
  data->email = tree->get<string>("email");
  data->firstName = tree->get<string>("first_name");
  data->lastName = tree->get<string>("last_name");
  data->gender = tree->get<char>("gender");
  data->birthDate = tree->get<int64_t>("birth_date");
  return data;
}
