# Set source.
# Joel Anttila 2014

set(STUDIOWINDOW src/StudioWindow.h src/StudioWindow.cpp ui/StudioWindow.ui)

# Wizard component to list all the wizards?
set(NPRJWIZ src/NewProjectWizard.h src/NewProjectWizard.cpp)

# Project file format.
set(PRJSRC src/Project.h src/Project.cpp)
set(SUBSRC src/Subtitle.h src/Subtitle.cpp)
set(FILEFORMAT ${PRJSRC} ${SUBSRC})


set(SRC_LIST 
	src/Main.cpp
	${STUDIOWINDOW}
        ${NPRJWIZ}
        ${FILEFORMAT}
	PARENT_SCOPE)
