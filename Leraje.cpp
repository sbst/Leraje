#include "Components/Entities/VisitsEntity.h"
#include "Components/Entities/UsersEntity.h"
#include "Components/Entities/LocationsEntity.h"

using namespace Leraje;

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("Visits"   ,   Entities::VisitsEntity   )
FCGIDAEMON_ADD_DEFAULT_FACTORY("Users"    ,   Entities::UsersEntity    )
FCGIDAEMON_ADD_DEFAULT_FACTORY("Locations",   Entities::LocationsEntity)
FCGIDAEMON_REGISTER_FACTORIES_END()
