#include "Sandbox.hpp"
#include "PlayerController.hpp"

void Sandbox::start()
{
    setWidth(800);
    setHeight(600);
    setTitle("Sandbox");

    Scene scene;
    setActiveScene(scene);

    auto player = activeScene->createEntity();

    std::shared_ptr<PlayerController> controller = std::make_shared<PlayerController>(player, activeScene->getRegistry());
    activeScene->addComponent<Transform>(player, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 1.0f));
    activeScene->addComponent<Sprite>(player);
    activeScene->addComponent<Script>(player, controller);

    int width = 400;
    int height = 300;

    float frequency = 0.1f;
    float amplitude = 1.0f;
    int octaves = 7;

    float lacunarity = 2.0f;
    float persistence = 0.5f;

    float threshold = 0.5f;

    std::vector<std::vector<float> > mapValues = std::vector<std::vector<float> >(width, std::vector<float>(height));

    PerlinNoise noiseGenerator(Random::randomIntInRange(0, 100));

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            mapValues[i][j] = (noiseGenerator.noise(i / 10.0f, j / 10.0f, 0.0f, frequency, amplitude, octaves, lacunarity, persistence));
            auto tile = activeScene->createEntity();

            printf("%f\n", mapValues[i][j]);

            activeScene->addComponent<Sprite>(tile, glm::vec4(mapValues[i][j], mapValues[i][j] + 1.0f, mapValues[i][j], 0.55f));

            if (mapValues[i][j] < threshold)
            {
            activeScene->addComponent<Sprite>(tile, glm::vec4(mapValues[i][j], mapValues[i][j], mapValues[i][j] + 1.0f, 1.0f));
            }
            activeScene->addComponent<Transform>(tile, glm::vec3(i * 2.0f, j * 2.0f, 0.0f), glm::vec3(2.0f, 2.0f, 0.0f));
        }
    }
}

int main() 
{
    Sandbox game;
    Application engine(game);
    engine.start();
    return 0;
}