# Stable Fast 2D
C++ code-first ECS-driven game engine supporting multiple development paradigms and allows you to choose the amount of control you want over your program

### Multiple approaches
You decide wether to initalize and manage all engine components yourself or use a more user-friendly `Application/Layer` system

#### GLM - Stable Fast 2D uses [glm](https://github.com/g-truc/glm) as its main math library 

##### Examples of hello world application
#### Approach 1 (lowlevel)
```cpp
#include "sf2d.hpp"
using namespace s2f;

int main() 
{
  EngineInfo engineInfo{};
  engineInfo.windowInfo.size = { 1000, 700 };
  engineInfo.windowInfo.title = "Sandbox";

  Engine engine(engineInfo);
  Renderer& renderer = engine.renderer();
  Camera camera;

  // Position, rotation, scale and color of the square
  auto transform = makeTransform({ 0.f }, { 0.f }, { 1.f });
  glm::vec4 color { 1.f, 0.f, 0.f, 1.f };

  while (engine.runs()) 
  {
    engine.startFrame();
    renderer.setProjview(camera.projview());
    renderer.begin();
    renderer.drawQuad(transform, color);
    renderer.end();
    engine.endFrame();
  }
  return 0;
}

```
Here is an example of a program that uses internal Renderer directly to draw a red quad with position at [0, 0, 0], rotation of [0, 0, 0] and scale of [1, 1] (values come from ```makeTransform``` function that takes position, rotation, scale and outputs a transform matrix)<br/>
We also create a camera object and feed its internally calculated projview matrix into the renderer

Below is an example of the same program but without lowlevel details using ```Application/Layer```

#### Approach 2 (Application instance)
```cpp
#include "sf2d.hpp"
using namespace s2f;

class GameLayer : public Layer
{
public:
  void start() override
  {
    useCamera(mCamera);
  }

  void onUpdate(f32 dt) override {}
  void onRender() override
  {
    // Transform{} creates a 0 position 0 rotation 1 scale transform same as in previous example
    // .matrix() internally calls makeTransform() to get glm::mat4
    mRenderer.drawQuad(Transform{}.matrix(), { 1.f, 0.f, 0.f, 1.f });
  }

private:
  Camera mCamera;
}

int main()
{
  EngineInfo engineInfo{};
  engineInfo.windowInfo.size = { 1000, 700 };
  engineInfo.windowInfo.title = "Sandbox";

  Application app(engineInfo);
  app.pushLayer<GameLayer>();
  app.mainLoop();
  return 0;
}
```
Here after filling out ```EngineInfo``` initialization struct we create ```Application``` instance instead of ```Engine``` that manages most lowlevel code internally<br/>
```Layer``` represents a renderable area with its own scene, objects, camera and logic
Layers can be rendered on top of eachother, pushed on top and removed, in terms of data structures layers in Appplication behave like a stack


### Entity Component System (ECS  )
ECS is a huge part of the engine and basically all complex features run on it, its the one oppinionated part of the engine that should be used in almost any project (especially more complex than drawing a red square)

The core architecture of Stable Fast 2D centers on an ECS driven by `Scene`. Game state is organized into **Components** attached to lightweight **Entities**, while logic is executed by **Systems**.

#### 1. Creating Entities & Adding Components
Entities are created through a `Scene`. Components can be attached and configured directly:

```cpp
Scene scene;

Entity sprite = scene.newEntity();
sprite.get<Transform>()->position = glm::vec2(-1.f, 0.f);
sprite.get<Transform>()->scale = glm::vec2(0.2f);

sprite.add<Sprite>(ASSETS_PATH / "textures" / "container.jpg");
sprite.add<Collider>(glm::vec2(0.2f));

auto& rb = *sprite.add<Rigidbody>(2.f, 1.f);
rb.addForceX(200.f);
rb.resolveCollisions = true;
```

#### 2. Writing & Querying Systems
Systems are functions that iterate over components or entities using `queryComponents` or `queryEntities`:

```cpp
// Query specific components directly
void gravitySystem(const std::vector<Entity>& entities, f32 fixedDT)
{
    for (auto&& [rb] : queryComponents<Rigidbody>(entities))
    {
        if (rb.massInverse == 0.f) continue;
        rb.addForceY(rb.mass * -1.f);
    }
}

// Query entities with multiple matching components
void animationSystem(const std::vector<Entity>& entities, f32 dt)
{
    for (auto [entity, animator, _] : queryEntities<SpriteAnimator, Sprite>(entities))
    {
        animator.playAnimation("attack");
    }
}
```

#### 3. Registering & Running Systems
Systems are registered to the `Scene` and executed during standard updates or fixed-timestep ticks:

```cpp
// Register systems
scene.addSystem(animationSystem);
scene.addFixedSystem(gravitySystem);

// Execution loop (inside main loop or Layer)
scene.update(dt);       // Updates variable-timestep systems
scene.tick(fixedDt);    // Updates fixed-timestep systems (physics/logic)
```

#### 4. Automated Scene Rendering (`SceneRenderer`)
Instead of manually drawing every visual component, `SceneRenderer` binds to a `Scene` and `Renderer` to automatically process and draw entities (e.g., those with `Sprite` or particle components).

```cpp
// Low-level usage
SceneRenderer sceneRenderer(scene, renderer);

// Inside render loop
renderer.begin();
sceneRenderer.render(); // Automatically draws all renderable entities in scene
renderer.end();

// Application / Layer usage (mSceneRenderer is built-in)
void GameLayer::onRender() override
{
    mSceneRenderer.render();
}
```
