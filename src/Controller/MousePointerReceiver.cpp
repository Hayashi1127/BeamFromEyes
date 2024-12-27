# pragma once

# include <Siv3D.hpp>

# include "MousePointerReceiver.hpp"

namespace BeamFromEyes::Controller
{
	void MousePointerReceiver::Update()
	{
		windowPos = Window::GetPos();
		sceneSize = Scene::Size();
		position = Cursor::ScreenPos() - windowPos - sceneSize / 2;

		isPressed = MouseL.pressed();
	}

	Vec2 MousePointerReceiver::GetPointerPosition()
	{
		return position;
	}

	bool MousePointerReceiver::GetIsPressed()
	{
		return isPressed;
	}

	MousePointerReceiver::MousePointerReceiver()
	{
		Cursor::ClipToWindow(true);
		windowPos = Window::GetPos();
	}

	MousePointerReceiver::~MousePointerReceiver()
	{
		Cursor::ClipToWindow(false);
	}
}
