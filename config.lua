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
  friction = 0.0,
  elasticity = 1.0,
  infinity = true
};

-- ball
ball_settings = {
  x = 400.0,
  y = 678.0,
  mass = 0.5,
  friction = 0.0,
  elasticity = 1.0,
  speed = 200.0,
  infinity = true
};

-- wall
wall_settings = {
  mass = 10.0,
  friction = 0.0,
  elasticity = 1.0
};

-- brick
brick_settings = {
  mass = 10.0,
  friction = 0.0,
  elasticity = 1.0
};

--[[
- @title level tables
- @brief - the level must have a maximum of 10 columns * 7 rows
         - type of bricks: 1, 2, 3, 4, 5, 6 & 7
         - to place a gap must put a 0
--]]

kTotalLevels = 4; -- change if a level is added or removed

level1 = {
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

level2 = {
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
  5, 0, 0, 0, 0, 0, 0, 0, 0, 5,
  4, 0, 0, 0, 0, 0, 0, 0, 0, 4,
  3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
  2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

level3 = {
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  0, 6, 6, 6, 6, 6, 6, 6, 6, 0,
  0, 0, 5, 5, 5, 5, 5, 5, 0, 0,
  0, 0, 0, 4, 4, 4, 4, 0, 0, 0,
  0, 0, 0, 0, 3, 3, 0, 0, 0, 0,
  2, 2, 0, 0, 0, 0, 0, 0, 2, 2,
  1, 1, 0, 0, 0, 0, 0, 0, 1, 1
};

level4 = {
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  2, 2, 2, 2, 2, 0, 0, 0, 0, 0,
  3, 3, 3, 3, 3, 3, 0, 0, 0, 0,
  4, 4, 4, 4, 4, 4, 4, 0, 0, 0,
  5, 5, 5, 5, 5, 5, 5, 5, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 0,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};
