#include "pch.h"
#include "Components/Entity.h"

using namespace Leraje::Entities;
using namespace std;

Entity::Entity(fastcgi::ComponentContext *context)
  : fastcgi::Component(context), IComponent(context)
{}

Entity::~Entity()
{}

void Entity::onLoad()
{
  db = Database::Database::GetDatabase();
  loadDatabase();
}

void Entity::onUnload()
{}

void Entity::handleRequest(fastcgi::Request* request, fastcgi::HandlerContext* context)
{
  request->setContentType("text/plain; charset=utf-8");
  if(request->getRequestMethod() == "GET") getDataFromTable(*request);
  else if (request->getRequestMethod() == "POST") setDataToTable(*request);
  else handleCustomRequest(*request);
}

void Entity::getDataFromTable(fastcgi::Request& request)
{
  string result = "";
  uint32_t val = 0;
  char tableName[20];
  sscanf(request.getURI().c_str(), "/%[^/]/%d", tableName, &val);
  if (db->ReadFromTable(tableName, val, result))
  {
    stringbuf buffer(result);
    request.write(&buffer);
    request.setStatus(200);
  }
  else
    request.setStatus(404);
}
// TODO: email should be unique field
void Entity::setDataToTable(fastcgi::Request& request)
{
  bool result = false;
  char tableName[20];
  if (request.getURI().find("new") != string::npos)
  {
    result = true;
    sscanf(request.getURI().c_str(), "/%[^/]/new", tableName);
    vector<string> files;
    request.argNames(files);
    for (auto it : files)
    {
      if (!db->WriteToTable(tableName, it))
      {
        result = false;
      }
    }
  }

  if (result)
  {
    stringbuf buffer("{}");
    request.write(&buffer);
    request.setStatus(200);
  }
  else
    request.setStatus(400);

}
