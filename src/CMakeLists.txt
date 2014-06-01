# Set source.
# Joel Anttila 2014

set(STUDIOWINDOW src/StudioWindow.h src/StudioWindow.cpp ui/StudioWindow.ui)

set(SRC_LIST 
	src/Main.cpp
	${STUDIOWINDOW}
	PARENT_SCOPE)
