#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <creature.hpp>
#include <glm/glm.hpp>

class Field
{
    using Square = double;
    using SquareRow = std::vector<Square>;
    using Squares = std::vector<SquareRow>;
    int _fieldHalfWidth;
    int _fieldHalfHeight;
    std::vector<Creature> _creatures;
    std::vector<std::vector<double>> _squares;
public:

    Field();
    void init();
    void resetPositions();
    void resetSquares();

    std::vector<Creature> creatures() const;
    void simulatePhysics();
    void evaluateResults();
    int fieldHalfWidth() const;
    int fieldHalfHeight() const;
    std::vector<std::vector<double> > squares() const;
    double getWeightInPoint(glm::vec2 point) const;
    glm::i32vec2 getSquareIndexByPosition(glm::vec2 point);
};

#endif // FIELD_HPP
