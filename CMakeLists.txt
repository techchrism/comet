cmake_minimum_required(VERSION 3.13)
project(Comet)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(Comet main.cpp internal/LinkedList.h internal/LinkedListNode.h gui/elements/components/InputHandler.h gui/elements/components/GuiFrame.h gui/elements/components/GuiFrame.cpp internal/Options.h internal/OptionsManager.cpp internal/OptionsManager.h gui/GuiManager.cpp gui/GuiManager.h gui/elements/menu/GuiVerticalMenu.cpp gui/elements/menu/GuiVerticalMenu.h gui/GuiMainMenu.cpp gui/GuiMainMenu.h gui/GuiEditor.cpp gui/GuiEditor.h gui/elements/components/GuiStar.cpp gui/elements/components/GuiStar.h gui/elements/components/comet/GuiComet.cpp gui/elements/components/comet/GuiComet.h gui/elements/components/comet/CometTrailComponent.cpp gui/elements/components/comet/CometTrailComponent.h gui/GuiBase.cpp gui/GuiBase.h gui/elements/menu/GuiStarScreen.cpp gui/elements/menu/GuiStarScreen.h gui/GuiTextBox.cpp gui/GuiTextBox.h gui/GuiEditorMenu.cpp gui/GuiEditorMenu.h)