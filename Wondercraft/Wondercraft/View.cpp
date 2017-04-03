#include "View.hpp"

#include <string>
#include <cmath>

#include "Tile.hpp"
#include "Menu.hpp"

View::View(Model* model) {
	windowSize = sf::Vector2f(960, 540);

	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Wondercraft");
	
	this->model = model;

	levelTextures = new TextureLoader("assets/tilesets/");
	spriteTextures = new TextureLoader("assets/sprites/");
	menuTextures = new TextureLoader("assets/menus/");
	itemTextures = new TextureLoader("assets/items/");
	EMPTY_ITEM_TEXTURE.create(SQUARE_SIZE_X, SQUARE_SIZE_Y);

	title.setTexture(*(menuTextures->get("titleScreen.png")));
	end.setTexture(*(menuTextures->get("endScreen.png")));
}

void View::initGame() {
	initVertexArray();
	initMenuArray();

	background.setTexture(*(levelTextures->get(model->tileSet + "/bg.png")));

	healthBar.setTexture(*(menuTextures->get("healthBar.png")));
	health.setTexture(*(menuTextures->get("health.png")));

	//player sprites
	playerHat.setTexture(*(spriteTextures->get("player/" + ItemType::enumToString(model->player->equipment[0]) + ".png")));
	playerHat.setOrigin(playerHat.getLocalBounds().width / 2, playerHat.getLocalBounds().height / 2);
	playerRobe.setTexture(*(spriteTextures->get("player/" + ItemType::enumToString(model->player->equipment[1]) + ".png")));
	playerRobe.setOrigin(playerRobe.getLocalBounds().width / 2, playerRobe.getLocalBounds().height / 2);
	playerStaff.setTexture(*(spriteTextures->get("player/" + ItemType::enumToString(model->player->equipment[2]) + ".png")));
	playerStaff.setOrigin(playerStaff.getLocalBounds().width / 2, playerStaff.getLocalBounds().height / 2);

	//menu sprites
	menu.setTexture(*(menuTextures->get("1.png")));
	index.setTexture(*(menuTextures->get("3.png")));
	selected.setTexture(*(menuTextures->get("4.png")));

	//transition sprites
	map.setTexture(*(menuTextures->get("transition/transition.png")));
	icon.setTexture(*(menuTextures->get("transition/icon.png")));
}

void View::initVertexArray() {
	int numCols = int(ceil(windowSize.x / TILE_SIZE) + 1);
	int numRows = int(ceil(windowSize.y / TILE_SIZE) + 1);

	//initialize the vertex array
	tileVertices = sf::VertexArray(sf::Quads, numCols * numRows * 4);

	//initialize positions
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			sf::Vertex* currTile = &tileVertices[(col + row * numCols) * 4];

			currTile[0].position = sf::Vector2f(col + 0, row + 0) * TILE_SIZE;
			currTile[1].position = sf::Vector2f(col + 1, row + 0) * TILE_SIZE;
			currTile[2].position = sf::Vector2f(col + 1, row + 1) * TILE_SIZE;
			currTile[3].position = sf::Vector2f(col + 0, row + 1) * TILE_SIZE;
		}
	}
}

void View::initMenuArray() {
	for (int row = 0; row < 3; row++) {
		equipmentSquares[row].setPosition(317, 3 + (SQUARE_SIZE_Y + 2) * row);
		equipmentSquares[row].setTexture(*(menuTextures->get("tile.png")));
	}

	for (int col = 0; col < 3; col++) {
		craftingSquares[col].setPosition(528 + (SQUARE_SIZE_X + 57) * col, 136);
		craftingSquares[col].setTexture(*(menuTextures->get("tile.png")));
	}


	for (int col = 0; col < 10; col++) {
		for (int row = 0; row < 3; row++) {
			inventorySquares[col][row].setPosition(84 + (SQUARE_SIZE_X + 5) * col, 280 + (SQUARE_SIZE_Y + 2) * row);
			inventorySquares[col][row].setTexture(*(menuTextures->get("tile.png")));
		}
	}

	index.setPosition(84, 280);
}

