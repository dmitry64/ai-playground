#include "field.hpp"

std::vector<Creature> Field::creatures() const
{
    return _creatures;
}

int Field::fieldHalfWidth() const
{
    return _fieldHalfWidth;
}

int Field::fieldHalfHeight() const
{
    return _fieldHalfHeight;
}

std::vector<std::vector<double> > Field::squares() const
{
    return _squares;
}

double Field::getWeightInPoint(glm::vec2 point) const
{
    assert(!isnanf(point.x));
    assert(!isnanf(point.y));
    if(std::abs(point.x)>=_fieldHalfWidth || std::abs(point.y)>=_fieldHalfHeight) {
        return 0.0;
    }

    glm::vec2 index = point + glm::vec2(_fieldHalfWidth, _fieldHalfHeight) - glm::vec2(0.5,0.5);
    glm::i32vec2 ind(std::round(index.x), std::round(index.y));
    assert(ind.x >= 0 && ind.y >= 0);
    if(_squares.size()>0) {
        assert(ind.y<_squares.size());
        auto & row = _squares[ind.y];
        assert(ind.x<row.size());
        return row[ind.x];
    }
}

glm::i32vec2 Field::getSquareIndexByPosition(glm::vec2 point)
{
    glm::vec2 index = point + glm::vec2(_fieldHalfWidth, _fieldHalfHeight) - glm::vec2(0.5,0.5);
    glm::i32vec2 ind(std::round(index.x), std::round(index.y));
    assert(ind.x >= 0 && ind.y >= 0);
    assert(ind.y<_squares.size());
    auto & row = _squares[ind.y];
    assert(ind.x<row.size());
    return ind;
}

Field::Field() : _fieldHalfWidth(15), _fieldHalfHeight(15)
{

}

void Field::init()
{
    NeuralNetParams params(0.15,0.5);
    NeuralNet net({5,6,6,3},params);

    _creatures.push_back(Creature(net,glm::vec2(2,3),glm::vec2(2,3)));
    _creatures.push_back(Creature(net,glm::vec2(-3,5),glm::vec2(5,-3)));
    _creatures.push_back(Creature(net,glm::vec2(-4,3),glm::vec2(1,3)));
    _creatures.push_back(Creature(net,glm::vec2(2,2),glm::vec2(2,7)));
    _creatures.push_back(Creature(net,glm::vec2(6,1),glm::vec2(-5,3)));
    _creatures.push_back(Creature(net,glm::vec2(1,-3),glm::vec2(-2,1)));
    _creatures.push_back(Creature(net,glm::vec2(5,-6),glm::vec2(-2,-7)));
    _creatures.push_back(Creature(net,glm::vec2(8,-6),glm::vec2(-2,-8)));
    _creatures.push_back(Creature(net,glm::vec2(-7,-3),glm::vec2(-2,-9)));

    for(int i=-_fieldHalfHeight; i<=_fieldHalfHeight; ++i) {
        SquareRow row;
        for(int j=-_fieldHalfWidth; j<=_fieldHalfWidth; ++j) {
            row.push_back(double(rand())/double(RAND_MAX));
            std::cout << "VAL:" << row.back() << "\n";
        }
        _squares.push_back(row);
    }
}

void Field::resetPositions()
{
    int width = _fieldHalfWidth * 2;
    int height = _fieldHalfHeight * 2;
    for(auto & creature : _creatures) {
        creature.setPosition(glm::vec2(rand() % width - _fieldHalfWidth, rand() % height - _fieldHalfHeight));
        glm::vec2 dir( double(rand())/double(RAND_MAX) - 0.5,double(rand())/double(RAND_MAX) - 0.5);
        while(dir.length()==0) {
            dir = glm::vec2( double(rand())/double(RAND_MAX) - 0.5,double(rand())/double(RAND_MAX) - 0.5);
        }
        creature.setDirection(glm::normalize(dir));
    }
}

void Field::resetSquares()
{
    _squares.clear();
    for(int i=-_fieldHalfHeight; i<=_fieldHalfHeight; ++i) {
        SquareRow row;
        for(int j=-_fieldHalfWidth; j<=_fieldHalfWidth; ++j) {
            row.push_back(double(rand())/double(RAND_MAX));
            std::cout << "VAL:" << row.back() << "\n";
        }
        _squares.push_back(row);
    }
}

void Field::simulatePhysics()
{
    Field copy(*this);
    for(auto & creature : _creatures) {
        creature.thinkAndMove(copy);
        auto index = getSquareIndexByPosition(creature.position());
        auto & value = _squares[index.y][index.x];
        /*if(value != 0.0) {
            value -= 0.001;
            if(value < 0 )
                value = 0.0;
        }*/
    }
}

void Field::evaluateResults()
{
    Field copy(*this);
    for(auto & creature : _creatures) {
        creature.evaluateResults(copy);
    }
    resetPositions();
    resetSquares();
}
