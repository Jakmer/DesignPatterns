#include <iostream>
#include <memory>

// Product class

class Robot
{
    std::string type;
    std::string head;
    std::string torso;
    std::string arms;
    std::string legs;

public:
    Robot(std::string type):type(type)
    {
    }
    void setHead(std::string head)
    {
        this->head = head;
    }
    void setTorso(std::string torso)
    {
        this->torso = torso;
    }
    void setArms(std::string arms)
    {
        this->arms = arms;
    }
    void setLegs(std::string legs)
    {
        this->legs = legs;
    }
    void show()
    {
        std::cout << "Robot type: " << type << std::endl;
        std::cout << "Robot head: " << head << std::endl;
        std::cout << "Robot torso: " << torso << std::endl;
        std::cout << "Robot arms: " << arms << std::endl;
        std::cout << "Robot legs: " << legs << std::endl;
    }
};

// Abstract builder class
class RobotBuilder
{   
    protected:
        std::unique_ptr<Robot> robot;
    public:
        RobotBuilder(std::string type):robot(new Robot(type))
        {
        }
        virtual void buildHead() = 0;
        virtual void buildTorso() = 0;
        virtual void buildArms() = 0;
        virtual void buildLegs() = 0;
        std::unique_ptr<Robot> getRobot()
        {
            return std::move(robot);
        }
        virtual ~RobotBuilder() = default;
};

// Concrete builder class
class TankRobotBuilder : public RobotBuilder
{
public:
    TankRobotBuilder():RobotBuilder("Tank Robot")
    {
    }
    void buildHead() override
    {
        robot->setHead("Tank Robot Head");
    }
    void buildTorso() override
    {
        robot->setTorso("Tank Robot Torso");
    }
    void buildArms() override
    {
        robot->setArms("Tank Robot Arms");
    }
    void buildLegs() override
    {
        robot->setLegs("Tank Robot Legs");
    }
};

// Concrete builder class
class NinjaRobotBuilder : public RobotBuilder
{
public:
    NinjaRobotBuilder():RobotBuilder("Ninja Robot")
    {
    }
    void buildHead() override
    {
        robot->setHead("Ninja Robot Head");
    }
    void buildTorso() override
    {
        robot->setTorso("Ninja Robot Torso");
    }
    void buildArms() override
    {
        robot->setArms("Ninja Robot Arms");
    }
    void buildLegs() override
    {
        robot->setLegs("Ninja Robot Legs");
    }
};

// Director class
class Director
{
    std::unique_ptr<RobotBuilder> robotBuilder;
public:
    void setRobotBuilder(std::unique_ptr<RobotBuilder> robotBuilder)
    {
        this->robotBuilder = std::move(robotBuilder);
    }
    std::unique_ptr<Robot> getRobot()
    {
        return std::move(robotBuilder->getRobot());
    }
    void constructRobot()
    {
        robotBuilder->buildHead();
        robotBuilder->buildTorso();
        robotBuilder->buildArms();
        robotBuilder->buildLegs();
    }
};

int main()
{
    Director director;
    
    std::unique_ptr<RobotBuilder> tankRobotBuilder = std::make_unique<TankRobotBuilder>();
    std::unique_ptr<RobotBuilder> ninjaRobotBuilder = std::make_unique<NinjaRobotBuilder>();

    director.setRobotBuilder(std::move(tankRobotBuilder));
    director.constructRobot();
    std::unique_ptr<Robot> tankRobot = director.getRobot();
    tankRobot->show();

    director.setRobotBuilder(std::move(ninjaRobotBuilder));
    director.constructRobot();
    std::unique_ptr<Robot> ninjaRobot = director.getRobot();
    ninjaRobot->show();

    return 0;
}