#ifndef __GAMELUABINDINGS_H
#define __GAMELUABINDINGS_H

/* NOTE: This class should be included as the last include in
    your game/applications singleton's cpp file. */

// Utils
#include "StringUtilsBind.h"
// Config
#include "ConfigBind.h"
// Camera
#include "Camera2DBind.h"
#include "Camera3DBind.h"
// Game Draw
#include "ColourBind.h"
#include "OpenGLDrawBind.h"
// Game Objects
#include "GameObjectBind.h"
#include "BossBind.h"
#include "BulletBind.h"
#include "PlayerBind.h"
// Game Timers
#include "TimerBind.h"
#include "FrameCounter.h"
#include "FPSLimiterBind.h"
// Game Physics
#include "PhysicsBind.h"
// Game Input
#include "GamePadBind.h"
#include "KeyboardBind.h"
#include "MouseBind.h"
#include "InputSystemBind.h"
// Game
#include "GameBind.h"

#endif // __GAMELUABINDINGS_H
