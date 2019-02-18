#include "stdafx.h"
#include "Application.h"
#include "Renderer.h"
#include "World.h"
#include "Controller.h"
#include "Camera.h"
#include "Shader.h"

#include "MungusMath.h"
#include "MungusUtil.h"

struct Mungus::ActiveBindings {
	typedef std::function<void(Mungus::Application*, int, int, int, int)> keyLambda;
	typedef std::function<void(Mungus::Application*, int, int, int)> mouseLambda;
	typedef std::function<void(Mungus::Application*, double, double)> cursorLambda;

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

	std::stack<mouseLambda>  lmbBindings = std::stack<mouseLambda>();
	std::stack<mouseLambda>  rmbBindings = std::stack<mouseLambda>();

	std::stack<mouseLambda>  leftClickBindings = std::stack<mouseLambda>();
	std::stack<mouseLambda> rightClickBindings = std::stack<mouseLambda>();

	std::stack<cursorLambda> mouseMoveBindings = std::stack<cursorLambda>();
};

//////// client call functions /////////////
void Mungus::Application::setNoClipBindings(void) {
	bindings->aBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
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
	bindings->dBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
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
	bindings->wBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
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
	bindings->sBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
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
	bindings->spaceBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
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
	bindings->xBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
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
	bindings->qBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraStrafingStatus(MPLANAR_REVERSE);
			break;
		case GLFW_RELEASE:
			app->setCameraStrafingStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});
	bindings->eBindings.push([](Mungus::Application* app, int key, int scanCode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			app->setCameraStrafingStatus(MPLANAR_FORWARD);
			break;
		case GLFW_RELEASE:
			app->setCameraStrafingStatus(MSTATIONARY);
			break;
		default:
			break;
		};
	});

	bindings->lmbBindings.push([](Mungus::Application* app, int button, int action, int mods) {

		switch (action) {
		case GLFW_PRESS:
			app->disableCursor();
			app->bindings->mouseMoveBindings.push([](Mungus::Application* app, double xpos, double ypos) {
				app->turnCamera((float)(-(app->getLastMouseLocation().xpos - xpos) * app->getCameraRotationSpeed()) / 360.0f);
				app->pitchCamera((float)(app->getLastMouseLocation().ypos - ypos) * app->getCameraRotationSpeed() / 360.0f);
			});
			break;
		case GLFW_RELEASE: {
			app->bindings->mouseMoveBindings.pop();
			app->enableCursor();
			break;
		}
		default:
			MLOG("unknown mouse action: " << action)
			break;
		}
	});

	bindings->leftClickBindings.push([](Mungus::Application* app, int button, int action, int mods) {
		app->setPrimarySelection(app->findFirstIntersectingWithRay(app->getRayFromCursorLocation(app->getLastMouseLocation())));
	}); 

	bindings->rightClickBindings.push([](Mungus::Application* app, int button, int action, int mods) {
		std::cout << "right clicked\n";
	});
}

const float Mungus::Application::time(void) const{
	return (float)glfwGetTime();
}

const float Mungus::Application::frameTime(void) const {
	return time() - renderer->getLastFrameTime();
}

void inline Mungus::Application::loadActor(const std::string& actorName) {
	world->loadActor(actorName, renderer->getPrograms());
}

void inline Mungus::Application::setBackground(MungusMath::MVec4 color) { renderer->setBackground(color); }

int Mungus::Application::getWindowWidth(void) const {
	return renderer->getWindowWidth();
}

int Mungus::Application::getWindowHeight(void) const {
	return renderer->getWindowHeight();
}

