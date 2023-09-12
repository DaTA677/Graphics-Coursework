#include "../NCLGL/window.h"
#include "Renderer.h"

int main()	{
	Window w("Make your own project!", 1280, 720, false);

	if(!w.HasInitialised()) {
		return -1;
	}

	//w.LockMouseToWindow(true);
	w.ShowOSPointer(false);
	
	Renderer renderer(w);
	if(!renderer.HasInitialised()) {
		return -1;
	}

	while(w.UpdateWindow()  && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		renderer.UpdateWatertime(w.GetTimer()->GetTotalTimeMSec());
		if(!renderer.GetCamera()->MoveCamera())
		renderer.updateCamera(w.GetTimer()->GetTotalTimeSeconds(), w.GetTimer()->GetTimeDeltaSeconds());
		renderer.UpdateScene(w.GetTimer()->GetTimeDeltaSeconds());
		renderer.RenderScene();
		renderer.SwapBuffers();
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F5)) {
			Shader::ReloadAllShaders();
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_3)) {
			renderer.GetCamera()->ToggleMoveCamera();
		}
	}
	return 0;
}