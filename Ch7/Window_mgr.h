#include "Screen.h"
#include <vector>
#include <string>

class Window_mgr {
public:
	// location id for each screen on the window
	using SceenIndex = std::vector<Screen>::size_type;
	// reset the Screen at the position
	void clear(SceenIndex);
private:
	std::vector<Screen> screens{Screen(24, 80, ' ')};
};