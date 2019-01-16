#include "stdafx.h"
#include "Application.h"
#include "Renderer.h"
#include "World.h"
#include "Controller.h"
#include "Camera.h"

#include "MungusMath.h"
#include "MungusUtil.h"

struct Mungus::KeyFunctions {
	typedef std::function<void(Mungus::Application*, GLFWwindow*, int, int, int, int)> keyLambda;

	std::stack<keyLambda>      aBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      bBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      cBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      dBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      eBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      fBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      gBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      hBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      iBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      jBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      kBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      lBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      mBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      nBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      oBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      pBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      qBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      rBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      sBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      tBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      uBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      vBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      wBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      xBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      yBindings = std::stack<keyLambda>();
	std::stack<keyLambda>      zBindings = std::stack<keyLambda>();
	std::stack<keyLambda>   zeroBindings = std::stack<keyLambda>();
	std::stack<keyLambda>    oneBindings = std::stack<keyLambda>();
	std::stack<keyLambda>    twoBindings = std::stack<keyLambda>();
	std::stack<keyLambda>  threeBindings = std::stack<keyLambda>();
	std::stack<keyLambda>   fourBindings = std::stack<keyLambda>();
	std::stack<keyLambda>   fiveBindings = std::stack<keyLambda>();
	std::stack<keyLambda>    sixBindings = std::stack<keyLambda>();
	std::stack<keyLambda>  sevenBindings = std::stack<keyLambda>();
	std::stack<keyLambda>  eightBindings = std::stack<keyLambda>();
	std::stack<keyLambda>   nineBindings = std::stack<keyLambda>();
	std::stack<keyLambda> escapeBindings = std::stack<keyLambda>();
	std::stack<keyLambda>  spaceBindings = std::stack<keyLambda>();
};

//////// client call functions /////////////
void Mungus::Application::setDefaultBindings(void) {
	bindings->aBindings.push([](Mungus::Application* app, GLFWwindow* window, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraTurningStatus(MPLANAR_REVERSE);
			break;
		case GLFW_RELEASE:
			app->setCameraTurningStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});
	bindings->dBindings.push([](Mungus::Application* app, GLFWwindow* window, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraTurningStatus(MPLANAR_FORWARD);
			break;
		case GLFW_RELEASE:
			app->setCameraTurningStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});
	bindings->wBindings.push([](Mungus::Application* app, GLFWwindow* window, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraAdvancingStatus(MPLANAR_FORWARD);
			break;
		case GLFW_RELEASE:
			app->setCameraAdvancingStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});
	bindings->sBindings.push([](Mungus::Application* app, GLFWwindow* window, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraAdvancingStatus(MPLANAR_REVERSE);
			break;
		case GLFW_RELEASE:
			app->setCameraAdvancingStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});
	bindings->spaceBindings.push([](Mungus::Application* app, GLFWwindow* window, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraAscendingStatus(MPLANAR_FORWARD);
			break;
		case GLFW_RELEASE:
			app->setCameraAscendingStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});
	bindings->xBindings.push([](Mungus::Application* app, GLFWwindow* window, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraAscendingStatus(MPLANAR_REVERSE);
			break;
		case GLFW_RELEASE:
			app->setCameraAscendingStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});
}

const float Mungus::Application::time(void) const{
	return (float)glfwGetTime();
}

const float Mungus::Application::frameTime(void) const {
	return time() - renderer->getLastFrameTime();
}

void inline Mungus::Application::loadAsset(const std::string& assetPath) {
	world->loadAsset(assetPath, renderer->getVertexShaders(), renderer->getFragmentShaders());
}

void inline Mungus::Application::setBackground(MungusMath::MVec4 color) { renderer->setBackground(color); }

const unsigned long Mungus::Application::frameCount(void) const {
	return world->getFrameCount();
}

const unsigned long Mungus::Application::setEntityPosition(const unsigned long id, float x, float y, float z) {
	return world->setEntityPosition(id, x, y, z);
}

const unsigned long Mungus::Application::scaleEntity(const unsigned long id, float x, float y, float z) {
	return world->scaleEntity(id, x, y, z);
}

