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
