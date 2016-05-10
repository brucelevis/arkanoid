/**
 *
 * @brief Lua Wrapper
 * @author Toni Marquez
 *
 **/

#include "luawrapper.h"

/// constructor
LuaWrapper::LuaWrapper() {

  LUA_ = nullptr;
}

/// init values
void LuaWrapper::init(const char* path) {

  LUA_ = luaL_newstate();
  luaL_openlibs(LUA_);
  if (luaL_dofile(LUA_, path)){ printf("ERROR en Lua\n"); }
}

/**
 * @brief register a function / call the function
 * @param const char* lua_function, lua_CFunction cfunction / none
 * @return void / void
 **/
void LuaWrapper::registerFunction(const char* lua_function, lua_CFunction cfunction) {

  lua_register(LUA_, lua_function, cfunction);
}

void LuaWrapper::callFunction() {

  lua_pcall(LUA_, 0, 0, 0);
}

/**
 * @brief insert global from lua file to the stack and pop it
 * @param const char* global
 * @return const int / const float / const char* / const bool
 **/
const int LuaWrapper::getGlobalInteger(const char* global) {

  lua_getglobal(LUA_, global);
  int integer = lua_tointeger(LUA_, -1);
  lua_pop(LUA_, 1);
  return integer;
}

const float LuaWrapper::getGlobalNumber(const char* global) {

  lua_getglobal(LUA_, global);
  float number = lua_tonumber(LUA_, -1);
  lua_pop(LUA_, 1);
  return number;
}

const char* LuaWrapper::getGlobalString(const char* global) {

  lua_getglobal(LUA_, global);
  char* string = (char*)lua_tostring(LUA_, -1);
  lua_pop(LUA_, 1);
  return string;
}

const bool LuaWrapper::getGlobalBoolean(const char* global) {

  lua_getglobal(LUA_, global);
  bool boolean = lua_toboolean(LUA_, -1);
  lua_pop(LUA_, 1);
  return boolean;
}

/**
 * @brief insert table from lua file to the stack, get a specified field
 *        and pop it
 * @param const char* table, const char* field
 * @return const int / const float / const char* / const bool
 **/
 const int LuaWrapper::getIntegerFromTable(const char* table,
                                           const char* field) {

   lua_getglobal(LUA_, table);
   lua_getfield(LUA_, -1, field);
   int integer = lua_tointeger(LUA_, -1);
   lua_pop(LUA_, 2);
   return integer;
 }

 const float LuaWrapper::getNumberFromTable(const char* table,
                                            const char* field) {

   lua_getglobal(LUA_, table);
   lua_getfield(LUA_, -1, field);
   double number = lua_tonumber(LUA_, -1);
   lua_pop(LUA_, 2);
   return number;
 }

 const char* LuaWrapper::getStringFromTable(const char* table,
                                            const char* field) {

   lua_getglobal(LUA_, table);
   lua_getfield(LUA_, -1, field);
   char* string = (char*)lua_tostring(LUA_, -1);
   lua_pop(LUA_, 2);
   return string;
 }

 const bool LuaWrapper::getBooleanFromTable(const char* table,
                                            const char* field) {

   lua_getglobal(LUA_, table);
   lua_getfield(LUA_, -1, field);
   bool boolean = lua_toboolean(LUA_, -1);
   lua_pop(LUA_, 2);
   return boolean;
 }

/**
* @brief insert table from lua file to the stack and get a specified
*        position by index
* @param const char* table, const short int index
* @return const int / const float / const char* / const bool
**/
const int LuaWrapper::getIntegerFromTableByIndex(const char* table,
                                                 const short int index) {

  lua_checkstack(LUA_, 3);
  lua_getglobal(LUA_, table);
  lua_pushnumber(LUA_, index + 1);
  lua_gettable(LUA_, -2);
  int integer = lua_tointeger(LUA_, -1);

  return integer;
}

const float LuaWrapper::getNumberFromTableByIndex(const char* table,
                                                  const short int index) {

  lua_checkstack(LUA_, 3);
  lua_getglobal(LUA_, table);
  lua_pushnumber(LUA_, index + 1);
  lua_gettable(LUA_, -2);
  float number = lua_tonumber(LUA_, -1);

  return number;
}

const char* LuaWrapper::getStringFromTableByIndex(const char* table,
                                                  const short int index) {

  lua_checkstack(LUA_, 3);
  lua_getglobal(LUA_, table);
  lua_pushnumber(LUA_, index + 1);
  lua_gettable(LUA_, -2);
  char* string = (char*)lua_tostring(LUA_, -1);

  return string;
}

const bool LuaWrapper::getBooleanFromTableByIndex(const char* table,
                                                  const short int index) {

  lua_checkstack(LUA_, 3);
  lua_getglobal(LUA_, table);
  lua_pushnumber(LUA_, index);
  lua_gettable(LUA_, -2);
  bool boolean = lua_toboolean(LUA_, -1);

  return boolean;
}

/** releasers **/
void LuaWrapper::pop(const unsigned short int num_elements) {

  lua_pop(LUA_, num_elements);
}

void LuaWrapper::remove(const short int index) {

  lua_remove(LUA_, index);
}

void LuaWrapper::free() {

  lua_settop(LUA_, 0);
}

/// reset lua
void LuaWrapper::reset() {

  lua_close(LUA_);
  LUA_ = luaL_newstate();
  luaL_openlibs(LUA_);
}

/// close lua
void LuaWrapper::close() {

  lua_settop(LUA_, 0);
  lua_close(LUA_);
}

/// destructor
LuaWrapper::~LuaWrapper() {

  lua_close(LUA_);
  LUA_ = nullptr;
}
