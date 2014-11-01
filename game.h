struct coordinate {
	int x;
	int y;
} Coordinate;


/* Game Variable */
struct game {
	int blockCount;
	struct coordinate blocks[32];
	struct coordinate player;
} Game;

int *getBlockCount(struct game *game);
