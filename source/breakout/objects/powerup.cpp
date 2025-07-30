#include "powerup.hpp"

#include "ball.hpp"
#include "paddle.hpp"
#include "player.hpp"
#include "glm/ext/vector_common.hpp"
#include "glm/gtx/rotate_vector.hpp"

breakout::PowerUp::PowerUp()
{
    PopulateSprites<PowerFont>();
    bounds = {
        .left = 0,
        .top = 0,
        .right = static_cast<float>(sprites[0]->width),
        .bottom = static_cast<float>(sprites[0]->height)
    };
}

breakout::PowerUp::~PowerUp()
{
    if (!consumed)
    {
        OnEnd();
    }
}

void breakout::PowerUp::OnBegin()
{
    powerTimer.Reset();
    active = true;
    if (internalBeginCallback) internalBeginCallback();
    if (onBeginCallback) onBeginCallback();
}

void breakout::PowerUp::OnEnd()
{
    if (internalEndCallback) internalEndCallback();
    if (onEndCallback) onEndCallback();
    consumed = true;
}

void breakout::PowerUp::Update(const float deltaTime)
{
    location += direction * (speed * deltaTime);

    if (!consumed && active && powerTimer.Elapsed() >= duration)
    {
        OnEnd();
    }
}

void breakout::PowerUp::Animate()
{
    const float frameTime = 1.f / animationSpeed;
    if (animationTimer.Elapsed() >= frameTime)
    {
        animationIndex = (++animationIndex + (int)sprites.size()) % (int)sprites.size();
        animationTimer.Reset();
    }

    Engine.Renderer().Draw(sprites[animationIndex], location);
}

breakout::PowerExtraLife::PowerExtraLife(Player& player)
{
    PopulateSprites<PowerPlayerFont>();
    type = PowerUpType::ExtraLife;
    duration = 0.0f; // Instant
    internalBeginCallback = [&]()
    {
        player.extraLives++;
    };
}

breakout::PowerSlow::PowerSlow(std::vector<Ball>& balls)
{
    PopulateSprites<PowerSlowFont>();
    type = PowerUpType::Slow;
    duration = 15.0f;
    internalBeginCallback = [&]()
    {
        for (auto& ball : balls)
        {
            ball.speed = 325.f / 2.f; // Halve the speed
        } 
    };
    internalEndCallback = [&]()
    {
        for (auto& ball : balls)
        {
            ball.speed = 325.f; // Set back to original 
        }
    };
}

breakout::PowerBreak::PowerBreak(std::vector<Ball>& balls)
{
    PopulateSprites<PowerBreakFont>();
    type = PowerUpType::Break;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);
    
    internalBeginCallback = [&]()
    {
        // Max 3 balls on the field
        if (balls.empty() || balls.size() >= 3) return;

        // Pick a random side to shoot out at 30 degrees
        float angle = dis(gen) == 0 ? -30.0f : 30.0f;

        const int createCount = 3 - static_cast<int>(balls.size());
        auto reference = balls[0]; // Get the first ball
        for (int i = 0; i < createCount; i++)
        {
            if (i == 1) angle = -angle; // the second ball must go the other way
            // Limit ball angle to 70degrees to prevent full horizontal moving balls
            float currentAngle = glm::degrees(glm::acos(glm::dot(reference.direction, glm::vec2(0.0f, 1.0f))));
            float finalAngle = glm::clamp(currentAngle + angle, -70.f, 70.f);
            
            Ball ball {};
            ball.isAttachedToPaddle = reference.isAttachedToPaddle;
            ball.location = reference.location;
            ball.direction = glm::rotate(float2{0, -1}, glm::radians(finalAngle));
            balls.push_back(ball);
        }
    };
}

breakout::PowerEnlarge::PowerEnlarge(Paddle& paddle)
{
    PopulateSprites<PowerEnlargeFont>();
    type = PowerUpType::Enlarge;
    duration = 15.f;
    ogWidth = paddle.sprites[1]->width;
    internalBeginCallback = [&]()
    {
        active = true; consumed = false;
        auto shadow = Engine.Renderer().CreateImage("assets/images/paddle_ext_shadow.png");
        auto paddleExt = Engine.Renderer().CreateImage("assets/images/paddle_ext.png");
        paddle.location.x -= (float)abs(ogWidth - paddleExt->width) / 2.f; 
        paddle.sprites = {
            shadow,
            paddleExt
        };
        paddle.bounds = {
            .left = 0.0f,
            .top = 0.0f,
            .right = static_cast<float>(paddleExt->width),
            .bottom = static_cast<float>(paddleExt->height)
        };
    };
    internalEndCallback = [&]()
    {
        auto shadow = Engine.Renderer().CreateImage("assets/images/paddle_shadow.png");
        auto paddleExt = Engine.Renderer().CreateImage("assets/images/paddle.png");
        paddle.location.x += (float)abs(ogWidth - paddleExt->width) / 2.f;
        paddle.sprites = {
            shadow,
            paddleExt
        };
        paddle.bounds = {
            .left = 0.0f,
            .top = 0.0f,
            .right = static_cast<float>(paddleExt->width),
            .bottom = static_cast<float>(paddleExt->height)
        };
    };
}
