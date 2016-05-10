--[[
-
- @project Arkanoid
- @brief Lua Config
- @author Toni Marquez
-
--]]

-- window
kNormalWindowWidth = 800;
kNormalWindowHeight = 800;
kDebugWindowWidth = 1200;
kDebugWindowHeight = 800;
kSleepTime = 16.0;

-- bar
bar_settings = {
  x = 400.0,
  y = 700.0,
  mass = 0.5,
  friction = 0.5,
  elasticity = 1.0,
  infinity = true
};

-- ball
ball_settings = {
  x = 400.0,
  y = 678.0,
  mass = 0.5,
  friction = 0.5,
  elasticity = 1.0,
  speed = 100.0,
  infinity = false
};

--[[
- @title level tables
- @brief - first position of the table is the number of bricks
         - the level must have a maximum of 10 columns,
           but can have many rows as you want
         - type of bricks: 1, 2, 3, 4, 5, 6 & 7
         - to place a gap must put a 0 (it also counts for the total)
--]]

kTotalLevels = 3;

level1 = {
  70, -- number of bricks
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

level2 = {
  70, -- number of bricks
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

level3 = {
  70, -- number of bricks
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  6, 0, 6, 6, 6, 6, 6, 6, 6, 6,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
