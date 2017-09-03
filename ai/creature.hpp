#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <simpleneuralnet.hpp>

#include <glm/vec2.hpp>

class Field;

class Creature
{
    NeuralNet _neuralNet;
    glm::vec2 _position;
    glm::vec2 _direction;
    float _speed;
public:
    Creature(NeuralNet & net, glm::vec2 pos, glm::vec2 dir);
    void thinkAndMove(const Field & currentFieldState);
    void evaluateResults(const Field & currentFieldState);
    glm::vec2 position() const;
    glm::vec2 direction() const;
    float speed() const;
    std::vector<double> getDirectionWeights(const Field & currentFieldState);
    std::vector<glm::vec2> getDirections() const;

    void setPosition(const glm::vec2 &position);
    void setDirection(const glm::vec2 &direction);
    void setSpeed(float speed);
};

#endif // CREATURE_HPP
