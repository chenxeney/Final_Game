#include <algorithm>
#include <string>
#include "ImageButton.hpp"
#include "Point.hpp"
#include "Slider.hpp"
#include "Collider.hpp"
#include "Resources.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "iostream"
using namespace Engine;
using namespace std;
int i = 0;
Slider::Slider(float x, float y, float w, float h) :
	ImageButton("stage-select/slider.png", "stage-select/slider-blue.png", x, y),
	Bar("stage-select/bar.png", x, y, w, h),
	End1("stage-select/end.png", x, y + h / 2, 0, 0, 0.5, 0.5),
	End2("stage-select/end.png", x + w, y + h / 2, 0, 0, 0.5, 0.5){
        Position.x += w;
        Position.y += h / 2;
        Anchor = Engine::Point(0.5, 0.5);
    }
// TODO 4 (0/6): Finish the 6 functions below and ensure it can control both BGM and SFX volume.
//               The slider shouldn't be dragged outside the bar, and you should also keep the mouse-in / mouse-out effect.
void Slider::Draw() const {
    Bar.Draw();
    End1.Draw();
    End2.Draw();
    ImageButton::Draw();
	// TODO 4 (1/6): Draw all components.
}
void Slider::SetOnValueChangedCallback(std::function<void(float value)> onValueChangedCallback) {
	// TODO 4 (2/6): Set the function pointer. Can imitate ImageButton's 'SetOnClickCallback'.
	OnValueChangedCallback = onValueChangedCallback;
}
void Slider::SetValue(float value){
	// TODO 4 (3/6): Call 'OnValueChangedCallback' when value changed. Can imitate ImageButton's 'OnClickCallback'.
	//               Also move the slider along the bar, to the corresponding position.
    if(Down == true){
        float x = 190*value+745;
        if(x <= 935 && x >= 745){
            Position.x = x;
            OnValueChangedCallback(value);
        }
    }
}
void Slider::OnMouseDown(int button, int mx, int my){
	// TODO 4 (4/6): Set 'Down' to true if mouse is in the slider.
	cout << mx << " "<< my << endl;
    if (mx >= 745 && mx <= 935 && my <= Position.y+10 && my >= Position.y-10){
        Down = true;
        cout << "OnMouseDown" << endl;
    }
}
void Slider::OnMouseUp(int button, int mx, int my){
	// TODO 4 (5/6): Set 'Down' to false.
	Down = false;
}
void Slider::OnMouseMove(int mx, int my){
	// TODO 4 (6/6): Clamp the coordinates and calculate the value. Call 'SetValue' when you're done.
	mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
    if (!mouseIn || !Enabled) bmp = imgOut;
    else bmp = this->imgIn;
	float v = (mx-745)/190.0;
    SetValue(v);
}
