#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;


class Game
{
	private:
		Texture twood;
		
		void menu_bg()
		{
			RectangleShape rect(Vector2f(300, 150));
			rect.setTexture(&twood);
			
			for(int i=0; i<8;i++)
				{
					for(int j=0; j<7; j++)
					{
						window.draw(rect);
						rect.move(300, 0);
					}
					rect.move(-2100, 150);
				}
		}
	
	public:
		RenderWindow window;
		
		Game()
		{
			window.create(VideoMode(1920, 1080), "Title");
			window.setFramerateLimit(30);
			twood.loadFromFile("sprites/woodTexture.png");
		}
		
		void menu()
		{
			
			while (window.isOpen())
			{
				Event event;
				
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
						window.close();
				}
				menu_bg();
				window.display();
			}
		}
};

int main()
{
	Game game;
	game.menu();
	return 0;
}	

