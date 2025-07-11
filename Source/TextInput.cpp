#include "pch.h"
#include "TextInput.h"

TextInput::TextInput(SDL_Renderer* ren, Vec2 pos, TTF_Font* _font, std::string _text, SDL_Color _color1, SDL_Color _color2, SDL_Event* ev)
	: Button(ren, ev, pos, _font, _text, _color1, _color2)	{
	m_inputText = _text;
	m_inputAllowed = false;
	m_onlyNumbers = false;
	m_clicked = false;
	m_negAllowed = true;
}
TextInput::TextInput(const TextInput& obj) : Button(obj.m_ren, obj.m_ev, Vec2(obj.m_dest.x, obj.m_dest.y), obj.m_font, obj.m_text, obj.m_normalColor, obj.m_highlightColor), 
	m_inputAllowed(obj.m_inputAllowed), m_onlyNumbers(obj.m_onlyNumbers), m_inputText(obj.m_inputText), m_negAllowed(obj.m_negAllowed) {
	m_ev = obj.m_ev;
}
TextInput::~TextInput() {
	
}
TextInput& TextInput::operator=(const TextInput& obj) {
	m_ren = obj.m_ren;
	m_ev = obj.m_ev;
	m_dest = obj.m_dest;
	m_font = obj.m_font;
	m_text = obj.m_text;
	m_permaText = obj.m_permaText;
	m_normalColor = obj.m_normalColor;
	m_highlightColor = obj.m_highlightColor;
	m_color = obj.m_color;

	m_inputText = obj.m_inputText;
	m_inputAllowed = obj.m_inputAllowed;
	m_onlyNumbers = obj.m_onlyNumbers;
	m_clicked = obj.m_clicked;
	m_negAllowed = obj.m_negAllowed;

	m_sizePercent = obj.m_sizePercent;
	m_origWidth = obj.m_origWidth;
	m_origHeight = obj.m_origHeight;

	m_tex = obj.m_tex;

	Text::ChangeText(m_text);

	return *this;
}
void TextInput::StartInput() {
	m_inputAllowed = true;
	SDL_StartTextInput();
	LOGln("Input started");
}
void TextInput::StopInput() {
	m_inputAllowed = false;
	SDL_StopTextInput();
	LOGln("Input ended");
}
void TextInput::AcceptNumbers(bool yesOrNo) {
	m_onlyNumbers = yesOrNo;
	if (yesOrNo == true)
		m_inputText = '0';
}
void TextInput::AcceptNegativeNumbers(bool yesOrno) {
	if (yesOrno && !m_onlyNumbers) {
		AcceptNumbers(yesOrno);
	}
	m_negAllowed = yesOrno;

}
void TextInput::Update() {
	Button::Update();
}
void TextInput::Render() {
	Button::Render();
}
void TextInput::Input() {
	if (CheckMouseClick()) {
		if (!m_clicked) {
			m_clicked = true;
			StartInput();
		}
		else {
			m_clicked = false;
			StopInput();
		}
	}
	if ((CheckMouseClickOutside() || IsOver()) && m_clicked == true) {
		m_clicked = false;
		StopInput();
	}
	if (m_inputAllowed) {
		if (m_ev->type == SDL_TEXTINPUT || m_ev->type == SDL_KEYDOWN) {
			if (m_ev->key.keysym.sym == SDLK_RETURN) {
				StopInput(); 
			}
			else if (m_ev->type == SDL_KEYDOWN && m_ev->key.keysym.sym == SDLK_BACKSPACE && m_inputText.length() > 0) {
				m_inputText.pop_back();
				Text::ChangeText(m_inputText);
			}
			else if (!m_onlyNumbers && m_ev->type == SDL_TEXTINPUT) {
				m_inputText += m_ev->text.text;
				Text::ChangeText(m_inputText);
			}
			else if (m_onlyNumbers && m_ev->type == SDL_TEXTINPUT) {
				char num = *m_ev->text.text;
				if (m_negAllowed && m_inputText.length() == 0) {
					if (num == '-') {
						m_inputText = "-";
					}
				}
				if (num == '0' || num == '1' || num == '2' || num == '3' || num == '4' ||
					num == '5' || num == '6' || num == '7' || num == '8' || num == '9') {
					m_inputText += num;
				}

				Text::ChangeText(m_inputText);

			}
		}
	}
	else {
		if (m_inputText.length() == 0) {
			m_inputText = '0';
			Text::ChangeText(m_inputText);
		}
	}
}
int TextInput::GetNum() {
	if (m_onlyNumbers && m_inputText.length() > 0) {
		return std::stoi(m_inputText);
	}
	return -1;
}
bool TextInput::HasInputEnded() {
	return !m_inputAllowed;
}
bool TextInput::IsOver() {
	return !m_inputAllowed;

}
void TextInput::ChangeText(std::string _text) {
	if (m_inputText != _text) {
		m_inputText = _text;
		Text::ChangeText(m_inputText);
	}
}
void TextInput::ChangeText(int num) {
	std::string _text = std::to_string(num);
	if (m_inputText != _text) {
		m_inputText = _text;
		Text::ChangeText(_text);
	}
}