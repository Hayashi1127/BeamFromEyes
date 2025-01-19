# pragma once

# include <thread>
# include <Siv3D.hpp>

# include "EyetrackingReceiver.hpp"
# include "ExpressionApp.hpp"
// # include "nvAR.h"

namespace BeamFromEyes::Controller
{
	void EyetrackingReceiver::Update()
	{
		windowPos = Window::GetPos();
		sceneSize = Scene::Size();
		position = Cursor::ScreenPos(); //- windowPos - sceneSize / 2;

		isPressed = MouseL.pressed();

		NvCV_Status err = app.run();
		if (err != NVCV_SUCCESS)
		{
			ReceiveError(err);
		}
		else
		{
			if (hasCalibData)
			{

			}
			for (int i = 0; i < eyeExpressions.size(); i++)
			{
				eyeExpressions.at(i) = app._expressions[i + 12];
			}
		}


	}

	Vec2 EyetrackingReceiver::GetPointerPosition() const
	{
		return position;
	}

	bool EyetrackingReceiver::GetIsPressed() const
	{
		return isPressed;
	}

	EyetrackingReceiver::EyetrackingReceiver()
	{
		windowPos = Window::GetPos();

		// Nvidia AR SDK初期化
		// app初期化
		NvCV_Status err = app.init();
		if (err != NVCV_SUCCESS)
		{
			ReceiveError(err);
		}

		eyeExpressions = Array<float>(8);
		calibExpressions = Array<float>(8);
	}

	EyetrackingReceiver::~EyetrackingReceiver()
	{
	}

	void EyetrackingReceiver::ReceiveError(NvCV_Status error)
	{
		Print << error;
	}
}
