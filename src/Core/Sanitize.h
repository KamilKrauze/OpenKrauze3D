#ifndef SANITIZE_H
#define SANITIZE_H

#include "minimal.h"

#include <typeinfo>

/*
Checks for nullptrs
- True:	not nullptr
- False: nullptr
*/
#define checkptr(pObj)	(pObj != nullptr) 


/* Checks if value is NULL
- True:	not null
- False : nullptr
*/
#define CHECK(value) ( static_cast<decltype(value)>(value) != NULL )

#endif // !SANITIZE_H

