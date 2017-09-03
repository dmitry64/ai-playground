#include "creature.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <field.hpp>

glm::vec2 Creature::position() const
{
    return _position;
}

glm::vec2 Creature::direction() const
{
    return _direction;
}

float Creature::speed() const
{
    return _speed;
}

std::vector<double> Creature::getDirectionWeights(const Field &currentFieldState)
{
    std::vector<double> result;
    const auto & directions = getDirections();
    for(auto direction : directions) {
        result.push_back(currentFieldState.getWeightInPoint(_position + direction));
    }
    return result;
}

std::vector<glm::vec2> Creature::getDirections() const
{
    std::vector<glm::vec2> result;
    const glm::vec2 forward = _direction;
    result.push_back(forward);

    assert(!isnanf(forward.x));
    assert(!isnanf(forward.y));
    for(int i=1; i<4; ++i) {
        glm::vec2 vect = glm::rotate(forward,(glm::pi<float>()/2.0f)*i);
        assert(!isnanf(vect.x));
        assert(!isnanf(vect.y));
        result.push_back(vect);
    }
    return result;
}

void Creature::setPosition(const glm::vec2 &position)
{
    _position = position;
}

void Creature::setDirection(const glm::vec2 &direction)
{
    assert(!isnanf(direction.x));
    assert(!isnanf(direction.y));
    _direction = direction;
}

void Creature::setSpeed(float speed)
{
    _speed = speed;
}

Creature::Creature(NeuralNet &net, glm::vec2 pos, glm::vec2 dir) : _neuralNet(net), _position(pos), _direction(glm::normalize(dir))
{
    assert(!isnanf(_direction.x));
    assert(!isnanf(_direction.y));
    _speed = 0.001;
}

void Creature::thinkAndMove(const Field &currentFieldState)
{
    auto inputVals = getDirectionWeights(currentFieldState);
    inputVals.push_back(currentFieldState.getWeightInPoint(_position));
    _neuralNet.feedForward(inputVals);


    NeuralNet::OutputValues ret;
    _neuralNet.getResults(ret);
    _direction = glm::normalize(glm::vec2(ret[0],ret[1]));
    _speed = std::abs(ret[2]/100.0);
    _position += std::abs(_speed) * _direction;
    if(_position.x > currentFieldState.fieldHalfWidth())
        _position.x = currentFieldState.fieldHalfWidth() - 0.00001;
    if(_position.x < -currentFieldState.fieldHalfWidth())
        _position.x = -currentFieldState.fieldHalfWidth() + 0.00001;

    if(_position.y > currentFieldState.fieldHalfHeight())
        _position.y = currentFieldState.fieldHalfHeight() - 0.00001;
    if(_position.y < -currentFieldState.fieldHalfHeight())
        _position.y = -currentFieldState.fieldHalfHeight() + 0.00001;


    /*NeuralNet::InputValues input;
    input.push_back((_position.x + 15.0) / 30.0);
    input.push_back((_position.y + 15.0) / 30.0);
    input.push_back(std::abs(_speed));
    _neuralNet.feedForward(input);

    NeuralNet::OutputValues ret;
    _neuralNet.getResults(ret);
    _direction = glm::normalize(glm::vec2(ret.at(0),ret.at(1)));
    _speed = std::abs(ret.at(2)/100.0);

    _position += std::abs(_speed) * _direction;
    if(std::abs(_position.x) > currentFieldState.fieldHalfWidth())
        _position.x = currentFieldState.fieldHalfWidth();
    if(std::abs(_position.y) > currentFieldState.fieldHalfHeight())
        _position.y = currentFieldState.fieldHalfHeight();
    */
}

void Creature::evaluateResults(const Field &currentFieldState)
{
 /*   double val = currentFieldState.getWeightInPoint(_position);
    NeuralNet::OutputValues target;
    //std::cout << "X:" << _position.x << " Y:" << _position.y << "RET:" << ret[0] << " " << ret[1] << " " << ret[2] << " VAL:" << val << "\n";

    if(val > 0.5) {
        double reward = 1;
        target.push_back( reward );
        target.push_back( reward );
        target.push_back( reward );
        for(int i = 0; i<(val * 100); ++i) {
            _neuralNet.backProp(target);
        }
    } else {
        for(int i = 0; i<((1.0 - val)*100); ++i) {
            target.clear();
            target.push_back( (double(rand())/double(RAND_MAX) - 0.5)*2.0 );
            target.push_back( (double(rand())/double(RAND_MAX) - 0.5)*2.0 );
            target.push_back( (double(rand())/double(RAND_MAX) - 0.5)*2.0 );
            _neuralNet.backProp(target);
        }
    }*/

    /*NeuralNet::OutputValues target;
    double val = currentFieldState.getWeightInPoint(_position);
    target.push_back( val );
    target.push_back( val );
    target.push_back( val );
    _neuralNet.backProp(target);*/
    /*glm::vec2 targ(0,0);
    glm::vec2 rightDirection = glm::normalize(targ - _position);

    NeuralNet::OutputValues target;
    target.push_back( rightDirection.x );
    target.push_back( rightDirection.y );
    std::cout << "pos" << _position.x << " " << _position.y << " angle:" << glm::angle(rightDirection,_direction) << "\n";
    float angle = std::abs(glm::angle(rightDirection,_direction));
    float nullAngle = (angle == 0.0f) ? 00000000001 : angle;
    target.push_back( 3.15 / nullAngle ); // 1.0 / glm::angle(rightDirection,_direction)

    _neuralNet.backProp(target);*/
}
