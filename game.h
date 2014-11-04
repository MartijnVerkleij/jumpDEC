struct coordinate {
        int x;
        int y;
};


/* Game Variable */
struct game {
        int blockCount;
        struct coordinate blocks[32];
        struct coordinate player;
};

