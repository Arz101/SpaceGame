#include "CComponent.hpp"

CComponent::CComponent(SDL_Rect _rect, SDL_Color _color, SDL_Texture* _texture, SDL_Renderer* _render)
: CC_Rect(_rect), CC_Color(_color), CC_Texture(_texture), r(_render) {}

