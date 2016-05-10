/**
 *
 * @brief Lua Wrapper
 * @author Toni Marquez
 * @fixes register function
 *
 **/

#ifndef __LUAWRAPPER_H__
#define __LUAWRAPPER_H__ 1

#include <stdio.h>
#include <stdlib.h>

#include "lua.hpp"

class LuaWrapper {

  public:

    /// constructor
    LuaWrapper();

    /// destructor
    ~LuaWrapper();

    /// init values
    void init(const char* path);
    /**
     *
     *  this is like the lua stack works (LIFO):
     *
     *       |   |
     *     3 | - | -1
     *     2 | - | -2
     *     1 | - | -3
     *       |___|
     *
     **/

    /**
     * @brief register a function / call the function
     * @param const char* lua_function, lua_CFunction cfunction / none
     * @return void / void
     **/
    void registerFunction(const char* lua_function, lua_CFunction cfunction);
    void callFunction();
    /*
    // use this function for callback
    int LuaUpdate(lua_State* LUA){{

      return 0;
    }
    */

    /**
     * @brief insert global from lua file to the stack and pop it
     * @param const char* global
     * @return const int / const float / const char* / const bool
     **/
    const int getGlobalInteger(const char* global);
    const float getGlobalNumber(const char* global);
    const char* getGlobalString(const char* global);
    const bool getGlobalBoolean(const char* global);

    /**
     * @brief insert table from lua file to the stack, get a specified field
     *        and pop it
     * @param const char* table, const char* field
     * @return const int / const float / const char* / const bool
     **/
     const int getIntegerFromTable(const char* table, const char* field);
     const float getNumberFromTable(const char* table, const char* field);
     const char* getStringFromTable(const char* table, const char* field);
     const bool getBooleanFromTable(const char* table, const char* field);

     /**
     * @brief insert table from lua file to the stack and get a specified
     *        position by index
     * @param const char* table, const short int index
     * @return const int / const float / const char* / const bool
     **/
    const int getIntegerFromTableByIndex(const char* table,
                                         const short int index);
    const float getNumberFromTableByIndex(const char* table,
                                          const short int index);
    const char* getStringFromTableByIndex(const char* table,
                                          const short int index);
    const bool getBooleanFromTableByIndex(const char* table,
                                          const short int index);

    /** releasers **/
    void pop(const unsigned short int num_elements);
    void remove(const short int index);
    void free();

    /// reset lua
    void reset();

    /// close lua
    void close();

  private:

    /// copy constructor
    LuaWrapper(const LuaWrapper& copy);
    LuaWrapper operator=(const LuaWrapper& copy);

    /// private vars
    lua_State* LUA_;
};

#endif
