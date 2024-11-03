#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
using namespace sf;


class Game
{
	private:
		Texture twoodLight, twoodDarkLong, player_walk[6], player_walk_flipped[6], player_jump[6];
		Font font;
		RectangleShape player;
		int frame=0, pmovement_vector[2]={}, catSize[2]={75,75}, framesToJump=40;
		bool orientation=1, jumpingNow=false;//0-left 1-right
		
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
		
		
		bool isOnPlatform(std::vector<std::vector<int> > surfaces)
		{
			for(int i = 0; i < surfaces.size(); i++)
				if((player.getPosition().x > surfaces.at(i)[0] && player.getPosition().x < surfaces.at(i)[2] && player.getPosition().y + catSize[1]+1 < surfaces.at(i)[1] && player.getPosition().y + catSize[1]+1 > surfaces.at(i)[3])&& (player.getPosition().x+catSize[0]-3 > surfaces.at(i)[0] && player.getPosition().x+catSize[0]-3  < surfaces.at(i)[2] && player.getPosition().y  + catSize[1]+1 < surfaces.at(i)[1] && player.getPosition().y  + catSize[1]+1 > surfaces.at(i)[3]))
					return 1;
			return 0;
		}
		
		void cat_gravity(std::vector<std::vector<int> > surfaces)//x1,y2,x2,y2
		{
			if (isOnPlatform(surfaces) && !jumpingNow) pmovement_vector[1]=0;
			else if (!isOnPlatform(surfaces) && !jumpingNow) pmovement_vector[1]=10;
		}
		
		void call_movement(std::vector<std::vector<int> > surfaces)
		{
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				pmovement_vector[0]=-6;
				orientation=false;
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				pmovement_vector[0]=6;
				orientation=true;
			}
			else pmovement_vector[0]=0;
			if (Keyboard::isKeyPressed(Keyboard::Space) && framesToJump>0 && isOnPlatform(surfaces)) 
			{
				pmovement_vector[1]=-15;
				jumpingNow = true;
			}
		}
		
		void commit_movement(std::vector<std::vector<int> > surfaces) 
		{
			int waklIntRects[6][2]={{86,81},{85,76},{85,81},{86,81},{91,76},{91,81}};
			cat_gravity(surfaces);
			
			if (framesToJump>20&&jumpingNow)framesToJump--;
			else jumpingNow=false;
			
			if(isOnPlatform(surfaces)) framesToJump=40;
			
			if (framesToJump<30&&jumpingNow)pmovement_vector[1]=-10;
			
			player.move(pmovement_vector[0], pmovement_vector[1]);
			
			if (!isOnPlatform(surfaces))
			{
				int index=1;
				if (orientation)index+=3;
				player.setTexture(&player_jump[index]);
				player.setSize(Vector2f(catSize[0]*1.25, catSize[1]));
				player.setTextureRect(IntRect(0, 0, 96, 81));
			}
			else if (pmovement_vector[0]!=0)
			{
				player.setSize(Vector2f(catSize[0], catSize[1]));
				if (pmovement_vector[0]<0) player.setTexture(&player_walk[frame/6]);
				else player.setTexture(&player_walk_flipped[frame/6]);
				player.setTextureRect(IntRect(0, 0, waklIntRects[frame/6][0], waklIntRects[frame/6][1]));
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
			player_jump[0].loadFromFile("sprites/cat sprite/jump1.png");
			player_jump[1].loadFromFile("sprites/cat sprite/jump2.png");
			player_jump[2].loadFromFile("sprites/cat sprite/jump3.png");
			player_jump[3].loadFromFile("sprites/cat sprite/jump1-flipped.png");
			player_jump[4].loadFromFile("sprites/cat sprite/jump2-flipped.png");
			player_jump[5].loadFromFile("sprites/cat sprite/jump3-flipped.png");
			
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
			player.setSize(Vector2f(catSize[0], catSize[1]));
			Texture p;
			std::vector<std::vector<int> > blocks;
			std::vector<int> block;
			block.push_back(500);
			block.push_back(1080);
			block.push_back(750);
			block.push_back(1000);
			blocks.push_back(block);
			
			p.loadFromFile("sprites/cat sprite/walk2.png");
			player.setTexture(&p);
			
			RectangleShape rect(Vector2f(250, 80));
			rect.setFillColor(Color::Red);
			rect.setPosition(500, 1000);
			while (window.isOpen())
			{
				Event event;
				
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
						window.close();
					call_movement(blocks);
				}
				
				
				window.clear(Color::White);
				window.draw(rect);
				
				commit_movement(blocks);
				
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

