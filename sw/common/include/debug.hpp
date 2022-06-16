#pragma once

#ifdef MYDEBUG
#define DEBUG_MSG(str) do{cout << str << endl;} while(false)
#else
#define DEBUG_MSG(str) do{} while(false)
#endif