void Mungus::Application::disableCursor(void) const {
	glfwSetInputMode(renderer->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Mungus::Application::enableCursor(void) const {
	glfwSetInputMode(renderer->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

unsigned long Mungus::Application::findFirstIntersectingWithRay(const MungusMath::Line & line) {
	return world->findFirstIntersecting(line);
}

const unsigned long Mungus::Application::frameCount(void) const {
	return world->getFrameCount();
}

const Mungus::CursorLocation Mungus::Application::getLastMouseLocation(void) const {
	return *lastMouseLocation;
}

const float Mungus::Application::getLMBClickTime(void) const {
	return lmbClickTime;
}

const unsigned long Mungus::Application::setEntityPosition(const unsigned long id, float x, float y, float z) {
	return world->setEntityPosition(id, MungusMath::MVec3{ x, y, z });
}

const unsigned long Mungus::Application::scaleEntity(const unsigned long id, float x, float y, float z) {
	return world->scaleEntity(id, MungusMath::MVec3{ x, y, z });
}

const unsigned long Mungus::Application::rotateEntity(const unsigned long id, const MungusMath::MVec3 & axis, float angle) {
	return world->rotateEntity(id, axis, angle);
}

const unsigned long Mungus::Application::turnEntity(const unsigned long id, float angle) {
	return world->turnEntity(id, angle);
}

const unsigned long Mungus::Application::pitchEntity(const unsigned long id, float angle) {
	return world->pitchEntity(id, angle);
}

const unsigned long Mungus::Application::rollEntity(const unsigned long id, float angle) {
	return world->rollEntity(id, angle);
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

MungusMath::Line Mungus::Application::getRayFromCursorLocation(const CursorLocation & cursorLocation) const {
	return world->getRayFromCursorLocation(cursorLocation, (float)getWindowWidth(), (float)getWindowHeight());
}

float Mungus::Application::getNearRenderDistance(void) const {
	return world->getCamera().getNearRenderDistance();
}

float Mungus::Application::getFarRenderDistance(void) const {
	return world->getCamera().getFarRenderDistance();
}

float Mungus::Application::getFieldOfView(void) const {
	return world->getCamera().getFieldOfView();
}

float Mungus::Application::getAspectRatio(void) const {
	return world->getCamera().getAspectRatio();
}

void Mungus::Application::setNearRenderDistance(float nearRenderDistance) {
	world->getCamera().setNearRenderDistance(nearRenderDistance);
}

void Mungus::Application::setFarRenderDistance(float farRenderDistance) {
	world->getCamera().setFarRenderDistance(farRenderDistance);
}

void Mungus::Application::setFieldOfView(float fieldOfView) {
	world->getCamera().setFieldOfView(fieldOfView);
}

void Mungus::Application::setAspectRatio(float aspectRatio) {
	world->getCamera().setAspectRatio(aspectRatio);
}

////////////////////////////////////////////



////// client override functions ////////

void Mungus::Application::startup(void) {
	MLOG("client didn't override Mungus' startup method")
}

void Mungus::Application::mainLoop(void) {
	MLOG("client didn't override mainLoop method")
}

/////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/////////////// client should ignore everything below here ///////////////////
//////////////////////////////////////////////////////////////////////////////


Mungus::Application::Application(void) :
	world(std::make_shared<Mungus::World>(this)),
	renderer(std::make_shared<Mungus::Renderer>(this)),
	bindings(std::make_shared<Mungus::ActiveBindings>()),
	lastMouseLocation(std::make_shared<Mungus::CursorLocation>()),
	lmbClickTime(0),
	rmbClickTime(0),
	primarySelection(0)
{
	glfwSetWindowUserPointer(renderer->getWindow(), this);
	glfwSetKeyCallback(renderer->getWindow(), [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
		(static_cast<Mungus::Application*>(glfwGetWindowUserPointer(window)))->keyCallBack(window, key, scanCode, action, mods);
	});
	glfwSetMouseButtonCallback(renderer->getWindow(), [](GLFWwindow* window, int button, int action, int mods) {
		(static_cast<Mungus::Application*>(glfwGetWindowUserPointer(window)))->mouseCallBack(window, button, action, mods);
	});
	glfwSetCursorPosCallback(renderer->getWindow(), [](GLFWwindow* window, double xpos, double ypos) {
		(static_cast<Mungus::Application*>(glfwGetWindowUserPointer(window)))->cursorCallBack(window, xpos, ypos);
	});

	glfwSetFramebufferSizeCallback(renderer->getWindow(), [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		(static_cast<Mungus::Application*>(glfwGetWindowUserPointer(window)))->setAspectRatio((float)height / (float)width);
	});
}

Mungus::Application::~Application() {}

void Mungus::Application::run(void) {
	while (!glfwWindowShouldClose(renderer->getWindow())) {
		glfwPollEvents();


		mainLoop();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		incrementFrameCount();
		updateCameraPosition();
		updateMouseLocation();
		glfwSetWindowTitle(renderer->getWindow(), (std::to_string((int)(1 / frameTime())) + " - FPS").c_str());
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

inline const unsigned long Mungus::Application::createActor(const std::string & name) {
	return world->createActor(name);
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

void Mungus::Application::updateMouseLocation(void) {
	double xpos, ypos;
	glfwGetCursorPos(renderer->getWindow(), &xpos, &ypos);
	*lastMouseLocation = { (float)xpos, (float)ypos };
}

void Mungus::Application::keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_SPACE:
		if (!bindings->spaceBindings.empty())
			bindings->spaceBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_A:
		if (!bindings->aBindings.empty())
			bindings->aBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_B:
		if (!bindings->bBindings.empty())
			bindings->bBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_C:
		if (!bindings->cBindings.empty())
			bindings->cBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_D:
		if (!bindings->dBindings.empty())
			bindings->dBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_E:
		if (!bindings->eBindings.empty())
			bindings->eBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_F:
		if (!bindings->fBindings.empty())
			bindings->fBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_G:
		if (!bindings->gBindings.empty())
			bindings->gBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_H:
		if (!bindings->hBindings.empty())
			bindings->hBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_I:
		if (!bindings->iBindings.empty())
			bindings->iBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_J:
		if (!bindings->jBindings.empty())
			bindings->jBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_K:
		if (!bindings->kBindings.empty())
			bindings->kBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_L:
		if (!bindings->lBindings.empty())
			bindings->lBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_M:
		if (!bindings->mBindings.empty())
			bindings->mBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_N:
		if (!bindings->nBindings.empty())
			bindings->nBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_O:
		if (!bindings->oBindings.empty())
			bindings->oBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_P:
		if (!bindings->pBindings.empty())
			bindings->pBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_Q:
		if (!bindings->qBindings.empty())
			bindings->qBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_R:
		if (!bindings->rBindings.empty())
			bindings->rBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_S:
		if (!bindings->sBindings.empty())
			bindings->sBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_T:
		if (!bindings->tBindings.empty())
			bindings->tBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_U:
		if (!bindings->uBindings.empty())
			bindings->uBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_V:
		if (!bindings->vBindings.empty())
			bindings->vBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_W:
		if (!bindings->wBindings.empty())
			bindings->wBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_X:
		if (!bindings->xBindings.empty())
			bindings->xBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_Y:
		if (!bindings->yBindings.empty())
			bindings->yBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_Z:
		if (!bindings->zBindings.empty())
			bindings->zBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_0:
		if (!bindings->zeroBindings.empty())
			bindings->zeroBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_1:
		if (!bindings->oneBindings.empty())
			bindings->oneBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_2:
		if (!bindings->twoBindings.empty())
			bindings->twoBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_3:
		if (!bindings->threeBindings.empty())
			bindings->threeBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_4:
		if (!bindings->fourBindings.empty())
			bindings->fourBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_5:
		if (!bindings->fiveBindings.empty())
			bindings->fiveBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_6:
		if (!bindings->sixBindings.empty())
			bindings->sixBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_7:
		if (!bindings->sevenBindings.empty())
			bindings->sevenBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_8:
		if (!bindings->eightBindings.empty())
			bindings->eightBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_9:
		if (!bindings->nineBindings.empty())
			bindings->nineBindings.top()(this, key, scanCode, action, mods);
		break;
	case GLFW_KEY_ESCAPE:
		if (!bindings->escapeBindings.empty())
			bindings->escapeBindings.top()(this, key, scanCode, action, mods);
		break;
	default:
		MLOG("unrecognized key pressed: " << key)
		break;
	}
}

void Mungus::Application::mouseCallBack(GLFWwindow* window, int button, int action, int mods) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_PRESS)
			lmbClickTime = time();

		if (action == GLFW_RELEASE) {
			float lmbHeldDownTime = time() - lmbClickTime;
			if (lmbHeldDownTime < 0.2f) {
				bindings->leftClickBindings.top()(this, button, action, mods);
			}
		}

		if (!bindings->lmbBindings.empty())
			bindings->lmbBindings.top()(this, button, action, mods);
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		if (action == GLFW_PRESS)
			rmbClickTime = time();

		if (action == GLFW_RELEASE) {
			float rmbHeldDownTime = time() - rmbClickTime;
			if (rmbHeldDownTime < 0.2f) {
				bindings->rightClickBindings.top()(this, button, action, mods);
			}
		}

		if (!bindings->rmbBindings.empty())
			bindings->rmbBindings.top()(this, button, action, mods);
		break;
	default:
		MLOG("unrecognized mmouse button pressed: " << button)
		break;
	}
}

void Mungus::Application::cursorCallBack(GLFWwindow * window, double xpos, double ypos) {
	if (!bindings->mouseMoveBindings.empty())
		bindings->mouseMoveBindings.top()(this, xpos, ypos);
}

