-- ****************************
-- * (c) Dodgee Software 2019 *
-- ****************************

phase1Timer = Timer()
phase2Timer = Timer()
phase3Timer = Timer()
phase4Timer = Timer()
phase5Timer = Timer()
phase5ShootTimer = Timer()
pahse5Alternater = 0;

function main()
	-- Set Initial State
    if this:getState() == "" then
		this:setState("START")
	end

    if (this:getHealth() <= 0 and this:getState() ~= "DEAD") then
        this:setState("DEAD")
    end

    if this:getHealth() > 0 then
        -- Delegate Control to state function
        if (this:getState() == "START") then start() end
        if (this:getState() == "INTRO") then intro() end
        if (this:getState() == "PHASE1") then phase1() end
        if (this:getState() == "PHASE2") then phase2() end
        if (this:getState() == "PHASE3") then phase3() end
        if (this:getState() == "PHASE4") then phase4() end
        if (this:getState() == "PHASE5") then phase5() end
        if (this:getState() == "DEAD") then deadState() end
    end
end

-- Reset/Setup the Boss
function start()
	pGame:bossSpeak("Start")
	this:setX(pGame:getConfig():getWidth() + 100)
    this:setY(pGame:getConfig():getHeight() / 2.0);
    pGame:bossSpeak("Boss Intro: hahahaha, you cant defeat me!!")
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
    dx = ((pGame:getConfig():getWidth() - 200) - this:getX())
    dy = ((pGame:getConfig():getHeight() / 2.0) - this:getY())
    dm = math.sqrt(dx * dx + dy * dy)
    this:setXVelocity((dx / dm))
    this:setYVelocity((dy / dm))
    if dm <= 1 then
        this:setX((pGame:getConfig():getWidth() - 200))
        this:setY((pGame:getConfig():getHeight() / 2.0))
        this:setState("PHASE1")
        pGame:bossSpeak("Phase1: Shoot me if you dare!")
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
    if phase1Timer:getTicks() > 10000 then
        this:setState("PHASE2")
        pGame:bossSpeak("Phase2: You're making me mad!")
        phase1Timer:stop()
        phase2Timer:start()
        phase3Timer:stop()
        phase4Timer:stop()
        phase5Timer:stop()
    end
end

-- Stay in one spot and let the player shoot you
function phase2()
    this:setXVelocity((math.random() - math.random()) * 4.0)
    this:setYVelocity((math.random() - math.random()) * 4.0)
	this:setImmuneToDamage(true);
    if phase2Timer:getTicks() > 10000 then
        this:setState("PHASE3")
        pGame:bossSpeak("Phase3: Ima bounce off the walls rawr!")
        phase1Timer:stop()
        phase2Timer:stop()
        phase3Timer:start()
        phase4Timer:stop()
        phase5Timer:stop()
        this:setXVelocity(-4.0)
        this:setYVelocity(-4.0)
    end
end

-- Bounce
function phase3()
    if (this:getY() < 45 + this:getRadius()) then
        this:setY(45 + this:getRadius());
        this:setYVelocity(4.0);
    end
    if (this:getY() > pGame:getConfig():getHeight() - this:getRadius() - 45.0) then
        this:setY(pGame:getConfig():getHeight() - this:getRadius() - 45.0);
        this:setYVelocity(-4.0);
    end
    if (this:getX() - this:getRadius() < 0) then
        this:setX(0 + this:getRadius());
        this:setXVelocity(4.0);
    end
    if (this:getX() + this:getRadius() > pGame:getConfig():getWidth()) then
        this:setX(pGame:getConfig():getWidth() - this:getRadius());
        this:setXVelocity(-4.0);
    end
    if phase3Timer:getTicks() > 10000 then
        this:setState("PHASE4");
        pGame:bossSpeak("Phase4: Going back to my sweet spot!")
        phase1Timer:stop();
        phase2Timer:stop();
        phase3Timer:stop();
        phase4Timer:start();
        phase5Timer:stop();
    end
end

-- Go back to initial position
function phase4()
    dx = ((pGame:getConfig():getWidth() - 100) - this:getX())
    dy = ((pGame:getConfig():getHeight() / 2.0) - this:getY())
    dm = math.sqrt(dx * dx + dy * dy)
    this:setXVelocity((dx / dm) * 4.0)
    this:setYVelocity((dy / dm) * 4.0)
    if dm <= 5 then
        this:setX(pGame:getConfig():getWidth() - 100)
        this:setY(pGame:getConfig():getHeight() / 2.0)
        this:setState("PHASE5")
        pGame:bossSpeak("Phase5: Pew Pew Pew You Die Now!")
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
    if phase5ShootTimer:getTicks() > 1000 then
        phase5ShootTimer:stop()
        phase5ShootTimer:start()
        radianStep = math.pi * 2.0 / 8.0
        radianMax = math.pi * 2.0
        for radian = 0, radianMax, radianStep do
            x = math.cos(radian) * this:getRadius() + this:getX()
            y = math.sin(radian) * this:getRadius() + this:getY()
            xVel = math.cos(radian) * 4.0
            yVel = math.sin(radian) * 4.0
            pGame:createBossBullet(x, y, xVel, yVel)
        end
    end

    if phase5Timer:getTicks() > 10000 then
        this:setImmuneToDamage(false);
        this:setState("PHASE1")
        pGame:bossSpeak("Phase1: Shoot me if you dare!")
        phase1Timer:start()
        phase2Timer:stop()
        phase3Timer:stop()
        phase4Timer:stop()
        phase5Timer:stop()
        phase5ShootTimer:stop()
        this:setXVelocity(0.0)
        this:setYVelocity(0.0)
        phase5ShootOffset = 0
    end
end

function deadState()

end
