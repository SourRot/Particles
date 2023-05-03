#include "Engine.h"

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particles");
}
void Engine::run()
{
	Clock clock;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		clock.restart();
		Time dt = clock.getElapsedTime();
		input();
		update(dt.asSeconds());
		draw();
	}
}

void Engine::input()
{
	srand(time(0));
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_Window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				for (int i = 0; i < 5; i++)
				{
					Particle newPart(m_Window, rand() % (50 - 25 + 1) + 25, Mouse::getPosition(m_Window));
					m_particles.push_back(newPart);
				}
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{

}