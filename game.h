struct coordinate {
	int x;
	int y;
} Coordinate;


/* Game Variable */
typedef struct {
	int blockCount;
	Coordinate[64] blocks;
	Coordinate player;
} Game;
