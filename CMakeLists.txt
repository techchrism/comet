cmake_minimum_required(VERSION 3.13)
project(TheEditor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(TheEditor main.cpp internal/LinkedList.h internal/LinkedListNode.h extra/Editor.cpp extra/Editor.h gui/InputHandler.h gui/GuiFrame.h gui/GuiFrame.cpp internal/Options.h internal/OptionsManager.cpp internal/OptionsManager.h gui/elements/GuiMenu.cpp gui/elements/GuiMenu.h gui/GuiManager.cpp gui/GuiManager.h)