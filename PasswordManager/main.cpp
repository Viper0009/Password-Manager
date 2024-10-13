#include "MainHeader.h"
#include "States/States.h"
const float ScreenRatio(1080.f / 1920.f);
const Vector2u BaseScreenSize(1100, 1100 * ScreenRatio);
Vector2u ScreenSize(VideoMode::getFullscreenModes().front().width * 0.55, VideoMode::getFullscreenModes().front().width * 0.55 * ScreenRatio);
Vector2u CurrentScreenSize(ScreenSize);
#ifdef DEBUG
BufferReplacement errorLog;
#endif
int WinMain() {
	prepare();
	RenderWindow window(VideoMode(ScreenSize.x, ScreenSize.y), L"Password Manager");
	unique_ptr<Resource> rsrc = make_unique<Resource>();
	Resource& r = *rsrc;
	States states(r);
	Clock clock;
	double elTime;
	bool resized = false;
	while (window.isOpen()) {
		elTime = clock.restart().asMicroseconds();
		Event event;
		while (window.pollEvent(event)) {
			mainCheck(event, window, resized);
			states.check(event);
		}
		resized = false;

		window.clear(r.colors.background);
		states.update(window, elTime);
		window.display();
	}

	destruct();
	return 0;
}

void prepare() {
	srand(time(0) - 0xcabf);
#ifdef DEBUG
	errorLog.f.open(L"errorLog.txt", fstream::out);
	errorLog.buf = cerr.rdbuf(errorLog.f.rdbuf());
#endif
}
void destruct() {
#ifdef DEBUG
	cerr.rdbuf(errorLog.buf);
	errorLog.f.close();
#endif
}

void mainCheck(Event& event, RenderWindow& window, bool& resized)
{
	switch (event.type) {
	case event.Closed: {
		window.close();
	} break;
	case Event::Resized: {
		if (!resized) {
			resized = true;
			if (abs(int(event.size.width) - int(CurrentScreenSize.x)) > abs(int(event.size.height) - int(CurrentScreenSize.y)))
				window.setSize(Vector2u(event.size.width, event.size.width * ScreenRatio));
			else
				window.setSize(Vector2u(event.size.height / ScreenRatio, event.size.height));
			CurrentScreenSize = window.getSize();
		}
	} break;
	}
}
