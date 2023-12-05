#include <iostream>
#include <memory>

/**  Suppose you have consol with HDMI cable and you need to plugin to VGA monitor
 *   You will need some kind of adapter to do this
 */

// 1. Create two classes with different interfaces
class HDMIsource
{
    std::string output;

public:
    HDMIsource()
    {
        output = "This is HDMI display: ";
    }

    virtual void hdmiDisplay(std::string &stream)
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
    virtual void vgaDisplay(std::string &stream)
    {
        std::cout << output << stream << std::endl;
    }
};


// 2. Create adapter class which will inherit from both classes
class SourceAdapter : public HDMIsource, public AVGsource
{
public:
    virtual void hdmiDisplay(std::string &stream)
    {
        vgaDisplay(stream);
    }
};

int main()
{
    std::string stream = "some digits";
    std::unique_ptr<HDMIsource> source = std::make_unique<SourceAdapter>();

    source->hdmiDisplay(stream);

    // 3. Now you can use HDMI interface to display on VGA monitor

    return 0;
}
