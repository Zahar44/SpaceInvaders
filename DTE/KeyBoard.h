#pragma once

class KeyBoard {
public:
	struct State {
		bool isDown = false;
		bool changed = false;
	};
	
	enum Key {
		LEFT,
		RIGHT,
		UP,
		SPACE,

		END // must be last
	};

	KeyBoard() {}

	bool IsDown(Key key) {
		return states[key].isDown;
	}
	bool IsChanged(Key key) {
		return states[key].changed;
	}
	bool IsDownOnce(Key key) {
		return states[key].isDown && states[key].changed;
	}

	void Update() {
		for (size_t i = 0; i < Key::END; i++)
		{
			states[i].changed = false;
		}
	}

	void Update(Key key, LPARAM lParam) {
		bool isDown = (lParam & (1 << 31)) == 0;
		states[key].changed = isDown != lastStates[key].isDown;
		states[key].isDown = isDown;

		lastStates[key] = states[key];
	}

	Key getKey(WPARAM& wParam) {
		switch (wParam)
		{
		case VK_LEFT:
			return Key::LEFT;
			break;
		case VK_RIGHT:
			return Key::RIGHT;
			break;
		case VK_UP:
			return Key::UP;
			break;
		case VK_SPACE:
			return Key::SPACE;
			break;
		default:
			return Key::END;
			break;
		}
 	}
private:
	State states[Key::END];
	State lastStates[Key::END];
};
