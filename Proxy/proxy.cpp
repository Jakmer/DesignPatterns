#include <iostream>
#include <memory>


/**
 * Abstract object
*/ 
class Image
{
public:
    virtual void display() const = 0;
};

/**
 * RealImage is object that is probably high-operation cost 
*/
class RealImage : public Image
{
private:
    std::string image_content;

public:
    RealImage(std::string &image_content):image_content("RealImage: "+image_content)
    {
    }

    virtual void display() const override
    {
        std::cout<<image_content<<"\n";
    }
};

/**
 *  ProxyImage is object that is low-operation cost
 * 
*/

class ProxyImage : public Image
{
private:
    mutable std::unique_ptr<RealImage> real_image;
    mutable std::string image_content;
public:
    ProxyImage(std::string &image_content):image_content("Proxy: "+image_content)
    {
    }

    virtual void display() const override
    {
        if(!real_image)
        {
            real_image = std::make_unique<RealImage>(image_content);
        }
        real_image->display();
    }
    
};

void client(Image &image)
{
    image.display();
}

int main()
{
    std::string image_content = "Image content";
    
    RealImage real_image(image_content);
    client(real_image);     // Display RealImage: Image content
    
    /**
     * Clieent uses ProxyImage instead of RealImage
    */

    ProxyImage proxy_image(image_content);
    client(proxy_image);    // Display RealImage: Proxy: Image content


    return 0;
}


