#pragma once

#include "oolua/oolua_dsl.h"
#include "oolua/proxy_tags.h"

#include <string>

#include "Game.h"
#include "Camera.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "Sprite.h"
#include "AssetManager.h"
#include "Texture.h"
#include "IRenderable.h"
#include "PhysicsComponent.h"
#include "AnimSet.h"
namespace OOLUA
{
	typedef talga::Game Game;
	typedef talga::Camera Camera;
	typedef talga::Rectangle Rectangle;
	typedef talga::GameObject GameObject;
	typedef talga::Sprite Sprite;
	typedef talga::AnimSprite AnimSprite;
	typedef talga::Texture Texture;
	typedef talga::AnimationSet AnimationSet;
	typedef talga::AssetManager AssetManager;
	typedef talga::IRenderable IRenderable;
	typedef talga::PhysicsComponent PhysicsComponent;
	typedef talga::RectCollider RectCollider;

	typedef const Texture* cpTex;
	typedef const AnimationSet* cpAnimSet;
}

//Texture
OOLUA_PROXY(Texture)
OOLUA_TAGS(OOLUA::No_public_constructors)
OOLUA_PROXY_END

//IRenderable
OOLUA_PROXY(IRenderable)
OOLUA_TAGS(OOLUA::Abstract)
OOLUA_PROXY_END

//AnimSet
OOLUA_PROXY(AnimationSet)
OOLUA_TAGS(OOLUA::No_public_constructors)
OOLUA_PROXY_END

//PhysComp
OOLUA_PROXY(PhysicsComponent)
OOLUA_TAGS(OOLUA::Abstract)
OOLUA_MFUNC(setFriction)
OOLUA_MFUNC(setMoment)
OOLUA_MFUNC(setMass)
OOLUA_MFUNC(applyForceX)
OOLUA_MFUNC(applyForceY)
OOLUA_MFUNC(applyImpulseX)
OOLUA_MFUNC(applyImpulseY)
OOLUA_MFUNC(setX)
OOLUA_MFUNC(setY)
OOLUA_MFUNC_CONST(getFriction)
OOLUA_MFUNC_CONST(getMoment)
OOLUA_MFUNC_CONST(getMass)
OOLUA_MFUNC_CONST(getX)
OOLUA_MFUNC_CONST(getY)
OOLUA_MFUNC_CONST(getVx)
OOLUA_MFUNC_CONST(getVy)
OOLUA_MFUNC_CONST(getOrientation)
OOLUA_PROXY_END

//RectCollider
OOLUA_PROXY(RectCollider, PhysicsComponent)
OOLUA_TAGS(OOLUA::No_default_constructor)
OOLUA_CTORS(
OOLUA_CTOR(int, int)
OOLUA_CTOR(int, int, int)
OOLUA_CTOR(int, int, int, int)
)
OOLUA_PROXY_END

//AssetManager
OOLUA_PROXY(AssetManager)
	OOLUA_TAGS(OOLUA::No_public_constructors)
	OOLUA_MFUNC_CONST(GetTexture)
	OOLUA_MFUNC(AddTexture)
	OOLUA_MEM_FUNC(cpAnimSet, AddAnimationSet, std::string, std::string, OOLUA::Lua_table_ref)
OOLUA_PROXY_END

//Rectangle
OOLUA_PROXY(Rectangle)
	OOLUA_TAGS(OOLUA::No_public_constructors)
	OOLUA_MFUNC_CONST(getX)
	OOLUA_MFUNC_CONST(getY)
	OOLUA_MFUNC_CONST(getZ)
	OOLUA_MFUNC(setX)
	OOLUA_MFUNC(setY)
	OOLUA_MFUNC(setZ)
OOLUA_PROXY_END

//Sprite
OOLUA_PROXY(Sprite, IRenderable)
OOLUA_TAGS(OOLUA::No_default_constructor)
OOLUA_CTORS(
OOLUA_CTOR(cpTex)
)
OOLUA_PROXY_END

//AnimSprite
OOLUA_PROXY(AnimSprite, IRenderable)
OOLUA_TAGS(OOLUA::No_default_constructor)
OOLUA_CTORS(
OOLUA_CTOR(cpAnimSet)
)
OOLUA_PROXY_END

//GameObject
OOLUA_PROXY(GameObject)
OOLUA_TAGS(OOLUA::No_default_constructor)
	OOLUA_CTORS(
	OOLUA_CTOR(IRenderable*, PhysicsComponent*)
	OOLUA_CTOR(const std::string&)
	)
	OOLUA_MEM_FUNC(void, addKeyCallback, std::string, Lua_func_ref)
	OOLUA_MEM_FUNC(void, addCollisionCallback, int, Lua_func_ref)
	OOLUA_MEM_FUNC(void, setCollisionType, int)
	OOLUA_MFUNC(setCollider)
	OOLUA_MFUNC(getCollider)
	OOLUA_MFUNC(setRenderable)
	OOLUA_MFUNC(playAnimation)
OOLUA_PROXY_END

//Camera
OOLUA_PROXY(Camera)
	OOLUA_TAGS(OOLUA::No_public_constructors)
	OOLUA_MEM_FUNC(Rectangle&, box)
OOLUA_PROXY_END

//Game
OOLUA_PROXY(Game)
OOLUA_TAGS(OOLUA::No_public_constructors)
OOLUA_MEM_FUNC(Camera&, camera)
OOLUA_MEM_FUNC(AssetManager*, manager)
OOLUA_MFUNC(addObj)
OOLUA_MEM_FUNC_RENAME(printToLuaPromptStr, void, printToLuaPrompt, const std::string&)
OOLUA_MEM_FUNC_RENAME(printToLuaPromptFl, void, printToLuaPrompt, float)
OOLUA_PROXY_END

void LUA_REGISTER_TYPES();