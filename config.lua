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
kSleepTime = 16.0; -- not using

-- bar
bar_settings = {
  cbar_x = 400.0,
  cbar_y = 700.0,
  lbar_x = 370.0,
  rbar_x = 430.0,
  mass = 0.5,
  friction = 0.0,
  elasticity = 1.0,
  infinity = true,
  max_speed = 500.0,
  air_friction = 0.98
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
         - first value is the number of the level
         - second value is the amount of bricks excluding gaps (0)
         - kind of bricks: 1, 2, 3, 4, 5, 6 & 7
         - to place a gap must put a 0
--]]

kTotalLevels = 4; -- change if a level is added or removed

level1 = {
  1, 70,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

level2 = {
  2, 30,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
  5, 0, 0, 0, 0, 0, 0, 0, 0, 5,
  4, 0, 0, 0, 0, 0, 0, 0, 0, 4,
  3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
  2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

level3 = {
  3, 38,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  0, 6, 6, 6, 6, 6, 6, 6, 6, 0,
  0, 0, 5, 5, 5, 5, 5, 5, 0, 0,
  0, 0, 0, 4, 4, 4, 4, 0, 0, 0,
  0, 0, 0, 0, 3, 3, 0, 0, 0, 0,
  2, 2, 0, 0, 0, 0, 0, 0, 2, 2,
  1, 1, 0, 0, 0, 0, 0, 0, 1, 1
};

level4 = {
  4, 49,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  2, 2, 2, 2, 2, 0, 0, 0, 0, 0,
  3, 3, 3, 3, 3, 3, 0, 0, 0, 0,
  4, 4, 4, 4, 4, 4, 4, 0, 0, 0,
  5, 5, 5, 5, 5, 5, 5, 5, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 0,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};
