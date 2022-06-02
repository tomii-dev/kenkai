#include "UIElement.hpp"
#include <string>

class Button : public UIElement{
    std::string m_text;
    void Setup();
public:
    Button();
    Button(const std::string& text, float sizeX, float sizeY);
    Button(float sizeX, float sizeY);
    void Update() override;
};