cmake_minimum_required(VERSION 3.28)

add_executable(
    main
    bot.cxx
    bot.hxx
    damage.hxx
    forwards.hxx
    main.cxx
    player.cxx
    player.hxx)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR})