const unsigned long Mungus::Application::rotateEntity(const unsigned long id, const MungusMath::MVec3 & axis, float angle) {
	return world->rotateEntity(id, axis, angle);
}

const MungusMath::MVec3 Mungus::Application::getCameraPosition(void) const {
	return world->getCameraPosition();
}

void Mungus::Application::setCameraPosition(float x, float y, float z) {
	world->setCameraPosition(x, y, z);
}

void Mungus::Application::moveCamera(const MungusMath::MVec3& moveBy) {
	world->moveCamera(moveBy);
}

const MungusMath::MVec3 Mungus::Application::getCameraForward(void) const {
	return world->getCameraForward();
}

const MungusMath::MVec3 Mungus::Application::getCameraUp(void) const {
	return world->getCameraUp();
}

const MungusMath::MVec3 Mungus::Application::getCameraRight(void) const {
	return world->getCameraRight();
}

const MungusMath::MVec3 Mungus::Application::getCameraPlanarForward(void) const {
	return world->getCameraPlanarForward();
}

const MungusMath::MVec3 Mungus::Application::getCameraPlanarUp(void) const {
	return world->getCameraPlanarUp();
}

const MungusMath::MVec3 Mungus::Application::getCameraPlanarRight(void) const {
	return world->getCameraPlanarRight();
}

void Mungus::Application::rotateCamera(const MungusMath::MVec3& axis, float theta) {
	world->rotateCamera(axis, theta);
}

void Mungus::Application::turnCamera(float angle) {
	world->turnCamera(angle);
}

void Mungus::Application::pitchCamera(float angle) {
	world->pitchCamera(angle);
}

void Mungus::Application::rollCamera(float angle) {
	world->rollCamera(angle);
}

inline const float Mungus::Application::getCameraRotationSpeed(void) const {
	return world->getCameraRotationSpeed();
}

inline void Mungus::Application::setCameraRotationSpeed(float speed) {
	world->setCameraRotationSpeed(speed);
}

inline const float Mungus::Application::getCameraMovementSpeed(void) const {
	return world->getCameraMovementSpeed();
}

inline void Mungus::Application::setCameraMovementSpeed(float speed) {
	world->setCameraMovementSpeed(speed);
}

void Mungus::Application::setCameraStrafingStatus(int setting) {
	world->setCameraStrafingStatus(setting);
}

void Mungus::Application::setCameraAscendingStatus(int setting) {
	world->setCameraAscendingStatus(setting);
}

void Mungus::Application::setCameraAdvancingStatus(int setting) {
	world->setCameraAdvancingStatus(setting);
}

void Mungus::Application::setCameraTurningStatus(int setting) {
	world->setCameraTurningStatus(setting);
}

void Mungus::Application::setCameraPitchingStatus(int setting) {
	world->setCameraPitchingStatus(setting);
}

void Mungus::Application::setCameraRollingStatus(int setting) {
	world->setCameraPitchingStatus(setting);
}

////////////////////////////////////////////



////// client override functions ////////

void Mungus::Application::startup(void) {
	MLOG("client didn't override Mungus' startup method")
}

void Mungus::Application::mainLoop(void) {
	MLOG("client didn't override run method")
}

/////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/////////////// client should ignore everything below here ///////////////////
//////////////////////////////////////////////////////////////////////////////


Mungus::Application::Application(void) :
	world(std::make_shared<Mungus::World>(this)),
	renderer(std::make_shared<Mungus::Renderer>(this)),
	bindings(std::make_shared<Mungus::KeyFunctions>())
{
	glfwSetWindowUserPointer(renderer->getWindow(), this);
	glfwSetKeyCallback(renderer->getWindow(), [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
		(static_cast<Mungus::Application*>(glfwGetWindowUserPointer(window)))->keyCallBack(window, key, scanCode, action, mods);
	});
}

Mungus::Application::~Application() {

}

