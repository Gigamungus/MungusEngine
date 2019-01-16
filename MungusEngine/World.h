#pragma once
#include "stdafx.h"


namespace Mungus {
	class Application;
	class Actor;
	class Asset;
	class Camera;

	class MUNGUS World {
	private:
		const Application* owner;
		unsigned long frameCount;
		unsigned long actorCount;
		std::unordered_map<std::string, std::shared_ptr<Mungus::Asset>> assets;
		std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> actors;
		std::shared_ptr<Camera> camera;

	public:
		World(const Application* owner);
		virtual ~World() {};

		void inline loadAsset(	const std::string& title,
								const std::unordered_map<std::string, const unsigned int>& vertexShaders,
								const std::unordered_map<std::string, const unsigned int>& fragmentShaders);

		const Camera inline getCamera(void) const;
		const inline unsigned long getFrameCount(void) const { return frameCount; }
		void inline incrementFrameCount(void) { frameCount++; }
		const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> inline getActors(void) const { return actors; }
		const unsigned long createEntity(const std::string& name);
		const unsigned long setEntityPosition(const unsigned long id, float x, float y, float z);
		const unsigned long scaleEntity(const unsigned long id, float x, float y, float z);
		const unsigned long rotateEntity(const unsigned long id, const MungusMath::MVec3& axis, float angle);

		const MungusMath::MVec3 getCameraPosition(void) const;
		void setCameraPosition(float x, float y, float z);
		void moveCamera(const MungusMath::MVec3& moveBy);

		const MungusMath::MVec3 getCameraForward(void) const;
		const MungusMath::MVec3 getCameraUp(void) const;
		const MungusMath::MVec3 getCameraRight(void) const;
		const MungusMath::MVec3 getCameraPlanarForward(void) const;
		const MungusMath::MVec3 getCameraPlanarUp(void) const;
		const MungusMath::MVec3 getCameraPlanarRight(void) const;

		void setCameraStrafingStatus(int setting);
		void setCameraAscendingStatus(int setting);
		void setCameraAdvancingStatus(int setting);
		void setCameraTurningStatus(int setting);
		void setCameraPitchingStatus(int setting);
		void setCameraRollingStatus(int setting);

		float getCameraRotationSpeed() const;
		void setCameraRotationSpeed(float speed);
		float getCameraMovementSpeed() const;
		void setCameraMovementSpeed(float speed);

		void rotateCamera(const MungusMath::MVec3& axis, float theta);
		void turnCamera(float angle);
		void pitchCamera(float angle);
		void rollCamera(float angle);
	};


}