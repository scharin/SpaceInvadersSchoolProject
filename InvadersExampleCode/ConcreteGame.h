class ConcreteGame : public Game {
public:

private:
	std::mt19937 mGenerator;
	sf::RenderWindow mRenderWindow;
	TextureResources mTextureResources;
	EntityVector mEntities;
	EntityVector mNewEntities;
	EntityVector mOldEntities;
	float mTime;
	float mSpawnTime;
	bool mGameOver;
};