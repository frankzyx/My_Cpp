#include <iostream>
#include <string>
#include <cstddef>

class Screen {
friend class Window_mgr;
public:
	typedef std::string::size_type pos;		// type must be defined before use

	Screen() = default;
	Screen(pos ht, pos wd): height(ht), width(wd) {}
	Screen(pos ht, pos wd, char c): height(ht), width(wd), 
									contents(ht*wd, c) {}

	char get() const {
		return contents[cursor];
	}

	char get(pos ht, pos wd) const {	// implicitly inline, b/c defined in class
		pos row = ht * width;
		return contents[row + wd];
	}


	Screen &set(char);
	Screen &set(pos, pos, char);

	Screen &move(pos r, pos c);

	void some_member() const;

	// display functions based on "const" or not
	Screen &display(std::ostream &os) { do_display(os); return *this; }
	const Screen &display(std::ostream &os) const { do_display(os); return *this; }


private:
	// mutable member is never constant
	mutable std::size_t access_ctr;

	pos cursor = 0;		// 1D position
	pos height = 0, width = 0;		// 2D coordinate
	std::string contents;

	void do_display(std::ostream &os) const { os << contents; }
};



// ===========================================================
// function definitions
inline Screen &Screen::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline Screen &Screen::set(char ch) {
	contents[cursor] = ch;
	return *this;
}

inline Screen &Screen::set(pos r, pos c, char ch) {
	contents[r * width + c] = ch;
	return *this;
}

void Screen::some_member() const {
	++access_ctr;
}