void Mungus::Application::run(void) {
	while (!glfwWindowShouldClose(renderer->getWindow())) {
		glfwPollEvents();
		mainLoop();
		incrementFrameCount();
		updateCameraPosition();
		renderer->setLastFrameTime((float)glfwGetTime());
		renderActors();
		glfwSwapBuffers(renderer->getWindow());
	}
	glfwDestroyWindow(renderer->getWindow());
	glfwTerminate();
}

void inline Mungus::Application::incrementFrameCount(void) {
	world->incrementFrameCount();
}

inline const unsigned long Mungus::Application::createEntity(const std::string & name) {
	return world->createEntity(name);
}

void Mungus::Application::renderActors(void) {
	renderer->renderActors(world->getActors(), world->getCamera());
}

void Mungus::Application::updateCameraPosition(void) {
	Camera camera = world->getCamera();

	switch (camera.advancing) {
	case MSTATIONARY:
		break;
	case MCAMERA_FORWARD:
		moveCamera(getCameraForward() * frameTime() * getCameraMovementSpeed());
		break;
	case MCAMERA_REVERSE:
		moveCamera(getCameraForward() * -frameTime() * getCameraMovementSpeed());
		break;
	case MPLANAR_FORWARD:
		moveCamera(getCameraPlanarForward() * frameTime() * getCameraMovementSpeed());
		break;
	case MPLANAR_REVERSE:
		moveCamera(getCameraPlanarForward() * -frameTime() * getCameraMovementSpeed());
		break;
	default:
		MLOG("unknown camera advancing state: " << camera.advancing)
		break;
	}

	switch (camera.ascending) {
	case MSTATIONARY:
		break;
	case MCAMERA_FORWARD:
		moveCamera(getCameraUp() * frameTime() * getCameraMovementSpeed());
		break;
	case MCAMERA_REVERSE:
		moveCamera(getCameraUp() * -frameTime() * getCameraMovementSpeed());
		break;
	case MPLANAR_FORWARD:
		moveCamera(getCameraPlanarUp() * frameTime() * getCameraMovementSpeed());
		break;
	case MPLANAR_REVERSE:
		moveCamera(getCameraPlanarUp() * -frameTime() * getCameraMovementSpeed());
		break;
	default:
		MLOG("unknown camera ascending state: " << camera.ascending)
		break;
	}

	switch (camera.strafing) {
	case MSTATIONARY:
		break;
	case MCAMERA_FORWARD:
		moveCamera(getCameraRight() * frameTime() * getCameraMovementSpeed());
		break;
	case MCAMERA_REVERSE:
		moveCamera(getCameraRight() * -frameTime() * getCameraMovementSpeed());
		break;
	case MPLANAR_FORWARD:
		moveCamera(getCameraPlanarRight() * frameTime() * getCameraMovementSpeed());
		break;
	case MPLANAR_REVERSE:
		moveCamera(getCameraPlanarRight() * -frameTime() * getCameraMovementSpeed());
		break;
	default:
		MLOG("unknown camera strafing state: " << camera.strafing)
		break;
	}

	switch (camera.turning) {
	case MSTATIONARY:
		break;
	case MCAMERA_FORWARD:
		rotateCamera(camera.up(), frameTime() * getCameraRotationSpeed());
		break;
	case MCAMERA_REVERSE:
		rotateCamera(camera.up(), -frameTime() * getCameraRotationSpeed());
		break;
	case MPLANAR_FORWARD:
		turnCamera(frameTime() * getCameraRotationSpeed());
		break;
	case MPLANAR_REVERSE:
		turnCamera(-frameTime() * getCameraRotationSpeed());
		break;
	default:
		MLOG("unknown camera turning state: " << camera.turning)
		break;
	}

	switch (camera.pitching) {
	case MSTATIONARY:
		break;
	case MCAMERA_FORWARD:
		rotateCamera(camera.right(), frameTime() * getCameraRotationSpeed());
		break;
	case MCAMERA_REVERSE:
		rotateCamera(camera.right(), -frameTime() * getCameraRotationSpeed());
		break;
	case MPLANAR_FORWARD:
		pitchCamera(frameTime() * getCameraRotationSpeed());
		break;
	case MPLANAR_REVERSE:
		pitchCamera(-frameTime() * getCameraRotationSpeed());
		break;
	default:
		MLOG("unknown camera pitching state: " << camera.pitching)
		break;
	}

	switch (camera.rolling) {
	case MSTATIONARY:
		break;
	case MCAMERA_FORWARD:
		rotateCamera(camera.forward(), frameTime() * getCameraRotationSpeed());
		break;
	case MCAMERA_REVERSE:
		rotateCamera(camera.forward(), -frameTime() * getCameraRotationSpeed());
		break;
	case MPLANAR_FORWARD:
		rollCamera(frameTime() * getCameraRotationSpeed());
		break;
	case MPLANAR_REVERSE:
		rollCamera(-frameTime() * getCameraRotationSpeed());
		break;
	default:
		MLOG("unknown camera rolling state: " << camera.rolling)
		break;
	}
}

