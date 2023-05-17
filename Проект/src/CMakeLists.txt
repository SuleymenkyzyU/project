add_executable(towerblock
        main.cpp
        Application.cpp
        Application.h
        Background.cpp
        Background.h
        Crane.cpp
        Crane.h
        Game.cpp
        Game.h
        GameScene.cpp
        GameScene.h
        HighScoreScene.cpp
        HighScoreScene.h
        HowToPlayScene.cpp
        HowToPlayScene.h
        MainMenuScene.cpp
        MainMenuScene.h
        Resource.cpp
        Resource.h
        Scene.cpp
        Scene.h
        ScoreStorage.h
        Tower.cpp
        Tower.h
        Unit.cpp
        Unit.h
		)

target_compile_definitions(towerblock PRIVATE ${OXYGINE_DEFINITIONS})
target_link_libraries(towerblock PRIVATE ${OXYGINE_CORE_LIBS})
set_target_properties(towerblock PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        INCLUDE_DIRECTORIES "${OXYGINE_INCLUDE_DIRS}"
        )

if (WIN32) #disable console mode for VC++
		set_target_properties(towerblock PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)
