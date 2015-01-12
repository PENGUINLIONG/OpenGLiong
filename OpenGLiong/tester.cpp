#include "LiongGL\Entrance.h"
#include "LiongIO\Entrance.h"
#include "LiongUI\Entrance.h"
#include "LiongSound\Entrance.h" 
#include <iostream>

using namespace LiongStudio::GL;
using namespace LiongStudio::IO;
using namespace LiongStudio::UI;
using namespace LiongStudio::Sound;

int main()
{
	ifstream stream, wavStream;
	MSG message;
	Window window({ 1280, 720 });
	
	if (window.Create())
	{
		Renderer &renderer = window.GetRenderer();
		//WAV wav;
		//wav.ReadData(&wavStream, L"F:\\assets\\live.wav");
		//WaveOut waveOut;
		//waveOut.Write(wav.GetSelected(), wav.GetSelectedLength(), wav.GetPCMFormat());
		
		Texture texture1;
		BMP::Automatic(stream, L"F:\\assets\\test1.bmp", texture1);
		Texture texture2;
		BMP::Automatic(stream, L"F:\\assets\\c.bmp", texture2);
		Texture texture3;
		BMP::Automatic(stream, L"F:\\assets\\button.bmp", texture3);

		Character *c = (Character *)window.GetEntity(window.AppendEntity(new Character(window.GetRenderer())));
		
		c->SwitchDisplayMode(CharacterDisplayMode::Normal);
		c->SwitchFX(CharacterFX::Normal);
		c->BindTexture(&texture2);
		c->SetPosition({ -50, 50 });
		c->SetSize({ 40.0f, 80.0f });
		
		Button *b = (Button *)window.GetEntity(window.AppendEntity(new Button(window.GetRenderer())));

		b->BindTexture(&texture3);
		b->SetPosition({ 0.0f, 30.0f });
		b->SetSize({ 20.0f, 10.0f });
		
		while (true)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
					return 0;
				else
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
			window.DrawTestImage();
	
			renderer.DrawBackGroundImage(texture1.Index);
			c->Render();
			b->Render();

			glFlush();
			window.Flush();
		}
	}
}
