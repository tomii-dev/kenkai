#include "UIElement.hpp"
#include <string>

enum ButtonSize { small, medium, big, chonky };

class Button : public UIElement{
    std::string m_text;
    ButtonSize m_size;
    void Setup();
public:
    Button();
    Button(const std::string& text, ButtonSize size);
    Button(ButtonSize size);
    void Update() override;
};