sf::Vector2i View::getSpritesheetCoords(int x, int y) {
	sf::Vector2i indices;

	//out of bounds
	if (x < 0 || x >= model->levelWidth || y < 0 || y >= model->levelHeight) {
		indices = sf::Vector2i(3, 0); // empty tile
	}
	//in bounds
	else {
		Tile* e = dynamic_cast<Tile*>(model->mapTiles[x][y]);

		if (e == NULL)
			indices = sf::Vector2i(3, 0); // empty tile

		else if (e->type == TileType::STONE)
			indices = sf::Vector2i(0, 0);

		else indices = sf::Vector2i(3, 0); // empty tile
	}
	
	return indices * (int(TILE_SIZE) + 2);
}

sf::RenderWindow& View::getWindow() {
	return window;
}

void View::updateTileArray() {
	int numCols = int(ceil(windowSize.x / TILE_SIZE) + 1);
	int numRows = int(ceil(windowSize.y / TILE_SIZE) + 1);

	//get first tile position within the level
	sf::Vector2f topLeft = getTopLeftCorner();
	int topLeftTileX = int(floor(topLeft.x));
	int topLeftTileY = int(floor(topLeft.y));

	//set texture coordinates
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			sf::Vertex* currTile = &tileVertices[(col + row * numCols) * 4];

			sf::Vector2i v = getSpritesheetCoords(col + topLeftTileX, row + topLeftTileY);
			currTile[0].texCoords = sf::Vector2f(v.x + 0 * TILE_SIZE, v.y + 0 * TILE_SIZE);
			currTile[1].texCoords = sf::Vector2f(v.x + 1 * TILE_SIZE, v.y + 0 * TILE_SIZE);
			currTile[2].texCoords = sf::Vector2f(v.x + 1 * TILE_SIZE, v.y + 1 * TILE_SIZE);
			currTile[3].texCoords = sf::Vector2f(v.x + 0 * TILE_SIZE, v.y + 1 * TILE_SIZE);
		}
	}
}

sf::Vector2f View::getTopLeftCorner() {
	sf::Vector2f startingCoord;
	startingCoord.x = model->camera.x - ((windowSize.x / 2) / TILE_SIZE);
	startingCoord.y = model->camera.y - ((windowSize.y / 2) / TILE_SIZE);

	return startingCoord;
}

sf::Vector2f View::getVertexArrayOffset() {
	sf::Vector2f topLeft = getTopLeftCorner();
	int topLeftTileX = int(floor(topLeft.x));
	int topLeftTileY = int(floor(topLeft.y));

	return sf::Vector2f(topLeftTileX - topLeft.x, topLeftTileY - topLeft.y) * TILE_SIZE;
}

void View::playTransition() {
	window.draw(map);
	icon.setPosition(118 + (model->currLevel - 1) * 230, 270);
	window.draw(icon);
	background.setTexture(*(levelTextures->get(model->tileSet + "/bg.png")));
}

