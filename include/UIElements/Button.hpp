#include "UIElement.hpp"
#include <string>

class Button : public UIElement{
    std::string m_text;
    bool m_mousePressed;
    void Setup();
public:
    Button();
    Button(const std::string& text, float sizeX, float sizeY);
    Button(float sizeX, float sizeY);
    void Update() override;
};