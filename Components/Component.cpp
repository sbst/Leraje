#include "pch.h"
#include "Component.h"

using namespace Leraje::Components;
using namespace std;

Component::Component(fastcgi::ComponentContext *context)
  : IComponent(context)
{}

Component::~Component()
{}

void Component::onLoad()
{
  db = Database::Database::GetDatabase();
  loadDatabase();
}

void Component::onUnload()
{}

void Component::handleRequest(fastcgi::Request* request, fastcgi::HandlerContext* context)
{
  request->setContentType("text/plain; charset=utf-8");
  if(request->getRequestMethod() == "GET") getDataFromTable(*request);
  else handleCustomRequest(*request);
}

void Component::getDataFromTable(fastcgi::Request& request)
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
