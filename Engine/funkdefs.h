#pragma once

#include <functional>

#include "Cmn.h"
#include "LuaEngine.h"
#include "oolua/oolua_function.h"

namespace talga
{
	class GameObject;
	struct LuaCollisionData;
	typedef std::function<void(GameObject*)> StagedStdFunction;
	typedef std::function<void(GameObject*, I32 ms)> UpdateStdFunction;
	typedef std::function<void(GameObject*)> UnstagedStdFunction;
	typedef std::function<void(GameObject*, I32)> KeyStdCallback;
	typedef std::function <void(GameObject*, const LuaCollisionData*)> CollisionStdCallback;
	
	class StagedFunc;

	typedef StagedFunc UnstagedFunc;
	typedef StagedFunc InitFunc;
	typedef StagedFunc DestroyFunc;

	enum class TALGA_FUNC_TYPE { NONE, LUA, STD };

	class UpdateFunc
	{
	public:
		UpdateFunc() : isLua{ TALGA_FUNC_TYPE::NONE }, luaFunc{ talga::LuaEngine::instance()->getState() }, ref{ } {}
		~UpdateFunc() {}

		void operator=(OOLUA::Lua_func_ref tempRef)
		{
			isLua = TALGA_FUNC_TYPE::LUA;
			this->ref = tempRef;
		}

		void operator=(UpdateStdFunction func)
		{
			isLua = TALGA_FUNC_TYPE::STD;
			stdFunc = func;
		}

		operator bool()
		{
			return !(isLua == TALGA_FUNC_TYPE::NONE);
		}

		void operator()(GameObject* obj, I32 ms);

	private:
		TALGA_FUNC_TYPE isLua;
		OOLUA::Lua_func_ref ref;
		OOLUA::Lua_function luaFunc;
		UpdateStdFunction stdFunc;
	};

	class StagedFunc
	{
	public:
		StagedFunc() : isLua{ TALGA_FUNC_TYPE::NONE }, luaFunc{ talga::LuaEngine::instance()->getState() }, ref{  } {}
		~StagedFunc() {}

		void operator=(OOLUA::Lua_func_ref tempRef)
		{
			isLua = TALGA_FUNC_TYPE::LUA;
			this->ref = tempRef;
		}

		void operator=(StagedStdFunction func)
		{
			isLua = TALGA_FUNC_TYPE::STD;
			stdFunc = func;
		}

		operator bool()
		{
			return !(isLua == TALGA_FUNC_TYPE::NONE);
		}

		void operator()(GameObject* obj);

	private:
		TALGA_FUNC_TYPE isLua;
		OOLUA::Lua_func_ref ref;
		OOLUA::Lua_function luaFunc;
		StagedStdFunction stdFunc;
	};
	

	class KeyCallbackFunc
	{
	public:
		KeyCallbackFunc() : isLua{ TALGA_FUNC_TYPE::NONE }, luaFunc{ talga::LuaEngine::instance()->getState() }, ref{} {}
		KeyCallbackFunc(const KeyCallbackFunc& cpy) : isLua{ cpy.isLua }, ref{ cpy.ref }, luaFunc(cpy.luaFunc), stdFunc{ cpy.stdFunc } {}
		~KeyCallbackFunc() {}

		void operator=(OOLUA::Lua_func_ref tempRef)
		{
			isLua = TALGA_FUNC_TYPE::LUA;
			this->ref = tempRef;
		}

		void operator=(KeyStdCallback func)
		{
			isLua = TALGA_FUNC_TYPE::STD;
			stdFunc = func;
		}

		operator bool()
		{
			return !(isLua == TALGA_FUNC_TYPE::NONE);
		}

		void operator()(GameObject* obj, I32 action);

	private:
		TALGA_FUNC_TYPE isLua;
		OOLUA::Lua_func_ref ref;
		OOLUA::Lua_function luaFunc;
		KeyStdCallback stdFunc;
	};

	class CollisionCallbackFunc
	{
	public:
		CollisionCallbackFunc() : isLua{ TALGA_FUNC_TYPE::NONE }, luaFunc{ talga::LuaEngine::instance()->getState() }, ref{} {}
		CollisionCallbackFunc(const CollisionCallbackFunc& cpy) : isLua{ cpy.isLua }, ref{ cpy.ref }, luaFunc(cpy.luaFunc), stdFunc{ cpy.stdFunc } {}
		~CollisionCallbackFunc() {}

		void operator=(OOLUA::Lua_func_ref tempRef)
		{
			isLua = TALGA_FUNC_TYPE::LUA;
			this->ref = tempRef;
		}

		void operator=(CollisionStdCallback func)
		{
			isLua = TALGA_FUNC_TYPE::STD;
			stdFunc = func;
		}

		operator bool()
		{
			return !(isLua == TALGA_FUNC_TYPE::NONE);
		}

		void operator()(GameObject* obj, const LuaCollisionData* data);

	private:
		TALGA_FUNC_TYPE isLua;
		OOLUA::Lua_func_ref ref;
		OOLUA::Lua_function luaFunc;
		CollisionStdCallback stdFunc;
	};

}