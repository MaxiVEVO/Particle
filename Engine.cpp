#include "Engine.h"


// The Engine constructor
Engine::Engine() 
{
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;
	VideoMode vm(pixelWidth, pixelHeight);
	m_Window.create(vm, "Particles", Style::Default);
}

// Run will call all the private functions
void Engine::run()
{
	Clock clock;
	float dt;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;
	while (m_Window.isOpen())
	{
		dt = clock.restart().asSeconds();
		input();
		update(dt);
		draw();
	}
}


// Private Functions
void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape)) m_Window.close();
		if (event.type == sf::Event::Closed) m_Window.close();
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				for (int i = 0; i < 5; i++)
				{
					Vector2i clickPos(event.mouseButton.x, event.mouseButton.y);
					Particle particle(m_Window, rand() % 26 + 25, clickPos);
					m_particles.push_back(particle);
				}
			}
		}
	}
}
void Engine::update(float dtAsSeconds)
{
	for(auto p = m_particles.begin(); p != m_particles.end();)
	{
		if (p->getTTL() > 0.0)
		{
			p->update(dtAsSeconds);
			p++;
		}
		else
		{
			p = m_particles.erase(p);
		}
	}
}
void Engine::draw()
{
	m_Window.clear();
	for (const Particle&p : m_particles)
	{
		m_Window.draw(p);
	}
	m_Window.display();
}