void Mungus::Application::keyCallBack(GLFWwindow * window, int key, int scanCode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_SPACE:
		if (!bindings->spaceBindings.empty())
			bindings->spaceBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_A:
		if (!bindings->aBindings.empty())
			bindings->aBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_B:
		if (!bindings->bBindings.empty())
			bindings->bBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_C:
		if (!bindings->cBindings.empty())
			bindings->cBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_D:
		if (!bindings->dBindings.empty())
			bindings->dBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_E:
		if (!bindings->eBindings.empty())
			bindings->eBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_F:
		if (!bindings->fBindings.empty())
			bindings->fBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_G:
		if (!bindings->gBindings.empty())
			bindings->gBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_H:
		if (!bindings->hBindings.empty())
			bindings->hBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_I:
		if (!bindings->iBindings.empty())
			bindings->iBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_J:
		if (!bindings->jBindings.empty())
			bindings->jBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_K:
		if (!bindings->kBindings.empty())
			bindings->kBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_L:
		if (!bindings->lBindings.empty())
			bindings->lBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_M:
		if (!bindings->mBindings.empty())
			bindings->mBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_N:
		if (!bindings->nBindings.empty())
			bindings->nBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_O:
		if (!bindings->oBindings.empty())
			bindings->oBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_P:
		if (!bindings->pBindings.empty())
			bindings->pBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_Q:
		if (!bindings->qBindings.empty())
			bindings->qBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_R:
		if (!bindings->rBindings.empty())
			bindings->rBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_S:
		if (!bindings->sBindings.empty())
			bindings->sBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_T:
		if (!bindings->tBindings.empty())
			bindings->tBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_U:
		if (!bindings->uBindings.empty())
			bindings->uBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_V:
		if (!bindings->vBindings.empty())
			bindings->vBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_W:
		if (!bindings->wBindings.empty())
			bindings->wBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_X:
		if (!bindings->xBindings.empty())
			bindings->xBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_Y:
		if (!bindings->yBindings.empty())
			bindings->yBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_Z:
		if (!bindings->zBindings.empty())
			bindings->zBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_0:
		if (!bindings->zeroBindings.empty())
			bindings->zeroBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_1:
		if (!bindings->oneBindings.empty())
			bindings->oneBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_2:
		if (!bindings->twoBindings.empty())
			bindings->twoBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_3:
		if (!bindings->threeBindings.empty())
			bindings->threeBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_4:
		if (!bindings->fourBindings.empty())
			bindings->fourBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_5:
		if (!bindings->fiveBindings.empty())
			bindings->fiveBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_6:
		if (!bindings->sixBindings.empty())
			bindings->sixBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_7:
		if (!bindings->sevenBindings.empty())
			bindings->sevenBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_8:
		if (!bindings->eightBindings.empty())
			bindings->eightBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_9:
		if (!bindings->nineBindings.empty())
			bindings->nineBindings.top()(this, window, key, scanCode, action, mods);
		break;
	case GLFW_KEY_ESCAPE:
		if (!bindings->escapeBindings.empty())
			bindings->escapeBindings.top()(this, window, key, scanCode, action, mods);
		break;
	default:
		MLOG("unrecognized key pressed: " << key)
	}
}
