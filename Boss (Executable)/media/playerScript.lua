
function main()
	---- Set Initial State
    --if this:getState() == "" then
		----this:setState("START")
	--end

	-- *****************
	-- * HANDLE EVENTS *
	-- *****************

	-- If player is still alive
	if (this:isDead() == false) then

        -- Player pressed shoot
        if (pGame:getInputSystem():getMouse():isLeftButtonToggled() == true) or
            (pGame:getInputSystem():getKeyboard():isKeyToggled(GLFW_KEY_SPACE) == true) then

            -- Calculate position and direction of the bullet
            dx = (pGame:getInputSystem():getMouse():getX() - pGame:getPlayer():getX());
            dy = (pGame:getInputSystem():getMouse():getY() - pGame:getPlayer():getY());
            dm = math.sqrt(dx * dx + dy * dy);
            dx = dx / dm;
            dy = dy / dm;
            if (math.abs(dm) < 1.0) then dm = 1 end;

            -- Create the bullet
            pGame:createPlayerBullet(this:getX() + dx * this:getRadius(), this:getY() + dy * this:getRadius(), dx * 5.0, dy * 5.0);

            --pGame:playSound("shootSound.wav");

        end;

        pGame:getPlayer():setXVelocity(0.0);
        pGame:getPlayer():setYVelocity(0.0);

        -- Make the player move based on input
        if (pGame:getInputSystem():getKeyboard():isKeyPressed(GLFW_KEY_W) == true) then
            pGame:getPlayer():setYVelocity(-pGame:getPlayer():getSpeed());
        end;
        if (pGame:getInputSystem():getKeyboard():isKeyPressed(GLFW_KEY_A) == true) then
            pGame:getPlayer():setXVelocity(-pGame:getPlayer():getSpeed());
        end;
        if (pGame:getInputSystem():getKeyboard():isKeyPressed(GLFW_KEY_S) == true) then
            pGame:getPlayer():setYVelocity(pGame:getPlayer():getSpeed());
        end;
        if (pGame:getInputSystem():getKeyboard():isKeyPressed(GLFW_KEY_D) == true) then
            pGame:getPlayer():setXVelocity(pGame:getPlayer():getSpeed());
        end;

	end;

end;
