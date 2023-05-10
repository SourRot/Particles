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
		Time dt = clock.restart();
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
	vector<Particle>::iterator iter = m_particles.begin();

	while(iter != m_particles.end())
	{
		Particle& p = *iter;
		if (iter->getTTL() > 0.0)
		{
			iter->update(dtAsSeconds);
			iter++;
		}
		else 
		{
			iter = m_particles.erase(iter);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));
	}
	m_Window.display();
}
