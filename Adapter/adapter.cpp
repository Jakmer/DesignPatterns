#include <iostream>
#include <memory>

/**  Suppose you have a console with HDMI cable and you need to plugin to VGA monitor
 *   You will need some kind of adapter to do this
 */

// 1. Create classes with different interfaces
class HDMIsource
{
    std::string output;

public:
    HDMIsource()
    {
        output = "This is HDMI display: ";
    }

    virtual void hdmiDisplay(std::string &stream, int type)
    {
        std::cout << output << stream << std::endl;
    }
};

class AVGsource
{
    std::string output;

public:
    AVGsource()
    {
        output = "This is VGA display: ";
    }
    virtual void vgaDisplay(std::string &stream, int type)
    {
        std::cout << output << stream << std::endl;
    }
};

class DisplayPortSource
{
    std::string output;

public: 
    DisplayPortSource()
    {
        output = "This is DisplayPort display: ";
    }
    virtual void displayPortDisplay(std::string &stream, int type)
    {
        std::cout << output << stream << std::endl;
    }
};


// 2. Create adapter class which will inherit from every classes
class SourceAdapter : public HDMIsource, public AVGsource, public DisplayPortSource
{
public:
    virtual void hdmiDisplay(std::string &stream, int type) override
    {
        switch (type)
        {
        case 1:
            vgaDisplay(stream, type);
            break;
        case 2:
            displayPortDisplay(stream, type);
            break;
        default:
            break;
        }
    }
};

int main()
{
    std::string stream = "some digits";
    std::unique_ptr<HDMIsource> source = std::make_unique<SourceAdapter>();

    source->hdmiDisplay(stream,1);  // This is VGA display: some digits
    source->hdmiDisplay(stream,2);  // This is DisplayPort display: some digits

    // 3. Now you can use HDMI interface to display on VGA monitor

    return 0;
}
