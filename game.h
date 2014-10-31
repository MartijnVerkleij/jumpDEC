struct coordinate {
	int x;
	int y;
} Coordinate;


/* Game Variable */
typedef struct {
	int blockCount;
	Coordinate[32] blocks;
	Coordinate player;
} Game;
