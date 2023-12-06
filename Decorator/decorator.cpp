#include <iostream>
#include <memory>

// Abstract component
class Text
{
public:
    virtual std::string write() = 0;
};

// Concrete component
class PlainText : public Text
{
private:
    std::string content;
public:
    PlainText(std::string content) : content(content) {}
    std::string write() override
    {
        return content;
    }
};

// Abstract decorator
class TextDecorator: public Text
{
protected:
    std::unique_ptr<Text> text;
public:
    TextDecorator(std::unique_ptr<Text> text) : text(std::move(text)) {}
    std::string write() override
    {
        return text->write();
    }
};

// Concrete decorators
class BoldDecorator : public TextDecorator
{
public:
    BoldDecorator(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}
    std::string write() override
    {
        return "\e[1m" + text->write() + "\033[0m";
    }
};

class ItalicDecorator : public TextDecorator
{
public:
    ItalicDecorator(std::unique_ptr<Text> text) : TextDecorator(std::move(text)) {}
    std::string write() override
    {
        return "\e[3m" + text->write() + "\033[0m";
    }
};

int main()
{
    std::unique_ptr<Text> text = std::make_unique<PlainText>("Hello world!");
    std::cout<<text->write()<<std::endl;

    std::unique_ptr<Text> boldText = std::make_unique<BoldDecorator>(std::make_unique<PlainText>("Hello world!"));
    std::cout<<boldText->write()<<std::endl;

    std::unique_ptr<Text> italicText = std::make_unique<ItalicDecorator>(std::make_unique<PlainText>("Hello world!"));
    std::cout<<italicText->write()<<std::endl;

    std::unique_ptr<Text> boldItalicText = std::make_unique<ItalicDecorator>(std::make_unique<BoldDecorator>(std::make_unique<PlainText>("Hello world!"))); 
    std::cout<<boldItalicText->write()<<std::endl;

    return 0;
}