add_library(${CMAKE_PROJECT_NAME}
  string_builder.c
  string_view.c
)

target_compile_options(
  ${CMAKE_PROJECT_NAME} PUBLIC
  -Wall -Werror -pedantic
  -fsanitize=address -fno-omit-frame-pointer
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
