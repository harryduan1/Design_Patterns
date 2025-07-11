#include <iostream>
#include <string>
#include <memory>

// === 抽象接口 ===
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// === 真实主题：真正加载图像 ===
class RealImage : public Image {
private:
    std::string filename;
public:
    RealImage(const std::string& file) : filename(file) {
        loadFromDisk();
    }

    void display() override {
        std::cout << "Displaying image: " << filename << "\n";
    }

private:
    void loadFromDisk() {
        std::cout << "Loading image from disk: " << filename << "\n";
    }
};

// === 代理类：延迟加载图像 ===
class ImageProxy : public Image {
private:
    std::string filename;
    std::shared_ptr<RealImage> realImage;

public:
    ImageProxy(const std::string& file) : filename(file), realImage(nullptr) {}

    void display() override {
        if (!realImage) {
            realImage = std::make_shared<RealImage>(filename);
        }
        realImage->display();
    }
};

// === 客户端测试 ===
int main() {
    std::shared_ptr<Image> image = std::make_shared<ImageProxy>("cat_photo.jpg");

    std::cout << "Image created, not loaded yet...\n";

    std::cout << "Calling display...\n";
    image->display();  // 第一次显示，会加载图像

    std::cout << "Calling display again...\n";
    image->display();  // 第二次显示，不再加载图像

    return 0;
}

// 输出结果
/*
Image created, not loaded yet...
Calling display...
Loading image from disk: cat_photo.jpg
Displaying image: cat_photo.jpg
Calling display again...
Displaying image: cat_photo.jpg
*/

/*
定义：代理模式通过引入一个代理类来控制对真实对象的访问，通常用于延迟加载、权限控制或日志记录等场景。
代理类在客户端和真实对象之间起到中介作用，客户端只需要与代理类交互，而不需要直接与真实对象交互。
这种模式可以提高性能（如延迟加载）、增强安全性（如权限控制）或增加功能（如日志记录）。
代理模式的核心在于代理类和真实对象都实现了相同的接口，这样客户端可以透明地使用代理类而不需要关心其背后的实现细节。
*/
