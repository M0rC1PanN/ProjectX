#include "pch.h"
#include "Events.h"

Events::Events() {
}

Events::~Events() {
}

void Events::OnEvent(SDL_Event* Event) {
	
	if (Event->type == SDL_QUIT) 
	{
		OnExit();
	}
	else
	{
		switch (Event->type)
		{
		case SDL_WINDOWEVENT: {
			switch (Event->window.event) {
				/*case SDL_WINDOWEVENT_ENTER: {
					if (Event->active.gain)    OnMouseFocus();
					else                OnMouseBlur();

					break;
				}
				case SDL_WINDOWEVENT_FOCUS_GAINED: {

					break;
				}*/
				/*case SDL_APPINPUTFOCUS: {
					if (Event->active.gain)    OnInputFocus();
					else                OnInputBlur();

					break;
				}
				case SDL_APPACTIVE: {
					if (Event->active.gain)    OnRestore();
					else                OnMinimize();

					break;
				}*/
				break;
			}
		}
		case SDL_KEYDOWN:
			OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
			break;
		case SDL_KEYUP:
			OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
			break;
		case SDL_MOUSEBUTTONDOWN: {
			switch (Event->button.button) {
			case SDL_BUTTON_LEFT:
				OnLButtonDown(Event->button.x, Event->button.y);
				break;
			case SDL_BUTTON_RIGHT:
				OnRButtonDown(Event->button.x, Event->button.y);
				break;
			case SDL_BUTTON_MIDDLE:
				OnMButtonDown(Event->button.x, Event->button.y);
				break;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			switch (Event->button.button) {
			case SDL_BUTTON_LEFT:
				OnLButtonUp(Event->button.x, Event->button.y);
				break;
			case SDL_BUTTON_RIGHT:
				OnRButtonUp(Event->button.x, Event->button.y);
				break;
			case SDL_BUTTON_MIDDLE:
				OnMButtonUp(Event->button.x, Event->button.y);
				break;
			}
			break;
		}
		case SDL_JOYAXISMOTION: {
			OnJoyAxis(Event->jaxis.which, Event->jaxis.axis, Event->jaxis.value);
			break;
		}

		case SDL_JOYBALLMOTION: {
			OnJoyBall(Event->jball.which, Event->jball.ball, Event->jball.xrel, Event->jball.yrel);
			break;
		}

		case SDL_JOYHATMOTION: {
			OnJoyHat(Event->jhat.which, Event->jhat.hat, Event->jhat.value);
			break;
		}
		case SDL_JOYBUTTONDOWN: {
			OnJoyButtonDown(Event->jbutton.which, Event->jbutton.button);
			break;
		}

		case SDL_JOYBUTTONUP: {
			OnJoyButtonUp(Event->jbutton.which, Event->jbutton.button);
			break;
		}
		case SDL_SYSWMEVENT: {
			break;
		}
		default: {
			OnUser(Event->user.type, Event->user.code, Event->user.data1, Event->user.data2);
			break;
		}
		}
	}
}

void Events::OnInputFocus() {
}

void Events::OnInputBlur() {
}

void Events::OnKeyDown(SDL_Keycode sym, int, int unicode) {
}

void Events::OnKeyUp(SDL_Keycode sym, int, int unicode) {
}

void Events::OnMouseFocus() {
}

void Events::OnMouseBlur() {
}

void Events::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
}

void Events::OnMouseWheel(bool Up, bool Down) {
}

void Events::OnLButtonDown(int mX, int mY) {
}

void Events::OnLButtonUp(int mX, int mY) {
}

void Events::OnRButtonDown(int mX, int mY) {
}

void Events::OnRButtonUp(int mX, int mY) {
}

void Events::OnMButtonDown(int mX, int mY) {
}

void Events::OnMButtonUp(int mX, int mY) {
}

void Events::OnJoyAxis(int which, int axis, int value) {
}

void Events::OnJoyButtonDown(int which, int button) {
}

void Events::OnJoyButtonUp(int which, int button) {
}

void Events::OnJoyHat(int which, int hat, int value) {
}

void Events::OnJoyBall(int which, int ball, int xrel, int yrel) {
}

void Events::OnMinimize() {
}

void Events::OnRestore() {
}

void Events::OnResize(int w, int h) {
}

void Events::OnExpose() {
}

void Events::OnExit() {
}

void Events::OnUser(int type, int code, void* data1, void* data2) {
}