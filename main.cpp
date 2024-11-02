#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
using namespace sf;


class Game
{
	private:
		Texture twoodLight, twoodDarkLong, player_walk[6], player_walk_flipped[6];
		Font font;
		RectangleShape player;
		int frame=0, pmovement_vector[2]={};
		
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
		
		int handle_menu_buttons(int stage)//0-none, 1-start, 2-credits
		{
			Vector2f mouse_pos = window.mapPixelToCoords(Mouse::getPosition(window));
			if (mouse_pos.x>410 && mouse_pos.x<1510 && mouse_pos.y>290 && mouse_pos.y<490 && Mouse::isButtonPressed(Mouse::Left)) return 1;
			if (mouse_pos.x>410 && mouse_pos.x<1510 && mouse_pos.y>590 && mouse_pos.y<790 && Mouse::isButtonPressed(Mouse::Left) || stage==2) return 2;
			return 0;
		}
		
		void call_movement()
		{
			if (Keyboard::isKeyPressed(Keyboard::A)) pmovement_vector[0]=-6;
			else if (Keyboard::isKeyPressed(Keyboard::D)) pmovement_vector[0]=6;
			else pmovement_vector[0]=0;
		}
		
		void commit_movement() 
		{
			player.move(pmovement_vector[0], pmovement_vector[1]);
			
			if (pmovement_vector[0]!=0)
			{
				if (pmovement_vector[0]<0) player.setTexture(&player_walk[frame/6]);
				else player.setTexture(&player_walk_flipped[frame/6]);
			}
			
			window.draw(player);
		}
		
		void count_frames()
		{
			frame++;
			if (frame>29)frame=0;
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
			player_walk[0].loadFromFile("sprites/cat sprite/walk1.png");
			player_walk[1].loadFromFile("sprites/cat sprite/walk2.png");
			player_walk[2].loadFromFile("sprites/cat sprite/walk3.png");
			player_walk[3].loadFromFile("sprites/cat sprite/walk4.png");
			player_walk[4].loadFromFile("sprites/cat sprite/walk5.png");
			player_walk[5].loadFromFile("sprites/cat sprite/walk6.png");
			player_walk_flipped[0].loadFromFile("sprites/cat sprite/walk1-flipped.png");
			player_walk_flipped[1].loadFromFile("sprites/cat sprite/walk2-flipped.png");
			player_walk_flipped[2].loadFromFile("sprites/cat sprite/walk3-flipped.png");
			player_walk_flipped[3].loadFromFile("sprites/cat sprite/walk4-flipped.png");
			player_walk_flipped[4].loadFromFile("sprites/cat sprite/walk5-flipped.png");
			player_walk_flipped[5].loadFromFile("sprites/cat sprite/walk6-flipped.png");
			
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
				stage = handle_menu_buttons(stage);
				}
				else if (stage==1) return;
				else
				{
					window.clear();
					menu_bg();
				}
				
				window.display();
			}
		}
		
		void scene1()
		{
			player.setSize(Vector2f(50, 50));
//			player.setFillColor(Color::Red);
			Texture p;
			p.loadFromFile("sprites/cat sprite/walk2.png");
			player.setTexture(&p);
			while (window.isOpen())
			{
				Event event;
				
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
						window.close();
					call_movement();
				}
				
				window.clear(Color::White);
				commit_movement();
				window.display();
				
				count_frames();
			}
		}
};

int main()
{
	Game game;
	game.menu();
	game.scene1();
	return 0;
}	

