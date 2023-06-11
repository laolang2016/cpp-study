## 一个碰撞检的例子

```lua linenums="1" title="main.lua"
local fixedInterval = 1 / 60 -- 60 FPS
local fixedTimer = 0
 
function love.load()
    love.physics.setMeter(48)
    world = love.physics.newWorld(0, 9.81 * 48, true)
 
    ground = love.physics.newBody(world, 0, 0, "static")
    ground_shape = love.physics.newRectangleShape(0, 500, 600, 10)
    ground_fixture = love.physics.newFixture(ground, ground_shape)
    ground_fixture:setUserData("ground")
 
    -- 坐标与速度
    x = 24
    y = 24
    speed = 200
 
    hero = love.physics.newBody(world, 24, 24, "dynamic")
    hero:setGravityScale(0) -- 重力为 0
    hero_shape = love.physics.newRectangleShape(48, 48)
    hero_fixture = love.physics.newFixture(hero, hero_shape)
    hero_fixture:setUserData("hero")
 
    -- 图片
    img = love.graphics.newImage("assets/sprite/box_red.png")
 
    -- 碰撞回调
    world:setCallbacks(beginContact, endContact, preSolve, postSolve)
 
end
 
local function fixUpdate()
    -- 根据方向键移动刚体
    if love.keyboard.isDown("up") then
        hero:setLinearVelocity(0, -speed)
    elseif love.keyboard.isDown("right") then
        hero:setLinearVelocity(speed, 0)
    elseif love.keyboard.isDown("down") then
        hero:setLinearVelocity(0, speed)
    elseif love.keyboard.isDown("left") then
        hero:setLinearVelocity(-speed, 0)
    end
end
 
function love.update(dt)
    -- 累加计时器的时间
    fixedTimer = fixedTimer + dt
    -- 如果计时器的时间超过了固定时间间隔，执行 FixedUpdate 逻辑
    while fixedTimer >= fixedInterval do
        fixedTimer = fixedTimer - fixedInterval
 
        -- 在这里执行 FixedUpdate 的逻辑
        fixUpdate()
    end
 
    world:update(dt)
end
 
function love.draw()
    love.graphics.polygon("line", ground:getWorldPoints(ground_shape:getPoints()))
    love.graphics.draw(img, hero:getX() - 24, hero:getY() - 24)
 
    love.graphics.polygon("line", hero:getWorldPoints(hero_shape:getPoints()))
    hero:setLinearVelocity(0, 0) -- 初始速度为 0
end
 
function beginContact(fixture1, fixture2, contact)
    -- 获取碰撞体的用户数据
    local userData1 = fixture1:getUserData()
    local userData2 = fixture2:getUserData()
 
    -- 在这里实现碰撞逻辑
    print("beginContact", userData1, userData2)
end
 
function endContact(fixture1, fixture2, contact)
    -- 获取碰撞体的用户数据
    local userData1 = fixture1:getUserData()
    local userData2 = fixture2:getUserData()
 
    -- 在这里实现碰撞逻辑
    -- print("endContact", userData1, userData2)
end
 
function preSolve(fixture1, fixture2, contact)
    -- 获取碰撞体的用户数据
    local userData1 = fixture1:getUserData()
    local userData2 = fixture2:getUserData()
 
    -- 在这里实现碰撞逻辑
    -- print("preSolve", userData1, userData2)
end
 
function postSolve(fixture1, fixture2, contact, normal_impulse, tangent_impulse)
    -- 获取碰撞体的用户数据
    local userData1 = fixture1:getUserData()
    local userData2 = fixture2:getUserData()
 
    -- 在这里实现碰撞逻辑
    -- print("postSolve", userData1, userData2)
end
```

