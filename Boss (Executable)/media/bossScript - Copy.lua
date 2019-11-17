-- ****************************
-- * (c) Dodgee Software 2019 *
-- ****************************
 
phase1Timer = Timer()
phase2Timer = Timer()
phase3Timer = Timer()
phase4Timer = Timer()
phase5Timer = Timer()
phase5ShootTimer = Timer()

function main()

    -- Set Initial State
    if this:getState() == "" then this:setState("START") end

    if this:getHealth() > 0 then
        -- Delegate Control to state function
        if this:getState() == "START" then start() end
        if this:getState() == "INTRO" then intro() end
        if this:getState() == "PHASE1" then phase1() end
        if this:getState() == "PHASE2" then phase2() end
        if this:getState() == "PHASE3" then phase3() end
        if this:getState() == "PHASE4" then phase4() end
        if this:getState() == "PHASE5" then phase5() end
    end
end

-- Reset/Setup the Boss
function start()
    this:setX(640 + 100)
    this:setY(240)
    this:setState("INTRO")
    phase1Timer:stop()
    phase2Timer:stop()
    phase3Timer:stop()
    phase4Timer:stop()
    phase5Timer:stop()
    phase5ShootTimer:stop()
    this:setImmuneToDamage(true);
end

-- Move the boss into initial position
function intro()
    --BattleGameState:bossSpeak("Boss Intro: hahahaha, you cant defeat me!!")
    dx = (500 - this:getX())
    dy = (240 - this:getY())
    dm = math.sqrt(dx * dx + dy * dy)
    this:setXVelocity((dx / dm))
    this:setYVelocity((dy / dm))
    if dm <= 1 then
        this:setX(500)
        this:setY(240)
        this:setState("PHASE1")
        this:setXVelocity(0.0)
        this:setYVelocity(0.0)
        phase1Timer:start()
        phase2Timer:stop()
        phase3Timer:stop()
        phase4Timer:stop()
        phase5Timer:stop()
        this:setImmuneToDamage(false);
    end
end

-- Stay in one spot and let the player shoot you
function phase1()
    --BattleGameState:bossSpeak("Phase1: Shoot me if you dare!")
    if phase1Timer:getTicks() > 10000 then
        this:setState("PHASE2")
        phase1Timer:stop()
        phase2Timer:start()
        phase3Timer:stop()
        phase4Timer:stop()
        phase5Timer:stop()
    end
end

-- Stay in one spot and let the player shoot you
function phase2()
    --BattleGameState:bossSpeak("Phase2: You're making me mad!")

    this:setXVelocity((math.random() - math.random()))
    this:setYVelocity((math.random() - math.random()))

    if phase2Timer:getTicks() > 10000 then
        this:setState("PHASE3")
        phase1Timer:stop()
        phase2Timer:stop()
        phase3Timer:start()
        phase4Timer:stop()
        phase5Timer:stop()
        this:setXVelocity(-1.0)
        this:setYVelocity(-1.0)
        this:setImmuneToDamage(true);
    end
end

-- Bounce
function phase3()
    --BattleGameState:bossSpeak("Phase3: Ima bounce off the walls rawr!")
    if (this:getY() < 100) then
        this:setY(100)
        this:setYVelocity(1.0)
    end
    if (this:getY() > 380) then
        this:setY(380)
        this:setYVelocity(-1.0)
    end
    if (this:getX() < 40) then
        this:setX(40)
        this:setXVelocity(1.0)
    end
    if (this:getX() > 580) then
        this:setX(580)
        this:setXVelocity(-1.0)
    end
    if phase3Timer:getTicks() > 10000 then
        this:setState("PHASE4")
        phase1Timer:stop()
        phase2Timer:stop()
        phase3Timer:stop()
        phase4Timer:start()
        phase5Timer:stop()
    end
end

-- Go back to initial position
function phase4()
    --BattleGameState:bossSpeak("Phase4: Going back to my sweet spot!")
    dx = (500 - this:getX())
    dy = (240 - this:getY())
    dm = math.sqrt(dx * dx + dy * dy)
    this:setXVelocity((dx / dm))
    this:setYVelocity((dy / dm))
    if dm <= 1 then
        this:setX(500)
        this:setY(240)
        this:setState("PHASE5")
        this:setXVelocity(0.0)
        this:setYVelocity(0.0)
        phase2Timer:start()
        this:setImmuneToDamage(true);
        phase1Timer:stop()
        phase2Timer:stop()
        phase3Timer:stop()
        phase4Timer:stop()
        phase5Timer:start()
        phase5ShootTimer:start()
    end
end

function phase5()
    --BattleGameState:bossSpeak("Phase5: Pew Pew Pew You Die Now!")
    if phase5ShootTimer:getTicks() > 1000 then
        phase5ShootTimer:stop()
        phase5ShootTimer:start()
        radianStep = math.pi * 2 / 8
        radianMax = math.pi * 2
        for radian = 0, radianMax, radianStep do
            x = math.cos(radian) * 55 + this:getX()
            y = math.sin(radian) * 55 + this:getY()
            xVel = math.cos(radian)
            yVel = math.sin(radian)
            BattleGameState:createBossBullet(x, y, xVel, yVel)
        end

    end

    if phase5Timer:getTicks() > 10000 then
        this:setImmuneToDamage(false);
        this:setState("PHASE1")
        phase1Timer:start()
        phase2Timer:stop()
        phase3Timer:stop()
        phase4Timer:stop()
        phase5Timer:stop()
        phase5ShootTimer:stop()
        phase5ShootOffset = 0
    end
end