void View::render() {
	window.clear();
	
	if (model->gameState == GameState::TITLE) {
		window.draw(title);
	}
	else if (model->gameState == GameState::END) {
		window.draw(end);
	}
	else if (model->gameState == GameState::TRANSITION) {
		playTransition();
	}
	else {
		float healthWidth = health.getTexture()->getSize().x / (float)40;
		health.setPosition(0 - ((40 - model->player->getHealth()) * healthWidth), 0);

		updateTileArray();

		//create a new render state for the camera displacement
		sf::RenderStates cameraState;
		cameraState.transform.translate(-getTopLeftCorner() * TILE_SIZE);

		//create a new render state for the vertex array
		sf::RenderStates vertexArrayState;
		vertexArrayState.transform.translate(getVertexArrayOffset());
		vertexArrayState.texture = levelTextures->get(model->tileSet + "/spritesheet.png");
		
		//draw background	
		window.draw(background);

		//draw vertex array
		window.draw(tileVertices, vertexArrayState);
		

		//draw health
		window.draw(health);
		window.draw(healthBar);


		//draw player
		playerHat.setTexture(*(spriteTextures->get("player/" + ItemType::enumToString(model->player->equipment[0]) + ".png")));
		playerHat.setPosition(model->player->getPosition() * TILE_SIZE);
		playerHat.setScale(model->player->facingRight ? 1 : -1, 1);
		window.draw(playerHat, cameraState);

		playerRobe.setTexture(*(spriteTextures->get("player/" + ItemType::enumToString(model->player->equipment[1]) + ".png")));
		playerRobe.setPosition(model->player->getPosition() * TILE_SIZE);
		playerRobe.setScale(model->player->facingRight ? 1 : -1, 1);
		window.draw(playerRobe, cameraState);

		playerStaff.setTexture(*(spriteTextures->get("player/" + ItemType::enumToString(model->player->equipment[2]) + ".png")));
		playerStaff.setPosition(model->player->getPosition() * TILE_SIZE);
		playerStaff.setScale(model->player->facingRight ? 1 : -1, 1);
		window.draw(playerStaff, cameraState);

		//draw player projectiles
		for (int i = 0; i < model->playerProjectiles.size(); i++) {
			sf::Sprite projectile;
			if (model->player->equipment[2] == ItemType::FIRE_STAFF) {
				projectile.setTexture(*spriteTextures->get("fire spell.png"));
			}
			else if (model->player->equipment[2] == ItemType::AIR_STAFF) {
				projectile.setTexture(*spriteTextures->get("air spell.png"));
			}
			else if (model->player->equipment[2] == ItemType::EARTH_STAFF) {
				projectile.setTexture(*spriteTextures->get("earth spell.png"));
			}
			else if (model->player->equipment[2] == ItemType::WATER_STAFF) {
				projectile.setTexture(*spriteTextures->get("water spell.png"));
			}
			else {
				projectile.setTexture(*spriteTextures->get("basic spell.png"));
			}
			projectile.setOrigin(projectile.getTexture()->getSize().x / 2, projectile.getTexture()->getSize().y / 2);
			projectile.setPosition(model->playerProjectiles[i]->getPosition() * TILE_SIZE);
			projectile.setRotation(model->playerProjectiles[i]->rotation);
			window.draw(projectile, cameraState);
		}

		//draw enemies
		for (int i = 0; i < model->enemies.size(); i++) {
			sf::Sprite enemy;
			
			Enemy* currentEnemy = dynamic_cast <Enemy*>(model->enemies[i]);

			switch (currentEnemy->type)
			{
			case EnemyType::GOOBER:
				//goober texture
				enemy.setTexture(*spriteTextures->get("goober1.png"));
				break;
			case EnemyType::GHOST:
				//ghost texture
				enemy.setTexture(*spriteTextures->get("ghostie.png"));
				break;
			case EnemyType::GOBLIN:
				//goblin texture
				enemy.setTexture(*spriteTextures->get("gremlin1.png"));
				break;
			default:
				break;
			}

			enemy.setOrigin(enemy.getTexture()->getSize().x / 2, enemy.getTexture()->getSize().y / 2); 

			if (currentEnemy->right == true) {
				enemy.setScale(sf::Vector2f(-1,1));
			}
			else if (currentEnemy->right == false) {
				enemy.setScale(sf::Vector2f(1, 1));
			}

			enemy.setPosition(model->enemies[i]->getPosition() * TILE_SIZE);
			window.draw(enemy, cameraState);
		}

		//draw items
		for (int i = 0; i < model->items.size(); i++) {
			sf::Sprite item;
			
			item.setTexture(*itemTextures->get(ItemType::enumToString(model->items[i]->type) + ".png"));
			item.setOrigin(item.getTexture()->getSize().x / 2, item.getTexture()->getSize().y / 2);
			item.setPosition(model->items[i]->position * TILE_SIZE);
			window.draw(item, cameraState);
		}

		if (model->gameState == GameState::INVENTORY) { //drawing the pause menu
			window.draw(menu);

			for (int i = 0; i < 3; i++) {
				window.draw(equipmentSquares[i]);
			}

			for (int i = 0; i < 3; i++) {
				window.draw(craftingSquares[i]);
			}

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 3; j++) {
					window.draw(inventorySquares[i][j]);
				}
			}

			//draws the player on the menu
			sf::Vector2f invPlayerPos(185, 135);
			playerHat.setPosition(invPlayerPos);
			window.draw(playerHat);
			playerRobe.setPosition(invPlayerPos);
			window.draw(playerRobe);
			playerStaff.setPosition(invPlayerPos);
			window.draw(playerStaff);

			//draws the index square
			if (model->menu.menuSide == MenuSide::EQUIPMENT) {
				index.setPosition(317, 3 + (SQUARE_SIZE_Y + 2) * model->menu.equipmentIndex);
			}
			else if (model->menu.menuSide == MenuSide::CRAFTING) {
				index.setPosition(528 + (SQUARE_SIZE_X + 57) * model->menu.craftingIndex, 136);
			}
			else if (model->menu.menuSide == MenuSide::INVENTORY) {
				index.setPosition(84 + (SQUARE_SIZE_X + 5) * model->menu.inventoryIndex.x,
					280 + (SQUARE_SIZE_Y + 2) * model->menu.inventoryIndex.y);
			}
			window.draw(index);

			//draws the selected square
			if (model->menu.selectedSide == MenuSide::EQUIPMENT) {
				selected.setPosition(317, 3 + (SQUARE_SIZE_Y + 2) * model->menu.selected.y);
			}
			else if (model->menu.selectedSide == MenuSide::CRAFTING) {
				selected.setPosition(528 + (SQUARE_SIZE_X + 57) * model->menu.selected.x, 136);
			}
			else if (model->menu.selectedSide == MenuSide::INVENTORY) {
				selected.setPosition(84 + (SQUARE_SIZE_X + 5) * model->menu.selected.x,
					280 + (SQUARE_SIZE_Y + 2) * model->menu.selected.y);
			}
			if(model->menu.selected != sf::Vector2i(-1, -1))
				window.draw(selected);

			//draw equipment items
			for (int i = 0; i < 3; i++) {
				sf::Sprite itemSprite;

				std::string itemString = ItemType::enumToString(model->player->equipment[i]);

				itemSprite.setTexture(*itemTextures->get(itemString + ".png"));
				itemSprite.setPosition(equipmentSquares[i].getPosition());
				window.draw(itemSprite);
			}

			//draw crafting items
			for (int i = 0; i < 3; i++) {
				sf::Sprite itemSprite;

				std::string itemString;
				if(i == 2) itemString = ItemType::enumToString(model->menu.craftedItem());
				else itemString = ItemType::enumToString(model->menu.craftingSlots[i]);

				if (itemString != "")
					itemSprite.setTexture(*itemTextures->get(itemString + ".png"));
				else itemSprite.setTexture(EMPTY_ITEM_TEXTURE);
				
				itemSprite.setPosition(craftingSquares[i].getPosition());
				window.draw(itemSprite);
			}

			//draw inventory items
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 3; j++) {
					if (model->inventory[i][j] != NULL) {
						//draw the inventory item on top
						sf::Sprite itemSprite;

						std::string itemString = ItemType::enumToString(model->inventory[i][j]);

						itemSprite.setTexture(*itemTextures->get(itemString + ".png"));
						itemSprite.setPosition(inventorySquares[i][j].getPosition());
						window.draw(itemSprite);
					}
				}
			}
		}
	}
    
	window.display();
}