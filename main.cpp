#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;


class Game
{
	private:
		Texture twoodLight, twoodDarkLong;
		Font font;
		
		void menu_bg()
		{
			RectangleShape rect(Vector2f(300, 150));
			rect.setTexture(&twoodLight);
			
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
		
		void menu_buttons()
		{
			RectangleShape rect(Vector2f(1100, 200));
			rect.setOutlineThickness(8);
			rect.setOutlineColor(Color(36, 34, 34));
			rect.setTexture(&twoodDarkLong);
			rect.setPosition(410, 290);
			
			Text text;
			text.setFont(font);
			text.setString("Start");
			text.setCharacterSize(170);
			text.setFillColor(Color::White);
			text.setPosition(750, 270);
			
			window.draw(rect);
			rect.move(0, 300);
			window.draw(rect);
			
			window.draw(text);
			text.move(-75, 300);
			text.setString("Credits");
			window.draw(text);
		}
		
		int handle_menu_buttons()//0-none, 1-start, 2-credits
		{
			Vector2f mouse_pos = window.mapPixelToCoords(Mouse::getPosition(window));
			if (mouse_pos.x>410 && mouse_pos.x<1510 && mouse_pos.y>290 && mouse_pos.y<490 && Mouse::isButtonPressed(Mouse::Left)) return 1;
			return 0;
		}
	
	public:
		RenderWindow window;
		
		Game()
		{
			window.create(VideoMode(1920, 1080), "Title");
			window.setFramerateLimit(30);
			twoodLight.loadFromFile("sprites/woodTexture.png");
			twoodDarkLong.loadFromFile("sprites/Wooden Planks cut long.png");
			font.loadFromFile("fonts/Minimal3x5.ttf");
			
		}
		
		void menu()
		{
			int stage = 0;
			while (window.isOpen())
			{
				Event event;
				
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
						window.close();
				}
				if (stage==0)
				{
				menu_bg();
				menu_buttons();
				}
				else if (stage==1) return;
				else//credits
				{}
				
				window.display();
				
				stage = handle_menu_buttons();
			}
		}
};

int main()
{
	Game game;
	game.menu();
	return 0;
}	

