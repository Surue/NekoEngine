#pragma once

#include <graphics/graphics.h>
#include <graphics/color.h>
#include <SFML/Graphics/RenderTarget.hpp>

namespace neko
{
template<>
inline Color::Color(const sf::Color& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

template<>
inline Color::operator sf::Color() const
{
    return sf::Color(r,g,b,a);
}

}

namespace neko::sfml
{
struct SfmlRenderTarget : public RenderTarget
{
	sf::RenderTarget* sfmlRenderTarget;
};
class SfmlRenderCommand : public RenderCommand
{
public:
    const sf::RenderStates& GetStates() const;
    void SetStates(const sf::RenderStates& states);
    const sf::Drawable* GetDrawable() const;
    void SetDrawable(sf::Drawable* drawable);
	void Render(RenderTarget* renderTarget) override;
private:
    sf::Drawable* drawable_ = nullptr;
    sf::RenderStates states_ = sf::RenderStates::Default;
};

}